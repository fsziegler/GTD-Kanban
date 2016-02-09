#ifndef GTDTREEWIDGET_H
#define GTDTREEWIDGET_H

#include "../../code/UserData.h"
#include <QTreeWidget>
#include <QDropEvent>

using namespace ZiegGTDKanban;

class MainWindow;

class GTDTreeWidget: public QTreeWidget
{
Q_OBJECT

public:
   GTDTreeWidget(MainWindow* mainWindow);
   virtual ~GTDTreeWidget();

   // INFORMATIONAL
   bool IsBranchCollapsed(const QString& branchStr) const;
   bool IsValidGTDTreeCategory(EnumGTDCategory category) const;

   // ACCESSORS
   QTreeWidgetItem* GetTreeWidgetItem(EnumGTDCategory category);

   // MODIFIERS
   // ClearTree() clears all GTD QTreeWidgetItem contents.
   void ClearTree();
   // ReloadTree() reloads the GTD QTreeWidgetItems into the UserData
   // singleton, which causes the expand/collapse states to be updated.
   void ReloadTree();
   bool AddNode(const TreeNode& node, EnumGTDCategory category);
   bool AddNode(const TreeNode& node, QTreeWidgetItem* twi);
   void addChild(QTreeWidgetItem* parent, QTreeWidgetItem* child, bool expand,
                 bool topLevelItem = false);

protected:
   bool AreTWIsEqual(const QTreeWidgetItem* lhs,
                     const QTreeWidgetItem* rhs) const;

Q_SIGNALS:
protected:
   // Event handlers
   virtual void mousePressEvent(QMouseEvent* event);
   virtual void keyPressEvent(QKeyEvent* event);
protected:
   // SetTreeItemProperties() sets the flags, foreground, and font of treeItem.
   void SetTreeItemProperties(QTreeWidgetItem& treeItem);
   bool IsPosInMemberHdrTWI(const QPoint& pos, bool gtdTWI) const;
   // PopulateChildren() populates node with the treeWidgetItem contents.
   void PopulateChildren(QTreeWidgetItem& treeWidgetItem, TreeNode& node);
   // ReplaceCategoryTree() populates category in the UserData singleton with
   // the contents of treeWidgetItem.
   void ReplaceCategoryTree(EnumGTDCategory category,
                            QTreeWidgetItem& treeWidgetItem);
   void MoveUp();
   void MoveDown();
   void MoveToTop();
   void MoveToBottom();
   void SortAscending();
   void SortDescending();
   void Delete();
   void Cut();
   void Copy();
   void Paste();
   void Link();
   void MoveUpLevel();
   void ExpandAll();
   void CollapseAll();

   void dropEvent(QDropEvent* event);

public slots:
   void onCustomContextMenuRequested(const QPoint& pos);
   void onMenuAction(QAction* action);
   void EditItem(QTreeWidgetItem *item);

private:
   // NOT IMPLEMENTED
   GTDTreeWidget();

   MainWindow*      mp_mainWindow;
   QTreeWidgetItem* mp_editItem;
   QString          m_editItemStr;

   QTreeWidgetItem  m_nonActionableTWI;
   QTreeWidgetItem  m_SomedayMaybeTWI;
   QTreeWidgetItem  m_ReferenceTWI;
   QTreeWidgetItem  m_TrashTWI;

   QTreeWidgetItem  m_actionableTWI;
   QTreeWidgetItem  m_tasksTWI;
   QTreeWidgetItem  m_DoItTWI;
   QTreeWidgetItem  m_WaitingOnSomeoneTWI;
   QTreeWidgetItem  m_CalendarTWI;
   QTreeWidgetItem  m_NextActionsTWI;

   QTreeWidgetItem  m_projectsTWI;
   QTreeWidgetItem  m_projectsToPlanTWI;
   QTreeWidgetItem  m_projectPlansTWI;
};

#endif // GTDTREEWIDGET_H
