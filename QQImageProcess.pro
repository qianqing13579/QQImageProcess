QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Src/ImageProcess/Bmp.h \
    Src/ImageProcess/Edge.h \
    Src/ImageProcess/Filter.h \
    Src/ImageProcess/GeometryTransformation.h \
    Src/ImageProcess/GrayTransformation.h \
    Src/ImageProcess/Histogram.h \
    Src/ImageProcess/Utility.h \
    Src/Utility/Alloc.h \
    Src/Utility/BmpDefinition_Linux.h \
    Src/Utility/BmpDefinition_Windows.h \
    Src/Utility/CommonDefinition.h \
    Src/Utility/Mat.h \
    Src/Samples.h

SOURCES += \
    Src/ImageProcess/Bmp.cpp \
    Src/ImageProcess/Edge.cpp \
    Src/ImageProcess/Filter.cpp \
    Src/ImageProcess/GeometryTransformation.cpp \
    Src/ImageProcess/GrayTransformation.cpp \
    Src/ImageProcess/Histogram.cpp \
    Src/ImageProcess/Utility.cpp \
    Src/Utility/Alloc.cpp \
    Src/Samples.cpp \
    Src/main.cpp

INCLUDEPATH +=\
            ./Src/ImageProcess/  \
            ./Src/Utility/  \
            ./Src/


