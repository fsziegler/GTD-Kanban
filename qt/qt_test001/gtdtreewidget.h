#ifndef GTDTREEWIDGET_H
#define GTDTREEWIDGET_H

#include "../../code/UserData.h"
#include <QTreeWidget>
#include <QDropEvent>

using namespace ZiegGTDKanban;

class MainWindow;

class GTDTreeWidget: public QTreeWidget
{
public:
   GTDTreeWidget(MainWindow* mainWindow);
   virtual ~GTDTreeWidget();

   // INFORMATIONAL
   bool IsBranchCollapsed(const QString& branchStr) const;
   bool IsValidGTDTreeCategory(EnumGTDCategory category) const;
   bool IsDirty() const;

   // ACCESSORS
   QTreeWidgetItem* GetTreeWidgetItem(EnumGTDCategory category);

   // MODIFIERS
   void ClearTree();
   bool AddNode(const TreeNode& node, EnumGTDCategory category);
   bool AddNode(const TreeNode& node, QTreeWidgetItem* twi);
   void addChild(QTreeWidgetItem* parent, QTreeWidgetItem *child, bool expand,
                 bool topLevelItem = false);
   void ResetDirtyFlag();

Q_SIGNALS:
protected:
    // Event handlers
    virtual void mousePressEvent(QMouseEvent *);
protected:
   void SetTreeItemProperties(QTreeWidgetItem& treeItem);
   bool IsPosInMemberHdrTWI(const QPoint& pos) const;
   void PopulateChildren(QTreeWidgetItem& treeWidgetItem, TreeNode& node);
   void ReplaceCategoryTree(EnumGTDCategory category,
         QTreeWidgetItem& treeWidgetItem);
   void dropEvent(QDropEvent * event);

private:
   // NOT IMPLEMENTED
   GTDTreeWidget();

   MainWindow*     mp_mainWindow;
   bool            m_dirtyFlag;
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
