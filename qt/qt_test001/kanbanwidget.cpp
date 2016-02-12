#include "kanbanwidget.h"
#include "mainwindow.h"
#include "actionmenuitems.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTreeWidget>
#include <QApplication>
#include <QMenu>
#include <QWindow>
#include <QInputDialog>

KanbanWidget::KanbanWidget(MainWindow* mainWindow)
   : QWidget((QWidget*) mainWindow),
     mp_mainWindow(mainWindow),
     UpdateTimer(this)
{
   setAutoFillBackground(true);
   QPalette Pal(palette());
   Pal.setColor(QPalette::Background, QColor(64, 128, 64));
   setPalette(Pal);

   connect(&UpdateTimer, SIGNAL(timeout()), this, SLOT(repaint()));
   UpdateTimer.start(250);
}

void KanbanWidget::ClearList(QList<KanbanTask*>& list)
{
   while(0 < list.size())
   {
      KanbanTask* task = list.back();
      list.pop_back();
      task->hide();
      delete task;
   }
}

void KanbanWidget::Clear()
{
   ClearList(m_readyList);
   ClearList(m_doingList);
   ClearList(m_doneList);
}

void KanbanWidget::CenterAllListItems(const QRegion& region,
                                      QList<KanbanTask*>& list)
{
   QPoint center(region.boundingRect().center());
   for(auto itr: list)
   {
      itr->Center(center);
      itr->show();
   }
}

void KanbanWidget::CenterAllItems()
{
   CenterAllListItems(m_readyRegion, m_readyList);
   CenterAllListItems(m_doingRegion, m_doingList);
   CenterAllListItems(m_doneRegion, m_doneList);
}

void KanbanWidget::AutoArrange(bool retainLists)
{
   if(!retainLists)
   {
      UpdateListRegions();
   }
   AutoArrange(m_readyRegion, m_readyList);
   AutoArrange(m_doingRegion, m_doingList);
   AutoArrange(m_doneRegion, m_doneList);
}

const QRegion& KanbanWidget::GetKanbanStateRegion(EnumKanbanState state)
{
   UpdateRegions();
   switch(state)
   {
   case kReady:
      return m_readyRegion;
   case kDoing:
      return m_doingRegion;
   case kDone:
      return m_doneRegion;
   default:
      break;
   }
   throw;
}

QList<KanbanTask*>& KanbanWidget::getReadyList()
{
   return m_readyList;
}

QList<KanbanTask*>& KanbanWidget::getDoingList()
{
   return m_doingList;
}

QList<KanbanTask*>& KanbanWidget::getDoneList()
{
   return m_doneList;
}

void KanbanWidget::onMenuAction(QAction* action)
{
   switch (action->data().toInt())
   {
   case kEditItem:
      EditItem();
      break;
   case kDelete:
      Delete();
      break;
   case kCut:
      Cut();
      break;
   case kCopy:
      Copy();
      break;
   case kPaste:
      Paste();
      break;
   case kLink:
      Link();
      break;
   case kAutoArrange:
      AutoArrange();
      break;
   default:
      throw;
   }
}

