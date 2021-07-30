///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
/*  Protocol Register to make this video player the default app to
    plabyback urls in the form of

    projectNull::[file:///C:/Users/Amr/Downloads/video1.mp4]

    projectNull::[http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/ElephantsDream.mp4]

    just pass any as first app argument and it will be played back either local or remote

    This code works only under windows
*/
#ifdef Q_OS_WIN
#pragma once

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
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
