#-------------------------------------------------
#
# Project created by QtCreator 2012-10-14T11:49:19
#
#-------------------------------------------------

QT       += core widgets

TARGET = ScanCode
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp
#use_cvsnakeimage.cpp

HEADERS  += mainwindow.h
#        use_cvsnakeimage.h

FORMS    += mainwindow.ui

LIBS += -lopencv_core \
        -lopencv_videoio \
        -lopencv_highgui \
        -lopencv_imgcodecs \
        -lopencv_imgproc \

INCLUDEPATH += 3rdparty/zint-2.5.1/build/include
LIBS += -L"$$_PRO_FILE_PWD_/3rdparty/zint-2.5.1/build/lib"
LIBS += -lzbar -lzint
