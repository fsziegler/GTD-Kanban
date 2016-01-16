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

protected:
   void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
   void mouseMoveEvent(QMouseEvent *event);

private slots:
   void on_actionExit_triggered();

   void on_actionOpen_triggered();

   void on_action_New_triggered();

   void on_actionSave_triggered();

   void on_actionSave_As_triggered();

   void on_actionAbout_triggered();

private:
   void ScaleAndCenterWindow(float scale);

   Ui::MainWindow *ui;

   InBasketForm m_inBasketForm;
   QPointer<QSplitter> mp_gtdSplitter;
   QPointer<QSplitter> mp_mainLRSplitter;
   QTextEdit m_gtdEditor;
   GTDTreeWidget m_gtdTree;

   QPointer<QSplitter> mp_kanbanSplitter;
   GTDCalendarWidget m_gtdCalendar;
   KanbanWidget m_kanbanWindow;

   QString m_currentFileNameStr;
};
#endif // MAINWINDOW_H
