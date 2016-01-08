#-------------------------------------------------
#
# Project created by QtCreator 2015-12-20T17:51:43
#
#-------------------------------------------------

QT       += core gui

DEFINES += BOOST_SYSTEM_NO_DEPRECATED
win32{
DEFINES += BOOST_ERROR_CODE_HEADER_ONLY
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_test001
TEMPLATE = app

X11 {
INCLUDEPATH += /usr/include/boost/ \
            /usr/include/boost/date_time/gregorian/
            ../../code
}
else:win32{
INCLUDEPATH += C:\dev\boost_1_60_0 \
               C:\dev\github\GTD-Kanban\code
}

SOURCES += main.cpp\
        mainwindow.cpp \
        inbasketform.cpp \
        gtdtreewidget.cpp \
        kanbancalendardialog.cpp \
        gtdcalendarwidget.cpp
unix {
SOURCES += ../../code/UserData.cpp \
            ../../code/TreeNode.cpp \
            ../../code/BoostJSON.cpp
}
else:win32 {
SOURCES += C:\dev\github\GTD-Kanban\code\UserData.cpp \
            C:\dev\github\GTD-Kanban\code\TreeNode.cpp
}

HEADERS  += mainwindow.h \
    inbasketform.h \
    gtdtreewidget.h \
    kanbancalendardialog.h \
    gtdcalendarwidget.h
unix {
HEADERS += ../../code/UserData.h \
            ../../code/TreeNode.h   \
            ../../code/BoostJSON.h
}
else:win32{
HEADERS += C:\dev\github\GTD-Kanban\code\UserData.h \
        C:\dev\github\GTD-Kanban\code\TreeNode.h
}

FORMS    += mainwindow.ui \
    inbasketform.ui \
    kanbancalendardialog.ui

unix {
LIBS += -lboost_system \
        -lboost_filesystem \
        -lboost_regex   \
        -lboost_date_time    \
         -lpthread
}
else:win32{
LIBS += -LC:/dev/boost_1_60_0/stage/lib \
        -llibboost_system-vc140-mt-1_60  \
        -lpthread
}

# Added 2015-12-21 by Fred
CONFIG += c++14
