#include "gtdtreewidget.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDrag>
#include <QMimeData>
#include <QMenu>

GTDTreeWidget::GTDTreeWidget(MainWindow* mainWindow)
   : mp_mainWindow(mainWindow),
     m_dirtyFlag(false),
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
   SetTreeItemProperties (m_nonActionableTWI);
   SetTreeItemProperties (m_SomedayMaybeTWI);
   SetTreeItemProperties (m_ReferenceTWI);
   SetTreeItemProperties (m_TrashTWI);
   SetTreeItemProperties (m_actionableTWI);
   SetTreeItemProperties (m_tasksTWI);
   SetTreeItemProperties (m_DoItTWI);
   SetTreeItemProperties (m_WaitingOnSomeoneTWI);
   SetTreeItemProperties (m_CalendarTWI);
   SetTreeItemProperties (m_NextActionsTWI);
   SetTreeItemProperties (m_projectsTWI);
   SetTreeItemProperties (m_projectsToPlanTWI);
   SetTreeItemProperties (m_projectPlansTWI);

   setColumnCount(1);
   setHeaderLabel(QString("      3. GTD Tree"));
   setSortingEnabled(false);
   setAcceptDrops(true);
   setDragEnabled(true);
   setDragDropMode(QTreeWidget::InternalMove);

   setSelectionMode(QAbstractItemView::ExtendedSelection);

   addChild(&m_nonActionableTWI, &m_SomedayMaybeTWI, false, true);
   addChild(&m_nonActionableTWI, &m_ReferenceTWI, false, true);
   addChild(&m_nonActionableTWI, &m_TrashTWI, false, true);
   addChild(&m_actionableTWI, &m_tasksTWI, true, true);
   insertTopLevelItem(0, &m_actionableTWI);
   insertTopLevelItem(0, &m_nonActionableTWI);
   addChild(&m_tasksTWI, &m_DoItTWI, true, true);
   addChild(&m_tasksTWI, &m_WaitingOnSomeoneTWI, true, true);
   addChild(&m_tasksTWI, &m_CalendarTWI, true, true);
   addChild(&m_tasksTWI, &m_NextActionsTWI, true, true);
   addChild(&m_actionableTWI, &m_projectsTWI, true, true);
   addChild(&m_projectsTWI, &m_projectsToPlanTWI, true, true);
   addChild(&m_projectsTWI, &m_projectPlansTWI, true, true);
   ResetDirtyFlag();
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

bool GTDTreeWidget::IsDirty() const
{
   return m_dirtyFlag;
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
   QList<QTreeWidgetItem* > childList;
   childList = m_SomedayMaybeTWI.takeChildren();
   childList = m_ReferenceTWI.takeChildren();
   childList = m_TrashTWI.takeChildren();

   childList = m_DoItTWI.takeChildren();
   childList = m_WaitingOnSomeoneTWI.takeChildren();
   childList = m_CalendarTWI.takeChildren();
   childList = m_NextActionsTWI.takeChildren();

   childList = m_projectsToPlanTWI.takeChildren();
   childList = m_projectPlansTWI.takeChildren();
   m_dirtyFlag = true;
}

void GTDTreeWidget::ReloadTree()
{
   ReplaceCategoryTree(EnumGTDCategory::kSomedayMaybe, m_SomedayMaybeTWI);
   ReplaceCategoryTree(EnumGTDCategory::kReference, m_ReferenceTWI);
   ReplaceCategoryTree(EnumGTDCategory::kTrash, m_TrashTWI);
   ReplaceCategoryTree(EnumGTDCategory::kDoIt, m_DoItTWI);
   ReplaceCategoryTree(EnumGTDCategory::kWaitingForAnotherPerson,
                       m_WaitingOnSomeoneTWI);
   ReplaceCategoryTree(EnumGTDCategory::kCalendar, m_CalendarTWI);
   ReplaceCategoryTree(EnumGTDCategory::kNextActions, m_NextActionsTWI);
   ReplaceCategoryTree(EnumGTDCategory::kProjectsToPlan, m_projectsToPlanTWI);
   ReplaceCategoryTree(EnumGTDCategory::kProjectPlans, m_projectPlansTWI);
}

bool GTDTreeWidget::AddNode(const TreeNode& node, EnumGTDCategory category)
{
   if (!IsValidGTDTreeCategory(category))
   {
      return false;
   }
   QTreeWidgetItem* twi = GetTreeWidgetItem(category);
   m_dirtyFlag = true;
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
      addChild(twi, childItem, itr.getExpandState());
   }
   m_dirtyFlag = true;
   return true;
}

void GTDTreeWidget::addChild(QTreeWidgetItem* parent, QTreeWidgetItem* child,
                             bool expand, bool topLevelItem)
{
   if (!topLevelItem)
   {
      static const QBrush b(QColor(255, 255, 128));
      child->setBackground(0, b);
   }
   parent->addChild(child);
   if (expand)
   {
      expandItem(child);
   }
   m_dirtyFlag = true;
}

void GTDTreeWidget::ResetDirtyFlag()
{
   m_dirtyFlag = false;
}

