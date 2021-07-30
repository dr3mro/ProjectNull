QT += quick multimedia qml

CONFIG += c++14 static
CONFIG -= qtquickcompiler
CONFIG += lrelease
CONFIG += embed_translations

mac:QMAKE_INFO_PLIST = src/mac/info.plist
mac:LIBS += -framework Carbon
mac:ICON = src/images/icon.icns
mac:DEFINES += INCLUDE_PRIVATE_API=1

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
    src/playerengine.h \
    src/singleinstance.h \
    src/win/protocolregister.h

SOURCES += \
        src/datahelper.cpp \
        src/main.cpp \
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
