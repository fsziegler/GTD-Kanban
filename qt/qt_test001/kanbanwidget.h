#ifndef KANBANWIDGET_H
#define KANBANWIDGET_H

#include <QWidget>
#include <QTimer>
#include "kanbantask.h"

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
   explicit KanbanWidget(QWidget *parent = 0);

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
   void Delete();
   void Cut();
   void Copy();
   void Paste();
   void Link();

private:
   void UpdateRegion(const QRect& inRect, QRegion& outRegion);
   void UpdateRegions();

   QList<KanbanTask*> m_readyList;
   QList<KanbanTask*> m_doingList;
   QList<KanbanTask*> m_doneList;

   QRegion m_titleRegion;
   QRegion m_readyRegion;
   QRegion m_doingRegion;
   QRegion m_doneRegion;
//   KanbanTask m_testChild;
   QTimer UpdateTimer;
};

#endif // KANBANWIDGET_H
