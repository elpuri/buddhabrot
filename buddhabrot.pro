#-------------------------------------------------
#
# Project created by QtCreator 2011-12-19T19:45:51
#
#-------------------------------------------------

QT       += core gui
contains(QT_MAJOR_VERSION, 5) {
    QT += widgets
}
TARGET = buddhabrot

TEMPLATE = app


SOURCES += main.cpp \
    viewer.cpp \
    buddhabrot.cpp

HEADERS += \
    viewer.h \
    buddhabrot.h