void KanbanWidget::paintEvent(QPaintEvent *pntEvent)
{
   QRect rect = pntEvent->rect();

   QPainter painter(this);
   painter.save();
   painter.setPen(Qt::lightGray);
   painter.setFont(QFont("Arial", 48));
   painter.drawText(rect, Qt::AlignCenter, "Kanban Board");
   QFont font("Arial", 16);
   font.setStyle(QFont::StyleItalic);
   painter.setFont(font);
   painter.drawText(rect, Qt::AlignHCenter | Qt::AlignBottom,
                    "Visualize your work\nLimit your work in progress\n");

   painter.setPen(QColor(0, 49, 83));
   painter.setFont(QFont("Arial", 24, QFont::DemiBold));

   static bool firstPaint(true);
   if(firstPaint)
   {
      QFontMetrics fMetrics(painter.font());
      QRect titleRect(rect);
      titleRect.setHeight(fMetrics.height() * 1.5);
      m_titleRegion = titleRect;
      firstPaint = false;
   }
   UpdateRegions();

   QRect readyRect(rect.left(), rect.top(), rect.right()/3,
                   m_titleRegion.boundingRect().height());
   static const QBrush b(Qt::white);
   painter.setBackground(b);
   painter.setBackgroundMode(Qt::BGMode::OpaqueMode);
   painter.fillRect(m_titleRegion.boundingRect(), b);

   // Draw outline rect & section dividers
   QBrush lineBrush(Qt::darkGray);
   painter.setPen(QPen(lineBrush, 6, Qt::SolidLine, Qt::SquareCap));
   painter.drawRect(rect);
   painter.setPen(QPen(lineBrush, 2, Qt::DotLine, Qt::SquareCap));

   QPoint top1_3(m_readyRegion.boundingRect().right(), rect.top());
   QPoint top2_3(m_doingRegion.boundingRect().right(), rect.top());
   painter.drawLine(top1_3, m_readyRegion.boundingRect().bottomRight());
   painter.drawLine(top2_3, m_doingRegion.boundingRect().bottomRight());

   // Draw Kanban header line
   painter.setPen(QPen(lineBrush, 3, Qt::SolidLine, Qt::SquareCap));
   painter.drawLine(m_titleRegion.boundingRect().bottomLeft(),
                    m_titleRegion.boundingRect().bottomRight());

   // Draw Kanban header text
   painter.setPen(QColor(0, 49, 83));
   painter.drawText(readyRect, Qt::AlignCenter, "Ready");
   readyRect.setLeft(readyRect.right());
   readyRect.setRight(2*readyRect.left());
   painter.drawText(readyRect, Qt::AlignCenter, "Doing");
   readyRect.setLeft(readyRect.right());
   readyRect.setRight(rect.right());
   painter.drawText(readyRect, Qt::AlignCenter, "Done!");

   painter.restore();
   QWidget::paintEvent(pntEvent);
}

void KanbanWidget::contextMenuEvent(QContextMenuEvent* event)
{
   QMenu* menu = new QMenu(this);
   size_t first(kEditItem);
   size_t last(kLink);
   for (size_t i = first; last >= i; ++i)
   {
      QAction* action = new QAction(actionTextPair[i].text, this);
      action->setData(actionTextPair[i].action);
      if((kLink == actionTextPair[i].action)
            || ((kPaste == actionTextPair[i].action)
                && mp_mainWindow->getClipboardList().empty())
        )
      {
         action->setEnabled(false);
      }
      menu->addAction(action);
      if(kPaste == actionTextPair[i].action)
      {
         menu->addSeparator();
      }
   }
   menu->addSeparator();
   QAction* action =
      new QAction(actionTextPair[kAutoArrange].text, this);
   action->setData(actionTextPair[kAutoArrange].action);
   menu->addAction(action);

   connect(menu, SIGNAL(triggered(QAction*)), this,
           SLOT(onMenuAction(QAction*)));

   QPoint pos0 = QApplication::topLevelWindows().front()->position();
   pos0.setY(pos0.y() - QApplication::style()->pixelMetric(
                QStyle::PM_TitleBarHeight));
   QPoint pos1(mapFromGlobal(QApplication::activeWindow()->pos()));
   menu->popup(mapFromGlobal(QCursor::pos()) + pos0 - pos1);
}

void KanbanWidget::keyPressEvent(QKeyEvent *event)
{
   if((event->key() == Qt::Key_X) && (event->modifiers() == Qt::CTRL))
   {
      Cut();
   }
   else if((event->key() == Qt::Key_C) && (event->modifiers() == Qt::CTRL))
   {
      Copy();
   }
   else if((event->key() == Qt::Key_V) && (event->modifiers() == Qt::CTRL))
   {
      Paste();
   }
   else if(event->key() == Qt::Key_Delete)
   {
      Delete();
   }
   else
   {
      QWidget::keyPressEvent(event);
   }
}

void KanbanWidget::resizeEvent(QResizeEvent *event)
{
   QWidget::resizeEvent(event);
   AutoArrange(true);
}

void KanbanWidget::ReplaceCategoryTree(EnumGTDCategory category,
                                       QList<KanbanTask*>& taskList)
{
   TreeNode node("temp");
   for(auto itr: taskList)
   {
      TreeNode newNode(itr->getText().toStdString());
      node.AddChildNode(newNode);
   }
//   PopulateChildren(treeWidgetItem, node);
   UserData::getInst().ReplaceCategoryTree(category, node.getChildren());
   UserData::getInst().DumpGTDCategory(category);
   mp_mainWindow->setDirtyFlag(true);
}

