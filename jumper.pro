TEMPLATE = app

QT += opengl

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
    src/gameobjectgun.cpp

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
    src/gameobjectgun.h

LIBS += -lGLESv2

DEFINES += JUMPER_DEBUG
