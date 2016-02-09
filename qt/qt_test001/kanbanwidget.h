#ifndef KANBANWIDGET_H
#define KANBANWIDGET_H

#include "kanbantask.h"
#include <QWidget>
#include <QTimer>

enum EnumKanbanState
{
   kReady,
   kDoing,
   kDone,
};

class MainWindow;

class KanbanWidget : public QWidget
{
Q_OBJECT

public:
   explicit KanbanWidget(MainWindow* mainWindow);

   const QRegion& GetKanbanStateRegion(EnumKanbanState state);

signals:

public slots:
   void onMenuAction(QAction* action);

Q_SIGNALS:
protected:
   // Event handlers
   virtual void paintEvent(QPaintEvent* event);
   virtual void contextMenuEvent(QContextMenuEvent* event);

protected:
   bool DeleteFromList(QList<KanbanTask *>& kanbanList);
   void Delete();
   bool CutFromList(QList<KanbanTask *>& kanbanList);
   void Cut();
   bool CopyFromList(QList<KanbanTask *>& kanbanList);
   void Copy();
   void Paste();
   void Link();
   void MoveTasks(QList<KanbanTask*>& srcList, QList<KanbanTask*>& destList);
   void UpdateListRegions();
   void AutoArrange(const QRegion& region, QList<KanbanTask*>& list);
   void AutoArrange();

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
};

#endif // KANBANWIDGET_H