bool KanbanWidget::DeleteFromList(EnumGTDCategory category,
                                  QList<KanbanTask *>& kanbanList)
{
   int cnt(0);
   for(auto itr: kanbanList)
   {
      if(itr->hasFocus())
      {
         const QString& itemStr = itr->getText();
         if(!UserData::getInst().RemoveNthStrInCategory(itemStr.toStdString(),
               category, cnt))
         {
            throw;
         }
         itr->hide();
         kanbanList.removeAt(cnt);
         delete itr;
         return true;
      }
      ++cnt;
   }
   return false;
}

void KanbanWidget::EditItem()
{
   if(!EditItem(EnumGTDCategory::kKanbanReady, m_readyList))
   {
      if(!EditItem(EnumGTDCategory::kKanbanDoing, m_doingList))
      {
         EditItem(EnumGTDCategory::kKanbanDone, m_doneList);
      }
   }
}

bool KanbanWidget::EditItem(EnumGTDCategory category,
                            QList<KanbanTask *>& kanbanList)
{
   int cnt(0);
   for(auto itr: kanbanList)
   {
      if(itr->hasFocus())
      {
         string itemStr;
         UserData::getInst().GetNthCategoryStr(category, cnt, itemStr);
         QInputDialog inputDialog;// = new QInputDialog();
         inputDialog.setOptions(QInputDialog::NoButtons);

         bool ok;
         QString origText(itemStr.c_str());
         QString text =  inputDialog.getText(NULL ,"Edit Task",
                                             "Task name:", QLineEdit::Normal,
                                             origText, &ok);
         if (ok && !text.isEmpty())
         {
            UserData::getInst().RemoveNthStrInCategory(itemStr, category, cnt);
            UserData::getInst().AddStrToCategory(text.toStdString(), category);
            itr->setText(text);
            mp_mainWindow->setDirtyFlag(true);
            AutoArrange();
         }
         return true;
      }
      ++cnt;
   }
   return false;
}

void KanbanWidget::Delete()
{
   if(!DeleteFromList(EnumGTDCategory::kKanbanReady, m_readyList))
   {
      if(!DeleteFromList(EnumGTDCategory::kKanbanDoing, m_doingList))
      {
         DeleteFromList(EnumGTDCategory::kKanbanDone, m_doneList);
      }
   }
}

bool KanbanWidget::CutFromList(EnumGTDCategory category,
                               QList<KanbanTask*>& kanbanList)
{
   int cnt(0);
   for(auto itr: kanbanList)
   {
      if(itr->hasFocus())
      {
         mp_mainWindow->getClipboardList().append(itr->getText());
         const QString& itemStr = itr->getText();
         if(!UserData::getInst().RemoveNthStrInCategory(itemStr.toStdString(),
               category, cnt))
         {
            throw;
         }
         itr->hide();
         kanbanList.removeAt(cnt);
         delete itr;
         return true;
      }
      ++cnt;
   }
   return false;
}

void KanbanWidget::Cut()
{
   if(!CutFromList(EnumGTDCategory::kKanbanReady, m_readyList))
   {
      if(!CutFromList(EnumGTDCategory::kKanbanDoing, m_doingList))
      {
         CutFromList(EnumGTDCategory::kKanbanDone, m_doneList);
      }
   }
}

bool KanbanWidget::CopyFromList(QList<KanbanTask *>& kanbanList)
{
   for(auto itr: kanbanList)
   {
      if(itr->hasFocus())
      {
         mp_mainWindow->getClipboardList().append(itr->getText());
         return true;
      }
   }
   return false;
}

void KanbanWidget::Copy()
{
   if(!CopyFromList(m_readyList))
   {
      if(!CopyFromList(m_doingList))
      {
         CopyFromList(m_doneList);
      }
   }
}

void KanbanWidget::Paste()
{
   for(auto itr: mp_mainWindow->getClipboardList())
   {
      KanbanTask* task = new KanbanTask(this);
      task->setText(itr);
      m_readyList.push_back(task);
      m_readyList.back()->move(20, 80);
      m_readyList.back()->show();
      m_readyList.back()->setFocus();
   }
//   QList<KanbanTask*> m_readyList;
//   QList<KanbanTask*> m_doingList;
//   QList<KanbanTask*> m_doneList;
   ReplaceCategoryTree(EnumGTDCategory::kKanbanReady, m_readyList);
   mp_mainWindow->setDirtyFlag(true);
   mp_mainWindow->getClipboardList().clear();
   AutoArrange();
}

