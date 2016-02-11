#ifndef KANBANWIDGET_H
#define KANBANWIDGET_H

#include "kanbantask.h"
#include "../../code/UserData.h"
#include <QWidget>
#include <QTimer>

using namespace ZiegGTDKanban;

class MainWindow;

enum EnumKanbanState
{
   kReady,
   kDoing,
   kDone,
};

class KanbanWidget : public QWidget
{
Q_OBJECT

public:
   explicit KanbanWidget(MainWindow* mainWindow);

   void ClearList(QList<KanbanTask*>& list);
   void Clear();
   void CenterAllListItems(const QRegion& region, QList<KanbanTask*>& list);
   void CenterAllItems();
   void AutoArrange(bool retainLists = false);
   const QRegion& GetKanbanStateRegion(EnumKanbanState state);

   QList<KanbanTask*>& getReadyList();
   QList<KanbanTask*>& getDoingList();
   QList<KanbanTask*>& getDoneList();

signals:

public slots:
   void onMenuAction(QAction* action);

Q_SIGNALS:
protected:
   // Event handlers
   virtual void paintEvent(QPaintEvent* event);
   virtual void contextMenuEvent(QContextMenuEvent* event);
   virtual void keyPressEvent(QKeyEvent *event);
   virtual void resizeEvent(QResizeEvent *event);

protected:
   void ReplaceCategoryTree(EnumGTDCategory category,
                            QList<KanbanTask*>& taskList);
   bool DeleteFromList(EnumGTDCategory category,
                       QList<KanbanTask *>& kanbanList);
   void Delete();
   bool CutFromList(EnumGTDCategory category, QList<KanbanTask *>& kanbanList);
   void Cut();
   bool CopyFromList(QList<KanbanTask *>& kanbanList);
   void Copy();
   void Paste();
   void Link();
   void MoveTasks(EnumGTDCategory srcCategory,
                  QList<KanbanTask*>& srcList, QList<KanbanTask*>& destList);
public:
   void UpdateListRegions();
protected:
   void AutoArrange(const QRegion& region, QList<KanbanTask*>& list);

private:
   void UpdateRegion(const QRect& inRect, QRegion& outRegion);
   // UpdateRegions() determines each region's boundaries afresh.
   void UpdateRegions();

   QList<KanbanTask*> m_readyList;
   QList<KanbanTask*> m_doingList;
   QList<KanbanTask*> m_doneList;
   MainWindow*        mp_mainWindow;

   QRegion m_titleRegion;
   QRegion m_readyRegion;
   QRegion m_doingRegion;
   QRegion m_doneRegion;
   QTimer UpdateTimer;

   friend class MainWindow;
};

#endif // KANBANWIDGET_H
