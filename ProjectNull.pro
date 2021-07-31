QT += quick multimedia qml

CONFIG += c++14 static
CONFIG -= qtquickcompiler
CONFIG += lrelease
CONFIG += embed_translations

mac:QMAKE_INFO_PLIST = src/mac/info.plist
mac:LIBS += -framework Carbon
mac:ICON = src/images/icon.icns
mac:DEFINES += INCLUDE_PRIVATE_API=1

win32-g++:DEFINES += _WIN32_WINNT=0x0602
win32:RC_ICONS=src/images/icon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += src/qml.qrc

TRANSLATIONS += \
    src/ProjectNull_ar_EG.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = src/qml/

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = src/qml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


HEADERS += \
    src/datahelper.h \
    src/logger.h \
    src/mdebug.h \
    src/mdkplayer.h \
    src/playerengine.h \
    src/singleinstance.h \
    src/win/protocolregister.h

SOURCES += \
        src/datahelper.cpp \
        src/main.cpp \
        src/mdkplayer.cpp \
        src/playerengine.cpp \
        src/singleinstance.cpp

mac:HEADERS +=\
    src/mac/fileopenevent.h \
    src/mac/darwincapturepreventer.h

mac:SOURCES += \
    src/mac/fileopenevent.cpp \
    src/mac/darwincapturepreventer.mm

DISTFILES += \
    ReadMe.txt \
    ToDo.txt \
    src/images/icon.ico \
    src/mac/Info.plist




########
macx:MDK_SDK = /Users/amr/Repos/ProjectNull/src/mac/libs/mdk-sdk
INCLUDEPATH += $$MDK_SDK/include
contains(QT_ARCH, x.*64) {
  android: MDK_ARCH = x86_64
  else:linux: MDK_ARCH = amd64
  else: MDK_ARCH = x64
} else:contains(QT_ARCH, .*86) {
  MDK_ARCH = x86
} else:contains(QT_ARCH, a.*64.*) { # arm64-v8a
  android: MDK_ARCH = arm64-v8a
  else: MDK_ARCH = arm64
} else:contains(QT_ARCH, arm.*) {
  android: MDK_ARCH = armeabi-v7a
  else:linux: MDK_ARCH = armhf
  else: MDK_ARCH = arm
}
static|contains(CONFIG, staticlib) {
  DEFINES += Q_MDK_API
} else {
  DEFINES += Q_MDK_API=Q_DECL_EXPORT
}
macx|ios {
  MDK_ARCH=
  QMAKE_CXXFLAGS += -F$$MDK_SDK/lib
  LIBS += -F$$MDK_SDK/lib -F/usr/local/lib -framework mdk
} else {
  LIBS += -L$$MDK_SDK/lib/$$MDK_ARCH -lmdk
}

mac {
  RPATHDIR *= @executable_path/Frameworks $$MDK_SDK/lib
  QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/
  isEmpty(QMAKE_LFLAGS_RPATH): QMAKE_LFLAGS_RPATH=-Wl,-rpath,
  for(R,RPATHDIR) {
    QMAKE_LFLAGS *= \'$${QMAKE_LFLAGS_RPATH}$$R\'
  }
}




