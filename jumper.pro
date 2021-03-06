TEMPLATE = app

QT += opengl multimedia
android: QT += sensors

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
	src/main.cpp \
    src/renderwidget.cpp \
    src/graphicscontroller.cpp \
    src/graphicsobject.cpp \
    src/graphicsscene.cpp \
    src/abstractcontroller.cpp \
    src/core.cpp \
    src/renderer.cpp \
    src/physicscontroller.cpp \
    src/graphicscamera.cpp \
    src/physicsscene.cpp \
    src/physicsbody.cpp \
    src/physicsgeometry.cpp \
    src/gameobject.cpp \
    src/gamecontroller.cpp \
    src/gameabstractscene.cpp \
    src/gamescenelevel.cpp \
    src/gameobjectbrick.cpp \
    src/gameobjectplayer.cpp \
    src/gameobjectguibutton.cpp \
    src/gameobjectbackground.cpp \
    src/gameobjectgun.cpp \
    src/gameobjectabstractmodifier.cpp \
    src/gameobjectmodifierrotate.cpp \
    src/gameobjectmodifieroffset.cpp \
    src/gameobjectmodifiertrain.cpp \
    src/gameobjectbrokenbrick.cpp \
    src/gamescenemainmenu.cpp \
    src/gamesceneauthorsmenu.cpp \
    src/gameobjecttext.cpp \
    src/gamescenegameover.cpp \
    src/gameobjectlevelpassed.cpp \
    src/gamescenelevelpassed.cpp \
    src/audiocontroller.cpp \
    src/gamescenepause.cpp \
    src/gamesceneselectlevel.cpp \
    src/gamelevelloader.cpp \
    src/gameobjectspike.cpp

HEADERS += \
    src/renderwidget.h \
    src/types.h \
    src/graphicscontroller.h \
    src/graphicsobject.h \
    src/graphicsscene.h \
    src/abstractcontroller.h \
    src/core.h \
    src/renderer.h \
    src/physicscontroller.h \
    src/graphicscamera.h \
    src/physicsscene.h \
    src/physicsbody.h \
    src/physicsgeometry.h \
    src/gameobject.h \
    src/gamecontroller.h \
    src/gameabstractscene.h \
    src/gamescenelevel.h \
    src/gameobjectbrick.h \
    src/gameobjectplayer.h \
    src/gameobjectguibutton.h \
    src/gameobjectbackground.h \
    src/gameobjectgun.h \
    src/gameobjectabstractmodifier.h \
    src/gameobjectmodifierrotate.h \
    src/gameobjectmodifieroffset.h \
    src/gameobjectmodifiertrain.h \
    src/gameobjectbrokenbrick.h \
    src/mathutils.h \
    src/gamescenemainmenu.h \
    src/gamesceneauthorsmenu.h \
    src/gameobjecttext.h \
    src/gamescenegameover.h \
    src/gameobjectlevelpassed.h \
    src/gamescenelevelpassed.h \
    src/audiocontroller.h \
    src/gamescenepause.h \
    src/gamesceneselectlevel.h \
    src/gamelevelloader.h \
    src/gameobjectspike.h

LIBS += -lGLESv2

DEFINES += JUMPER_DEBUG

RESOURCES += \
	jumper.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    res/icon.png

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
