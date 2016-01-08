#include "gtdtreewidget.h"
#include<QMessageBox>

GTDTreeWidget::GTDTreeWidget()
      : m_nonActionableTWI((QTreeWidget*) 0,
              QStringList(QString("Non-Actionable"))),
        m_SomedayMaybeTWI((QTreeWidget*) 0,
              QStringList(QString("Someday Maybe"))),
        m_ReferenceTWI((QTreeWidget*) 0, QStringList(QString("Reference"))),
        m_TrashTWI((QTreeWidget*) 0, QStringList(QString("Trash"))),
        m_actionableTWI((QTreeWidget*) 0, QStringList(QString("Actionable"))),
        m_tasksTWI((QTreeWidget*) 0, QStringList(QString("Tasks"))),
        m_DoItTWI((QTreeWidget*) 0, QStringList(QString("Do It!"))),
        m_WaitingOnSomeoneTWI((QTreeWidget*) 0,
              QStringList(QString("Waiting on someone"))),
        m_CalendarTWI((QTreeWidget*) 0, QStringList(QString("Calendar"))),
        m_NextActionsTWI((QTreeWidget*) 0,
              QStringList(QString("Next Actions"))),
        m_projectsTWI((QTreeWidget*) 0, QStringList(QString("Projects"))),
        m_projectsToPlanTWI((QTreeWidget*) 0,
              QStringList(QString("Projects-to-Plan"))),
        m_projectPlansTWI((QTreeWidget*) 0,
              QStringList(QString("Project Plans")))
{
   SetTreeItemProperties(m_nonActionableTWI);
   SetTreeItemProperties(m_SomedayMaybeTWI);
   SetTreeItemProperties(m_ReferenceTWI);
   SetTreeItemProperties(m_TrashTWI);
   SetTreeItemProperties(m_actionableTWI);
   SetTreeItemProperties(m_tasksTWI);
   SetTreeItemProperties(m_DoItTWI);
   SetTreeItemProperties(m_WaitingOnSomeoneTWI);
   SetTreeItemProperties(m_CalendarTWI);
   SetTreeItemProperties(m_NextActionsTWI);
   SetTreeItemProperties(m_projectsTWI);
   SetTreeItemProperties(m_projectsToPlanTWI);
   SetTreeItemProperties(m_projectPlansTWI);

   setColumnCount(1);
   setHeaderLabel(QString("      2. GTD Tree"));
   setSortingEnabled(false);
   setAcceptDrops(true);
   setDragEnabled(true);
   setDragDropMode(QTreeWidget::InternalMove);

   m_nonActionableTWI.addChild(&m_SomedayMaybeTWI);
   m_nonActionableTWI.addChild(&m_ReferenceTWI);
   m_nonActionableTWI.addChild(&m_TrashTWI);
   m_actionableTWI.addChild(&m_tasksTWI);
   insertTopLevelItem(0, &m_actionableTWI);
   insertTopLevelItem(0, &m_nonActionableTWI);
   m_tasksTWI.addChild(&m_DoItTWI);
   m_tasksTWI.addChild(&m_WaitingOnSomeoneTWI);
   m_tasksTWI.addChild(&m_CalendarTWI);
   m_tasksTWI.addChild(&m_NextActionsTWI);
   m_actionableTWI.addChild(&m_projectsTWI);
   m_projectsTWI.addChild(&m_projectsToPlanTWI);
   m_projectsTWI.addChild(&m_projectPlansTWI);
   expandAll();
}

GTDTreeWidget::~GTDTreeWidget()
{
}

bool GTDTreeWidget::IsBranchCollapsed(const QString& branchStr) const
{
   return ((branchStr == QString("Trash"))
         || (branchStr == QString("Calendar")));
}

void GTDTreeWidget::SetTreeItemProperties(QTreeWidgetItem& treeItem)
{
   static const Qt::ItemFlags flags(
         Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsUserCheckable
               | Qt::ItemIsEnabled);
   QFont font(treeItem.font(0).family(), 9, QFont::Bold);
   static const QBrush b(QColor(0, 49, 83));
   treeItem.setFlags(flags);
   treeItem.setForeground(0, b);
   treeItem.setFont(0, font);
}

bool GTDTreeWidget::IsPosInMemberHdrTWI(const QPoint& pos) const
{
   bool retVal(false);
   retVal = retVal || visualItemRect(&m_nonActionableTWI).contains(pos);
   retVal = retVal || visualItemRect(&m_actionableTWI).contains(pos);
   retVal = retVal || visualItemRect(&m_tasksTWI).contains(pos);
   retVal = retVal || visualItemRect(&m_projectsTWI).contains(pos);
   return retVal;
}

void GTDTreeWidget::dropEvent(QDropEvent * event)
{
   bool move(Qt::MoveAction == event->proposedAction());
   if (move && IsPosInMemberHdrTWI(event->pos()))
   {
      setVisible(false);
      setVisible(true);
      return;
   }
   QTreeWidget::dropEvent(event);
}
