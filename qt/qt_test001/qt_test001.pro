#-------------------------------------------------
#
# Project created by QtCreator 2015-12-20T17:51:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_test001
TEMPLATE = app

INCLUDEPATH += /usr/include/boost/\
            ../../code
LIBS += -lboost_system -lpthread

SOURCES += main.cpp\
        mainwindow.cpp \
    inbasketform.cpp \
    gtdtreewidget.cpp \
    kanbancalendardialog.cpp \
    gtdcalendarwidget.cpp \
    ../../code/UserData.cpp \
    ../../code/TreeNode.cpp

HEADERS  += mainwindow.h \
    inbasketform.h \
    gtdtreewidget.h \
    kanbancalendardialog.h \
    gtdcalendarwidget.h \
    ../../code/UserData.h \
    ../../code/TreeNode.h

FORMS    += mainwindow.ui \
    inbasketform.ui \
    kanbancalendardialog.ui

# Added 2015-12-21 by Fred
CONFIG += c++14
