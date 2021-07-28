#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QDir>
#include <QLocale>
#include <QTranslator>
#include <QQmlContext>
#include "videocapturedetector.h"
#include "playerengine.h"
#include "singleinstance.h"

void registerProtocol(){
    const QString urlScheme = "projectNull";
    const QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    const QString regPath = QStringLiteral("HKEY_CURRENT_USER\\Software\\Classes\\") + urlScheme;

    QScopedPointer<QSettings> reg(new QSettings(regPath, QSettings::NativeFormat));

    reg->setValue(QStringLiteral("Default"), "video player");
    reg->setValue(QStringLiteral("URL Protocol"), QString());

    reg->beginGroup(QStringLiteral("DefaultIcon"));
    reg->setValue(QStringLiteral("Default"), QString("%1,1").arg(appPath));
    reg->endGroup();

    reg->beginGroup(QStringLiteral("shell"));
    reg->beginGroup(QStringLiteral("open"));
    reg->beginGroup(QStringLiteral("command"));
    reg->setValue(QStringLiteral("Default"), appPath + QLatin1String(" %1"));
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QDir::setCurrent(qApp->applicationDirPath());

    registerProtocol();

    QString videoUrl;

    if(argc > 1 )
        videoUrl = DataHelper::processURL(qApp->arguments().join(","));

    SingleInstance singleInstance;

    PlayerEngine playerengine (videoUrl);

    QObject::connect(&singleInstance,&SingleInstance::doAction,&playerengine,&PlayerEngine::setVideoUrl);

    if(singleInstance.hasPrevious("com.nullproject.videoPlayer", videoUrl))
        exit(1);

    singleInstance.listen("com.nullproject.videoPlayer");

    VideoCaptureDetector vcd;

    QTranslator translator;

    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ProjectNull_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("VideoCaptureDetector", &vcd);
    context->setContextProperty("PlayerEngine", &playerengine);
    context->setContextProperty("SingleInstance", &singleInstance);


    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    playerengine.startPlayingMovie();

    return app.exec();
}
