/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGTD;
    QAction *actionKanban;
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionExit;
    QAction *action_New;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuHelp;
    QMenu *menuWizard;
    QMenu *menuStats;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        actionGTD = new QAction(MainWindow);
        actionGTD->setObjectName(QStringLiteral("actionGTD"));
        actionKanban = new QAction(MainWindow);
        actionKanban->setObjectName(QStringLiteral("actionKanban"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QStringLiteral("action_New"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuWizard = new QMenu(menuBar);
        menuWizard->setObjectName(QStringLiteral("menuWizard"));
        menuStats = new QMenu(menuBar);
        menuStats->setObjectName(QStringLiteral("menuStats"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuWizard->menuAction());
        menuBar->addAction(menuStats->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(action_New);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuView->addAction(actionGTD);
        menuView->addAction(actionKanban);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionGTD->setText(QApplication::translate("MainWindow", "&GTD", 0));
        actionKanban->setText(QApplication::translate("MainWindow", "&Kanban", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "&Open", 0));
        actionClose->setText(QApplication::translate("MainWindow", "&Close", 0));
        actionSave->setText(QApplication::translate("MainWindow", "&Save", 0));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save &As", 0));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", 0));
        action_New->setText(QApplication::translate("MainWindow", "&New", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0));
        menuWizard->setTitle(QApplication::translate("MainWindow", "Wi&zard", 0));
        menuStats->setTitle(QApplication::translate("MainWindow", "S&tats", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
