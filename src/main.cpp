///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QDir>
#include <QLocale>
#include <QTranslator>
#include <QQmlContext>
#include "playerengine.h"
#include "singleinstance.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#include <stdio.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <WinUser.h>
#endif

#ifdef Q_OS_DARWIN
#include "fileopenevent.h"
#include "datahelper.h"
#include "darwincapturepreventer.h"
#endif

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }

    QFile outFile("/Users/amr/Desktop/log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << msg << '\n';
}

/*  Protocol Register to make this video player the default app to
    plabyback urls in the form of

    projectNull::[file:///C:/Users/Amr/Downloads/video1.mp4]

    projectNull::[http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/ElephantsDream.mp4]

    just pass any as first app argument and it will be played back either local or remote

    Platform independent code needs to be added here

    This code works only under windows

ToDo :
    Add MacOs altarnate code.
*/
#ifdef Q_OS_WIN
void registerProtocol(){

    // Set the ptotocol Name to (projectNull)
    const QString urlScheme = "projectNull";

    // Get the current executable path to remmember and always open with
    const QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());

    // This is the open with path (in windows)
    const QString regPath = QStringLiteral("HKEY_CURRENT_USER\\Software\\Classes\\") + urlScheme;

    // create a scopped poniter to avoid calling delete later
    QScopedPointer<QSettings> reg(new QSettings(regPath, QSettings::NativeFormat));

    // Starting to set the Registery keys

    reg->setValue(QStringLiteral("Default"), "video player");
    reg->setValue(QStringLiteral("URL Protocol"), QString());

    reg->beginGroup(QStringLiteral("DefaultIcon"));
    reg->setValue(QStringLiteral("Default"), QString("%1,1").arg(appPath));
    reg->endGroup();

    reg->beginGroup(QStringLiteral("shell"));
    reg->beginGroup(QStringLiteral("open"));
    reg->beginGroup(QStringLiteral("command"));

    reg->setValue(QStringLiteral("Default"), appPath + QLatin1String(" %1"));
    // end of protocol code under windows 10

}
#endif
int main(int argc, char *argv[])
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // as of Qt 6.0 this is the default behaviour so this code is for backward compatibility only //
    //                                                                                            //
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)                                                        //
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);                                  //
#endif                                                                                            //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // Create a new app object
    QGuiApplication app(argc, argv);

    // Log Message Handler
    qInstallMessageHandler(myMessageOutput);

    // Set the executable path as Current Working Directory
    QDir::setCurrent(qApp->applicationDirPath());

#ifdef Q_OS_WIN
    // Call register protocol code
    registerProtocol();
#endif
    // Start the player Engine ( actually it only do some stuff not the real video playback )
    PlayerEngine playerengine (DataHelper::processURL(qApp->arguments().join(",")));

    // Start the single instance Server to prevent more than one instance at the same time
    SingleInstance singleInstance;

    // Create a string to store the video URL
    QString & videoUrl = playerengine.getVideoUrl();

#ifdef Q_OS_DARWIN
    FileOpenEvent foef;
    QObject::connect(&foef,&FileOpenEvent::urlOpened,&playerengine,&PlayerEngine::setVideoUrl);

    qApp->installEventFilter(&foef);

#endif

    // We here connect the single instance DoAction that is called when a new instance is started
    // it will call setVideoUrl in PlayerEngine so the current running app will get the url from
    // the newly started instance
    QObject::connect(&singleInstance,&SingleInstance::doAction,&playerengine,&PlayerEngine::setVideoUrl);

    // here we close self if found a previous instance is running after sending the url
    if(singleInstance.hasPrevious("com.nullproject.videoPlayer", videoUrl))
        exit(1);

    // start listening for new instances from now on if found no other instances running
    // and listen locally to the domain
    singleInstance.listen("com.nullproject.videoPlayer");


    // create translator object
    QTranslator translator;

    // search if current OS locale is found then load it
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ProjectNull_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    // QML GUI Engine
    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    context->setContextProperty("PlayerEngine", &playerengine);     // give QML acces to PlayerEngine
    context->setContextProperty("SingleInstance", &singleInstance); // give QML acces to SingleInstance

    // set The main.qml path ( it holds the whole UI )
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    // connect signal to exit if failed to create GUI
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    // now GUI is ready lets load it
    engine.load(url);

    // lets start the video now
    playerengine.startPlayingMovie();



    // The Magic code is here
#ifdef Q_OS_WIN
    SetWindowDisplayAffinity(GetActiveWindow(),WDA_MONITOR);
#endif
    // this is loop event handler that if close the app will quit
    QTimer x;
    x.start(1000);
    DarwinCapturePreventer dcp(app,nullptr);
    QObject::connect(&x,&QTimer::timeout,&dcp,&DarwinCapturePreventer::update);

    return app.exec();
}


////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
