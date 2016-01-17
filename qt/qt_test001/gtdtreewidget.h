#ifndef GTDTREEWIDGET_H
#define GTDTREEWIDGET_H

#include "../../code/UserData.h"
#include <QTreeWidget>
#include <QDropEvent>

using namespace ZiegGTDKanban;

class GTDTreeWidget: public QTreeWidget
{
public:
   GTDTreeWidget();
   virtual ~GTDTreeWidget();

   bool IsBranchCollapsed(const QString& branchStr) const;
   bool IsValidGTDTreeCategory(EnumGTDCategory category) const;
   QTreeWidgetItem* GetTreeWidgetItem(EnumGTDCategory category);
   void ClearTree();
   bool AddNode(const TreeNode& node, EnumGTDCategory category);
   bool AddNode(const TreeNode& node, QTreeWidgetItem* twi);
   void addChild(QTreeWidgetItem* parent, QTreeWidgetItem *child, bool topLevelItem = false);

protected:
   void SetTreeItemProperties(QTreeWidgetItem& treeItem);
   bool IsPosInMemberHdrTWI(const QPoint& pos) const;
   void dropEvent(QDropEvent * event);

private:
   QTreeWidgetItem m_nonActionableTWI;
   QTreeWidgetItem m_SomedayMaybeTWI;
   QTreeWidgetItem m_ReferenceTWI;
   QTreeWidgetItem m_TrashTWI;

   QTreeWidgetItem m_actionableTWI;
   QTreeWidgetItem m_tasksTWI;
   QTreeWidgetItem m_DoItTWI;
   QTreeWidgetItem m_WaitingOnSomeoneTWI;
   QTreeWidgetItem m_CalendarTWI;
   QTreeWidgetItem m_NextActionsTWI;

   QTreeWidgetItem m_projectsTWI;
   QTreeWidgetItem m_projectsToPlanTWI;
   QTreeWidgetItem m_projectPlansTWI;
};

#endif // GTDTREEWIDGET_H
