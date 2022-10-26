QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32

    }
}
else {
        LIBS     += -lGL -lGLU
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
TARGET = AstroGameExe
SOURCES += \
    asteroid.cpp \
    astroGame.cpp \
    main.cpp \
    space.cpp \
    spaceship.cpp \
    spacestation.cpp

HEADERS += \
    asteroid.h \
    astroGame.h \
    space.h \
    spaceship.h \
    spacestation.h

FORMS += \
    astroGame.ui


# ajout des libs au linker
INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include


LIBS += -L$$(OPENCV_DIR)\lib \
-lopengl32 -lglu32 \
-L$$(OPENCV_DIR)\lib \
-lopencv_core455 \
-lopencv_highgui455 \
-lopencv_imgproc455 \
-lopencv_imgcodecs455 \
-lopencv_videoio455 \
-lopencv_features2d455 \
-lopencv_calib3d455 \
-lopencv_objdetect455


RESOURCES += \
    resources/textures.qrc
