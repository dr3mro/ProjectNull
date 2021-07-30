QT += quick multimedia qml

CONFIG += c++14 static
CONFIG -= qtquickcompiler
CONFIG += lrelease
CONFIG += embed_translations

mac:QMAKE_INFO_PLIST = src/info.plist
mac:LIBS += -framework Carbon
mac:ICON = src/images/icon.icns


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

SOURCES += \
        src/datahelper.cpp \
        src/main.cpp \
        src/playerengine.cpp \
        src/singleinstance.cpp

HEADERS += \
    src/datahelper.h \
    src/playerengine.h \
    src/singleinstance.h

DISTFILES += \
    ReadMe.txt \
    ToDo.txt \
    src/images/icon.ico
