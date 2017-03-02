QT     += core widgets concurrent
CONFIG += c++11
TARGET = ImagesBrowser
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    dirimagesmodel.cpp \
    imagesview.cpp \
    thumbnailsstorage.cpp \
    dirstreeview.cpp

HEADERS  += mainwindow.h \
    dirimagesmodel.h \
    imagesview.h \
    thumbnailsstorage.h \
    dirstreeview.h
