#include "gtdtreewidget.h"
#include "mainwindow.h"
#include<QMessageBox>

GTDTreeWidget::GTDTreeWidget(MainWindow* mainWindow)
      : mp_mainWindow(mainWindow),
        m_nonActionableTWI((QTreeWidget*) 0,
              QStringList(QString("Non-Actionable"))),
        m_SomedayMaybeTWI((QTreeWidget*) 0,
              QStringList(QString("Someday Maybe"))),
        m_ReferenceTWI((QTreeWidget*) 0, QStringList(QString("Reference"))),
        m_TrashTWI((QTreeWidget*) 0, QStringList(QString("Trash"))),
        m_actionableTWI((QTreeWidget*) 0, QStringList(QString("Actionable"))),
        m_tasksTWI((QTreeWidget*) 0, QStringList(QString("Tasks"))),
        m_DoItTWI((QTreeWidget*) 0, QStringList(QString("Do It!"))),
        m_WaitingOnSomeoneTWI((QTreeWidget*) 0,
              QStringList(QString("Waiting for Another Person"))),
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

   addChild(&m_nonActionableTWI, &m_SomedayMaybeTWI, true);
   addChild(&m_nonActionableTWI, &m_ReferenceTWI, true);
   addChild(&m_nonActionableTWI, &m_TrashTWI, true);
   addChild(&m_actionableTWI, &m_tasksTWI, true);
   insertTopLevelItem(0, &m_actionableTWI);
   insertTopLevelItem(0, &m_nonActionableTWI);
   addChild(&m_tasksTWI, &m_DoItTWI, true);
   addChild(&m_tasksTWI, &m_WaitingOnSomeoneTWI, true);
   addChild(&m_tasksTWI, &m_CalendarTWI, true);
   addChild(&m_tasksTWI, &m_NextActionsTWI, true);
   addChild(&m_actionableTWI, &m_projectsTWI, true);
   addChild(&m_projectsTWI, &m_projectsToPlanTWI, true);
   addChild(&m_projectsTWI, &m_projectPlansTWI, true);
   expandAll();
}

GTDTreeWidget::~GTDTreeWidget()
{
}

bool GTDTreeWidget::IsBranchCollapsed(const QString& branchStr) const
{
   return ((branchStr == QString("Trash")) || (branchStr == QString("Calendar")));
}

bool GTDTreeWidget::IsValidGTDTreeCategory(EnumGTDCategory category) const
{
   if ((EnumGTDCategory::kInBasket == category)
         || (EnumGTDCategory::kMoveQueue == category)
         || (EnumGTDCategory::kGTDCategoryUNKNOWN == category))
   {
      return false;
   }
   return true;
}

QTreeWidgetItem* GTDTreeWidget::GetTreeWidgetItem(EnumGTDCategory category)
{
   switch (category)
   {
//    case EnumGTDCategory::kInBasket:
   case EnumGTDCategory::kSomedayMaybe:
      return &m_SomedayMaybeTWI;
   case EnumGTDCategory::kReference:
      return &m_ReferenceTWI;
   case EnumGTDCategory::kDoIt:
      return &m_DoItTWI;
   case EnumGTDCategory::kWaitingForAnotherPerson:
      return &m_WaitingOnSomeoneTWI;
   case EnumGTDCategory::kCalendar:
      return &m_CalendarTWI;
   case EnumGTDCategory::kProjectsToPlan:
      return &m_projectsToPlanTWI;
   case EnumGTDCategory::kProjectPlans:
      return &m_projectPlansTWI;
   case EnumGTDCategory::kNextActions:
      return &m_NextActionsTWI;
   case EnumGTDCategory::kTrash:
      return &m_TrashTWI;
   case EnumGTDCategory::kMoveQueue:
   default:
      throw;
   }
}

void GTDTreeWidget::ClearTree()
{
   QList<QTreeWidgetItem *> childList;
   childList = m_SomedayMaybeTWI.takeChildren();
   childList = m_ReferenceTWI.takeChildren();
   childList = m_TrashTWI.takeChildren();

   childList = m_DoItTWI.takeChildren();
   childList = m_WaitingOnSomeoneTWI.takeChildren();
   childList = m_CalendarTWI.takeChildren();
   childList = m_NextActionsTWI.takeChildren();

   childList = m_projectsToPlanTWI.takeChildren();
   childList = m_projectPlansTWI.takeChildren();
}