bool GTDTreeWidget::AreTWIsEqual(const QTreeWidgetItem* lhs,
                                 const QTreeWidgetItem* rhs) const
{
   return (visualItemRect(lhs) == visualItemRect(rhs));
}

void GTDTreeWidget::mousePressEvent(QMouseEvent* event)
{
   if (event->button() == Qt::LeftButton)
//        && mp_inBasketForm->inBasketTextEdit->geometry().contains(event->pos())) {
   {
      QPoint pos = event->pos();
      const QTreeWidgetItem& item = *itemAt(pos.x(), pos.y());
//        const QString itemStr = item.text(0);

      QDrag* drag = new QDrag(this);
      QMimeData* mimeData = new QMimeData;

//        mimeData->setText(commentEdit->toPlainText());
      drag->setMimeData(mimeData);
//        drag->setPixmap(iconPixmap);

//        Qt::DropAction dropAction = drag->exec();
//        ...
   }
   QTreeWidget::mousePressEvent(event);
}

void GTDTreeWidget::keyPressEvent(QKeyEvent* event)
{
   if((event->key() == Qt::Key_1) && (event->modifiers() == Qt::ALT))
   {
      mp_mainWindow->SetFocusInTextEdit();
   }
   else if((event->key() == Qt::Key_2) && (event->modifiers() == Qt::ALT))
   {
      mp_mainWindow->SetFocusInListWidget();
   }
   else if(((event->key() == Qt::Key_C) && (event->modifiers() == Qt::CTRL))
           || ((event->key() == Qt::Key_X) && (event->modifiers() == Qt::CTRL)))
   {
      QList<QTreeWidgetItem*> items = selectedItems();
      for(auto itr: items)
      {
         if(!itr->font(0).bold())
         {
            mp_mainWindow->getClipboardList().append(itr->text(0));
            cout << mp_mainWindow->getClipboardList().size() << endl;
            if(event->key() == Qt::Key_X)
            {
               QTreeWidgetItem* parent(itr->parent());
               delete parent->takeChild(parent->indexOfChild(itr));
            }
         }
      }
      ReloadTree();
   }
   else if((event->key() == Qt::Key_V) && (event->modifiers() == Qt::CTRL))
   {
       QList<QTreeWidgetItem*> items = selectedItems();
       if(0 == items.size())
       {
          return;
       }
       for(auto itr: mp_mainWindow->getClipboardList())
       {
          QStringList strings;
          strings.append(itr);
          QTreeWidgetItem* item = new QTreeWidgetItem(strings);
          static const QBrush b(QColor(255, 255, 128));
          item->setBackground(0, b);
          items[0]->addChild(item);
       }
       mp_mainWindow->getClipboardList().clear();
   }
   else
   {
      QTreeWidget::keyPressEvent(event);
   }
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

bool GTDTreeWidget::IsPosInMemberHdrTWI(const QPoint& pos, bool gtdTWI) const
{
   bool retVal(false);
   retVal = retVal || visualItemRect(&m_nonActionableTWI).contains(pos);
   retVal = retVal || visualItemRect(&m_actionableTWI).contains(pos);
   retVal = retVal || visualItemRect(&m_tasksTWI).contains(pos);
   retVal = retVal || visualItemRect(&m_projectsTWI).contains(pos);
   if(gtdTWI)
   {
      retVal = retVal || visualItemRect(&m_SomedayMaybeTWI).contains(pos);
      retVal = retVal || visualItemRect(&m_ReferenceTWI).contains(pos);
      retVal = retVal || visualItemRect(&m_TrashTWI).contains(pos);
      retVal = retVal || visualItemRect(&m_DoItTWI).contains(pos);
      retVal = retVal || visualItemRect(&m_WaitingOnSomeoneTWI).contains(pos);
      retVal = retVal || visualItemRect(&m_CalendarTWI).contains(pos);
      retVal = retVal || visualItemRect(&m_NextActionsTWI).contains(pos);
      retVal = retVal || visualItemRect(&m_projectsToPlanTWI).contains(pos);
      retVal = retVal || visualItemRect(&m_projectPlansTWI).contains(pos);
   }
   const int delta(1);
   const QTreeWidgetItem* pItem = itemAt(pos.x(), pos.y());
   const QRect itemRect = visualItemRect(pItem);
   retVal = retVal || (delta >= (pos.y() - itemRect.top()));
   retVal = retVal || (delta >= (itemRect.bottom() - pos.y()));
//   retVal = retVal || (delta >= abs(itemRect.y() - pos.y()));
   cout << (pos.y() - itemRect.top()) << ", " << (pos.y() - itemRect.bottom())
        << endl;
   return retVal;
}

void GTDTreeWidget::PopulateChildren(QTreeWidgetItem& treeWidgetItem,
                                     TreeNode& node)
{
   if (!isItemExpanded(&treeWidgetItem))
   {
      node.SetExpandState(false);
   }
   int cnt(0);
   while (treeWidgetItem.childCount() > cnt)
   {
      QTreeWidgetItem* child = treeWidgetItem.child(cnt);
      cout << "GTD tree item: " << child->text(0).toStdString() << endl;
      TreeNode newNode(child->text(0).toStdString(), &node);
      TreeNode& childNode = node.AddChildNode(newNode);
      if (0 < child->childCount())
      {
         PopulateChildren(*child, childNode);
      }
      ++cnt;
   }
   m_dirtyFlag = true;
}

void GTDTreeWidget::ReplaceCategoryTree(EnumGTDCategory category,
                                        QTreeWidgetItem& treeWidgetItem)
{
   TreeNode node("temp");
   PopulateChildren(treeWidgetItem, node);
   UserData::getInst().ReplaceCategoryTree(category, node.getChildren());
   UserData::getInst().DumpGTDCategory(category);
   m_dirtyFlag = true;
}

void GTDTreeWidget::dropEvent(QDropEvent* event)
{
   bool move(Qt::MoveAction == event->proposedAction());
   // Case where move is not allowed
   if (move && IsPosInMemberHdrTWI(event->pos(), false))
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
   ReplaceCategoryTree(EnumGTDCategory::kWaitingForAnotherPerson,
                       m_WaitingOnSomeoneTWI);
   ReplaceCategoryTree(EnumGTDCategory::kCalendar, m_CalendarTWI);
   ReplaceCategoryTree(EnumGTDCategory::kNextActions, m_NextActionsTWI);
   ReplaceCategoryTree(EnumGTDCategory::kProjectsToPlan, m_projectsToPlanTWI);
   ReplaceCategoryTree(EnumGTDCategory::kProjectPlans, m_projectPlansTWI);
   m_dirtyFlag = true;
}

enum EnumAction
{
   kMoveUp,
   kMoveDown,
   kMoveToTop,
   kMoveToBottom,
   kDelete,
   kCut,
   kCopy,
   kPaste,
   kLink,
   kMoveUpLevel,
   kExpandAll,
   kCollapseAll,
};

struct SActionTextPair
{
   EnumAction action;
   QString text;
};

const size_t SActionTextPairLen(12);
const SActionTextPair actionTextPair[SActionTextPairLen] =
{
   { kMoveUp, "Move Up" },
   { kMoveDown, "Move Down" },
   { kMoveToTop, "Move To Top" },
   { kMoveToBottom, "Move To Bottom" },
   { kDelete, "Delete" },
   { kCut, "Cut" },
   { kCopy, "Copy" },
   { kPaste, "Paste" },
   { kLink, "Link" },
   { kMoveUpLevel, "Move Up Level" },
   { kExpandAll, "Expand All" },
   { kCollapseAll, "Collapse All" },
};

void GTDTreeWidget::onCustomContextMenuRequested(const QPoint& pos)
{
   QMenu* menu = new QMenu(this);
   for (size_t i = 0; SActionTextPairLen > i; ++i)
   {
      QAction* action = new QAction(actionTextPair[i].text, this);
      action->setData(actionTextPair[i].action);
      menu->addAction(action);
   }
   connect(menu, SIGNAL(triggered(QAction*)), this,
           SLOT(onMenuAction(QAction*)));

   menu->popup(viewport()->mapToGlobal(pos));
}

void GTDTreeWidget::onMenuAction(QAction* action)
{
   int k = action->data().toInt();
   cout << action->data().toInt() << endl;
   switch (action->data().toInt())
   {
   case kMoveUp:
      break;
   case kMoveDown:
      break;
   case kMoveToTop:
      break;
   case kMoveToBottom:
      break;
   case kDelete:
      break;
   case kCut:
      break;
   case kCopy:
      break;
   case kPaste:
      break;
   case kLink:
      break;
   case kMoveUpLevel:
      break;
   case kExpandAll:
      m_nonActionableTWI.setExpanded(true);
      m_SomedayMaybeTWI.setExpanded(true);
      m_ReferenceTWI.setExpanded(true);
      m_TrashTWI.setExpanded(true);
      m_actionableTWI.setExpanded(true);
      m_tasksTWI.setExpanded(true);
      m_DoItTWI.setExpanded(true);
      m_WaitingOnSomeoneTWI.setExpanded(true);
      m_CalendarTWI.setExpanded(true);
      m_NextActionsTWI.setExpanded(true);
      m_projectsTWI.setExpanded(true);
      m_projectsToPlanTWI.setExpanded(true);
      m_projectPlansTWI.setExpanded(true);
      break;
   case kCollapseAll:
      m_nonActionableTWI.setExpanded(false);
      m_SomedayMaybeTWI.setExpanded(false);
      m_ReferenceTWI.setExpanded(false);
      m_TrashTWI.setExpanded(false);
      m_actionableTWI.setExpanded(false);
      m_tasksTWI.setExpanded(false);
      m_DoItTWI.setExpanded(false);
      m_WaitingOnSomeoneTWI.setExpanded(false);
      m_CalendarTWI.setExpanded(false);
      m_NextActionsTWI.setExpanded(false);
      m_projectsTWI.setExpanded(false);
      m_projectsToPlanTWI.setExpanded(false);
      m_projectPlansTWI.setExpanded(false);
      break;
   default:
      throw;
   }
}
