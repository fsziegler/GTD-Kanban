#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inbasketform.h"
#include "gtdtreewidget.h"
#include "gtdcalendarwidget.h"
#include "kanbanwidget.h"
#include "gtdtextedit.h"

#include <QMainWindow>
#include <QSplitter>
#include <QPointer>
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

//    void PushDragText(const QString& dragStr);
//    int PopDragText(QString& dragStr);
   void ShowStatusMessage(QString& statusMsg) const;

   void SetFocusInTextEdit();
   void SetFocusInListWidget();
   void SetFocusInGTDTreeWidget();
   void MinMaxInBasket();
   void setDirtyFlag(bool newState);
   bool isDirty() const;

   QStringList& getDragStringList();
   QStringList& getClipboardList();

   void PasteToKanban();

protected:
   bool LoadFromFile(const QString& jsonFileName);
   void OpenFile(const QString& fileName);
   void AddToFileHistory(const QString& fileName);
   void UpdateRecentFilesMenu();
   void CheckDirty(const QString& newTitle, const QString& newText);

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

Q_SIGNALS:
protected:
   // Event handlers
   virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
   virtual void mouseReleaseEvent(QMouseEvent* event);
   virtual void keyPressEvent(QKeyEvent* event);
   virtual void closeEvent(QCloseEvent* event);

private slots:
   void onCustomContextMenuRequested(const QPoint& pos);
   void on_actionMinimize_triggered();
   void on_actionMaximize_triggered();
   void on_actionRestore_triggered();

private:
   void ScaleAndCenterWindow(float scale);

   Ui::MainWindow*               ui;
   Qt::WindowStates              m_defaultWindowState;
   bool                          m_dirtyFlag;

   QPointer<InBasketForm>        mp_inBasketForm;
   QPointer<QSplitter>           mp_gtdSplitter;
   QPointer<QSplitter>           mp_mainLRSplitter;
   GTDTextEdit                   m_gtdTextEditor;
   GTDTreeWidget                 m_gtdTree;

   QPointer<QSplitter>           mp_kanbanSplitter;
   QPointer<GTDCalendarWidget>   mp_gtdCalendar;
   QPointer<KanbanWidget>        mp_kanbanWindow;

   QString                       m_currentFileNameStr;
   QStringList                   m_recentFileList;
   QStringList                   m_dragStringList;
   QStringList                   m_clipboardList;
};
#endif // MAINWINDOW_H
