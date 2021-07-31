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
#include "src/playercontroller.h"
#include "src/singleinstance.h"
#include "src/mdebug.h"
#include "src/mdkplayer.h"

#ifdef LOGEDNABLED
#include "src/logger.h"
#endif


#ifdef Q_OS_WIN
#include <Windows.h>
#include <WinUser.h>
#include "src/win/protocolregister.h"
#endif

#ifdef Q_OS_MACOS
#include "src/mac/fileopenevent.h"
#include "datahelper.h"
#include "mac/darwincapturepreventer.h"
#endif


int main(int argc, char *argv[])
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // as of Qt 6.0 this is the default behaviour so this code is for backward compatibility only //
    //                                                                                            //
                              #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)                          //
                     QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);                 //
                              #endif                                                              //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // Create a new app object
    QGuiApplication app(argc, argv);

#ifdef Q_OS_WIN
    // Call register protocol code
    registerProtocol();

    // Set the executable path as Current Working Directory
    QDir::setCurrent(qApp->applicationDirPath());
#endif

#ifdef LOGEDNABLED
    // Log Message Handler
    qInstallMessageHandler(myMessageLogger);
    qSetMessagePattern("[%{type}] %{appname} (%{file}:%{line}) - %{message}");
#endif

    mDebug() << "initialising...";

    // Start the player Controller
    PlayerController playercontroller (DataHelper::processURL(qApp->arguments().join(",")));

    mDebug() << "PlayerController Started ...";

    // Start the single instance Server to prevent more than one instance at the same time
    SingleInstance singleInstance;

    mDebug() << "SingleInstance localserver Started ...";

    // Create a string to store the video URL
    QString & videoUrl = playercontroller.getVideoUrl();

    mDebug() << "VideoUrl linked ...";

#ifdef Q_OS_MACOS
    FileOpenEvent foef;
    QObject::connect(&foef,&FileOpenEvent::urlOpened,&playercontroller,&PlayerController::setVideoUrl);
    qApp->installEventFilter(&foef);
    mDebug() << "DARWIN fileopener initialised ...";
#endif

    // We here connect the single instance DoAction that is called when a new instance is started
    // it will call setVideoUrl in PlayerController so the current running app will get the url from
    // the newly started instance
    QObject::connect(&singleInstance,&SingleInstance::doAction,&playercontroller,&PlayerController::setVideoUrl);
    mDebug() << "SingleInstance connected ...";


    // here we close self if found a previous instance is running after sending the url
    if(singleInstance.hasPrevious("com.nullproject.videoPlayer", videoUrl)){
        mDebug() << "Found another instance Exiting ...";
        exit(1);
    }


    // start listening for new instances from now on if found no other instances running
    // and listen locally to the domain
    singleInstance.listen("com.nullproject.videoPlayer");
    mDebug() << "SingleInstance listening ...";

    // create translator object
    QTranslator translator;
    mDebug() << "translator created ...";


    // search if current OS locale is found then load it
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ProjectNull_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            mDebug() << "translator loaded ...";
            break;
        }
    }

    // QML GUI Engine
    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    QmlMDKPlayer mdkPlayer;

    qmlRegisterType<QmlMDKPlayer>("MDKPlayer", 1, 0, "MDKPlayer");

    context->setContextProperty("PlayerController", &playercontroller);     // give QML acces to PlayerEngine
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
    playercontroller.startPlayingMovie();


    // The Magic code is goes here that make screen capture impossible

#ifdef Q_OS_MACOS
    DarwinCapturePreventer dcp(app,nullptr);
#endif

#ifdef Q_OS_WIN
    SetWindowDisplayAffinity(GetActiveWindow(),WDA_MONITOR);
#endif
    // this is loop event handler that if close the app will quit
    mDebug() << "App is running ...";
    return app.exec();
}


////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