void KanbanWidget::Link()
{
}

void KanbanWidget::MoveTasks(EnumGTDCategory srcCategory,
                             QList<KanbanTask*>& srcList,
                             QList<KanbanTask*>& destList)
{
   for(auto itr: srcList)
   {
      destList.push_back(itr);
   }
   srcList.clear();
   UserData::getInst().RemoveAllChildrenInCategory(srcCategory);
}

void KanbanWidget::UpdateListRegions()
{
   UpdateRegions();
   if((0 == m_readyList.size())
         && (0 == m_doingList.size())
         && (0 == m_doneList.size())
     )
   {
      return;
   }
   QList<KanbanTask*> tmpList;
   MoveTasks(EnumGTDCategory::kKanbanReady, m_readyList, tmpList);
   MoveTasks(EnumGTDCategory::kKanbanDoing, m_doingList, tmpList);
   MoveTasks(EnumGTDCategory::kKanbanDone, m_doneList, tmpList);
   while(0 < tmpList.size())
   {
      KanbanTask* task = tmpList.front();
      QPoint center(task->mapToParent(task->rect().center()));
      if(m_readyRegion.boundingRect().y() < center.y())
      {
         center.setY(m_readyRegion.boundingRect().y());
      }
      const string& newItemStr(tmpList.front()->getText().toStdString());
      if(m_readyRegion.contains(center))
      {
         UserData::getInst().AddStrToCategory(newItemStr,
                                              EnumGTDCategory::kKanbanReady);
         m_readyList.push_back(tmpList.front());
         tmpList.erase(tmpList.begin());
      }
      else if(m_doingRegion.contains(center))
      {
         UserData::getInst().AddStrToCategory(newItemStr,
                                              EnumGTDCategory::kKanbanDoing);
         m_doingList.push_back(tmpList.front());
         tmpList.erase(tmpList.begin());
      }
      else if(m_doneRegion.contains(center))
      {
         UserData::getInst().AddStrToCategory(newItemStr,
                                              EnumGTDCategory::kKanbanDone);
         m_doneList.push_back(tmpList.front());
         tmpList.erase(tmpList.begin());
      }
      else
      {
         return;
//         throw;
      }
   }
}

void KanbanWidget::AutoArrange(const QRegion& region, QList<KanbanTask*>& list)
{
   if(0 == list.size())
   {
      return;
   }
   // Center all items so horizontal position will not change
   for(auto itr: list)
   {
      itr->Center(region.boundingRect().center());
   }

   int netSpacing(region.boundingRect().height());
   for(auto itr: list)
   {
      netSpacing -= itr->height();
   }

   int factor(0);
   if(0 <= netSpacing)
   {
      while(netSpacing > (factor * (list.size() + 1)))
      {
         ++factor;
      }
   }
   else
   {
      while(netSpacing < (factor * (list.size() + 1)))
      {
         --factor;
      }
   }

   int top(m_titleRegion.boundingRect().height());
   for(auto itr: list)
   {
      top += factor;
      QPoint pos = itr->pos();
      pos.setY(top);
      itr->move(pos);
      top += itr->height();
   }
}

void KanbanWidget::UpdateRegion(const QRect& inRect, QRegion& outRegion)
{
   QRegion tmpRegion(inRect);
   outRegion.swap(tmpRegion);
}

void KanbanWidget::UpdateRegions()
{
   QRect currRect(rect());
   {
      QRect tmpRect(currRect);
      tmpRect.setBottom(m_titleRegion.boundingRect().height() - 1);
      UpdateRegion(tmpRect, m_titleRegion);
   }

   currRect.setTop(m_titleRegion.boundingRect().height());
   const int x1 = currRect.width() / 3;
   const int x2 = currRect.width() - x1;
   const int x3 = currRect.width();
   QRect tmpRect(currRect);
   tmpRect.setRight(x1);
   UpdateRegion(tmpRect, m_readyRegion);
   tmpRect.setLeft(x1);
   tmpRect.setRight(x2);
   UpdateRegion(tmpRect, m_doingRegion);
   tmpRect.setLeft(x2);
   tmpRect.setRight(x3);
   UpdateRegion(tmpRect, m_doneRegion);
}