bool GTDTreeWidget::AddNode(const TreeNode& node, EnumGTDCategory category)
{
   if (!IsValidGTDTreeCategory(category))
   {
      return false;
   }
   QTreeWidgetItem* twi = GetTreeWidgetItem(category);
   return AddNode(node, twi);
}

bool GTDTreeWidget::AddNode(const TreeNode& node, QTreeWidgetItem* twi)
{
   for (auto itr : node.getChildren())
   {
      QStringList strings;
      strings.append(itr.getMpNodeNameStr().c_str());
      QTreeWidgetItem* childItem = new QTreeWidgetItem(strings);
      AddNode(itr, childItem);
      addChild(twi, childItem);
   }
   return true;
}

void GTDTreeWidget::addChild(QTreeWidgetItem* parent, QTreeWidgetItem *child, bool topLevelItem)
{
    if(!topLevelItem)
    {
        static const QBrush b(QColor(255, 255, 128));
        child->setBackground(0, b);
    }
    parent->addChild(child);
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

   const int delta(1);
   const QTreeWidgetItem* pItem = itemAt(pos.x(), pos.y());
   const QRect itemRect = visualItemRect(pItem);
   retVal = retVal || (delta >= (pos.y() - itemRect.top()));
   retVal = retVal || (delta >= (itemRect.bottom() - pos.y()));
//   retVal = retVal || (delta >= abs(itemRect.y() - pos.y()));
   cout << (pos.y() - itemRect.top()) << ", " << (pos.y() - itemRect.bottom()) << endl;
   return retVal;
}

void GTDTreeWidget::PopulateChildren(QTreeWidgetItem& treeWidgetItem,
      TreeNode& node)
{
   int cnt(0);
   while(treeWidgetItem.childCount() > cnt)
   {
      QTreeWidgetItem *child = treeWidgetItem.child(cnt);
      cout << "GTD tree item: " << child->text(0).toStdString() << endl;
      TreeNode newNode(child->text(0).toStdString(), &node);
      TreeNode& childNode = node.AddChildNode(newNode);
      if(0 < child->childCount())
      {
          PopulateChildren(*child, childNode);
      }
      ++cnt;
   }
}

void GTDTreeWidget::ReplaceCategoryTree(EnumGTDCategory category,
      QTreeWidgetItem& treeWidgetItem)
{
   TreeNode node("temp");
   PopulateChildren(treeWidgetItem, node);
   mp_mainWindow->getUserData().ReplaceCategoryTree(category, node.getChildren());
   mp_mainWindow->getUserData().DumpGTDCategory(category);
}

void GTDTreeWidget::dropEvent(QDropEvent * event)
{
   bool move(Qt::MoveAction == event->proposedAction());
   // Case where move is not allowed
   if (move && IsPosInMemberHdrTWI(event->pos()))
   {
      setVisible(false);
      setVisible(true);
      return;
   }
   QTreeWidget::dropEvent(event);
   ReplaceCategoryTree(EnumGTDCategory::kSomedayMaybe, m_SomedayMaybeTWI);
   ReplaceCategoryTree(EnumGTDCategory::kReference, m_ReferenceTWI);
   ReplaceCategoryTree(EnumGTDCategory::kTrash, m_TrashTWI);
   ReplaceCategoryTree(EnumGTDCategory::kDoIt, m_DoItTWI);
   ReplaceCategoryTree(EnumGTDCategory::kWaitingForAnotherPerson, m_WaitingOnSomeoneTWI);
   ReplaceCategoryTree(EnumGTDCategory::kCalendar, m_CalendarTWI);
   ReplaceCategoryTree(EnumGTDCategory::kNextActions, m_NextActionsTWI);
   ReplaceCategoryTree(EnumGTDCategory::kProjectsToPlan, m_projectsToPlanTWI);
   ReplaceCategoryTree(EnumGTDCategory::kProjectPlans, m_projectPlansTWI);

}
