#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inbasketform.h"
#include "gtdtreewidget.h"
#include "gtdcalendarwidget.h"
#include "kanbanwidget.h"

#include <QMainWindow>
#include <QSplitter>
#include <QPointer>
#include <QTextEdit>
#include <QCalendarWidget>

namespace Ui
{
class MainWindow;
}

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();
    UserData& getUserData();

protected:
   void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
   void mouseMoveEvent(QMouseEvent *event);
   void OpenFile(const QString& fileName);
   void AddToFileHistory(const QString& fileName);
   void UpdateRecentFilesMenu();

private slots:
   void on_actionExit_triggered();

   void on_action_New_triggered();

   void on_actionSave_triggered();

   void on_actionSave_As_triggered();

   void on_actionAbout_triggered();

   void on_action_Open_triggered();

   void OpenRecentFile0();
   void OpenRecentFile1();
   void OpenRecentFile2();
   void OpenRecentFile3();
   void OpenRecentFile4();
   void OpenRecentFile5();
   void OpenRecentFile6();
   void OpenRecentFile7();
   void OpenRecentFile8();
   void OpenRecentFile9();

private:
   void ScaleAndCenterWindow(float scale);

   Ui::MainWindow*               ui;
   UserData m_userData;

   QPointer<InBasketForm>        mp_inBasketForm;
   QPointer<QSplitter>           mp_gtdSplitter;
   QPointer<QSplitter>           mp_mainLRSplitter;
   QTextEdit                     m_gtdEditor;
   GTDTreeWidget                 m_gtdTree;

   QPointer<QSplitter>           mp_kanbanSplitter;
   QPointer<GTDCalendarWidget>   mp_gtdCalendar;
   QPointer<KanbanWidget>        mp_kanbanWindow;

   QString                       m_currentFileNameStr;
   QStringList                   m_recentFileList;
};
#endif // MAINWINDOW_H
