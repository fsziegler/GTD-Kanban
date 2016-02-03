#include "inbasketform.h"
#include "ui_inbasketform.h"
#include "kanbancalendardialog.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <QKeyEvent>
#include <QDrag>
#include <QMimeData>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

InBasketForm::InBasketForm(MainWindow* parent)
      : QWidget(parent),
        mp_inBasketForm(new Ui::InBasketForm),
        mp_mainWindow(parent),
        mp_gtdTree(nullptr)
{
   mp_inBasketForm->setupUi(this);
   mp_inBasketForm->inBasketListWidget->setSelectionMode(
         QAbstractItemView::ExtendedSelection);
   // TEMPORARY FOR QUICK TESTING
   const QString inBasket("Call Fred re tel. # for the garage he recommended.\n"
         "Draft thoughts for the budget-meeting agenda.\nTalk to Angela about "
         "the filing system we need to set up.\nResearch database-management "
         "software on the Web.\nGet new staff person on board August\nvacation "
         "Staff off-site retreat\nPublish book\nFinalize computer upgrades\n"
         "Update will\nFinalize budgets\nFinalize new product line\nGet "
         "comfortable with new contact-management software\nGet reprints of "
         "Fortune article\nGet a publicist\nFinish new orchard planting\nR&D "
         "joint-venture video project\nProduce new training compact disk\n"
         "Establish next year’s seminar schedule\nOrchestrate a one-hour "
         "keynote presentation\nGet proficient with videoconferencing access\n"
         "Finalize employment agreements\nInstall new backyard lights");
// Allen, David (2002-12-31). Getting Things Done: The Art of Stress-Free
// Productivity (p. 34). Penguin Group. Kindle Edition.

   mp_inBasketForm->inBasketTextEdit->setText(inBasket);
   mp_inBasketForm->inBasketTextEdit->setAcceptDrops(true);
   QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt,
         Qt::NoModifier);
   QCoreApplication::postEvent(this, event);
   mp_inBasketForm->inBasketTextEdit->setAcceptDrops(true);
   setAcceptDrops(true);

   SetFocusInTextEdit();
}

InBasketForm::~InBasketForm()
{
   delete mp_inBasketForm;
}

void InBasketForm::SetGTDTreeWidget(GTDTreeWidget* gtdTree)
{
   mp_gtdTree = gtdTree;
}

void InBasketForm::GetSelectionOutOfGTDBasketList(
      QList<QListWidgetItem*>& itemSelectionList, bool move)
{
   itemSelectionList = mp_inBasketForm->inBasketListWidget->selectedItems();
   if (move)
   {
//      cout << "BEGIN InBasketForm::GetSelectionOutOfGTDBasketList()" << endl;
//      mp_mainWindow->getUserData().DumpAllGTD();
      for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end();
            ++itr)
      {
         // Store and pass back the row so it can be used to ID the node to move
         const QString rowStr((*itr)->text());
         const int row = mp_inBasketForm->inBasketListWidget->row((*itr));
         string stdRowStr;
         UserData::getInst().ReadStrAtRow(EnumGTDCategory::kInBasket,
               row, stdRowStr);
         assert(stdRowStr == rowStr.toStdString());
         mp_inBasketForm->inBasketListWidget->takeItem(
               mp_inBasketForm->inBasketListWidget->row((*itr)));
         UserData::getInst().MoveNthStrBetweenCategories(stdRowStr,
               EnumGTDCategory::kInBasket, EnumGTDCategory::kMoveQueue, row);
      }
//      cout << "END InBasketForm::GetSelectionOutOfGTDBasketList()" << endl;
//      mp_mainWindow->getUserData().DumpAllGTD();
   }
}

void InBasketForm::MoveFromListToTree(QList<QListWidgetItem*> itemSelectionList,
      const QString& nodeNameStr)
{
   QList<QTreeWidgetItem*> gtdTreeList = mp_gtdTree->findItems(nodeNameStr,
         Qt::MatchExactly | Qt::MatchRecursive, 0);
   QTreeWidgetItem* gtdTreeItem = gtdTreeList.front();
   for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end();
         ++itr)
   {
      QTreeWidgetItem* qti = new QTreeWidgetItem((QTreeWidget*) 0,
            QStringList((*itr)->text()));
      mp_gtdTree->addChild(gtdTreeItem, qti,
                           mp_gtdTree->IsBranchCollapsed(nodeNameStr));
   }
   EnumGTDCategory tgtCat = UserData::getInst().LookUpCategory(
         nodeNameStr.toStdString());
   UserData::getInst().MoveAllBetweenCategories(
         EnumGTDCategory::kMoveQueue, tgtCat);
//   cout << "END InBasketForm::MoveFromListToTree()" << endl;
//   mp_mainWindow->getUserData().DumpAllGTD();
}

void InBasketForm::MoveFromGTDBasketListToTree(const QString& nodeNameStr)
{
   // Cursory check - should never fail
   if (nullptr == mp_gtdTree)
   {
      return;
   }
   // Another cursory check - should never fail
   QList<QTreeWidgetItem*> gtdTreeList = mp_gtdTree->findItems(nodeNameStr,
         Qt::MatchExactly | Qt::MatchRecursive, 0);
   if (0 == gtdTreeList.size())
   {
      QString errMsg(nodeNameStr);
      errMsg.append(QString(" not found!"));
      QMessageBox msg(QMessageBox::Warning, "Error:", errMsg, QMessageBox::Ok);
      msg.exec();
      return;
   }

   // Find category in target tree
   QList<QListWidgetItem*> itemSelectionList;
   GetSelectionOutOfGTDBasketList(itemSelectionList);
   MoveFromListToTree(itemSelectionList, nodeNameStr);
}

void InBasketForm::MoveFromGTDBasketListToTree(const QString& itemNameStr,
      const QString& nodeNameStr)
{
   QList<QListWidgetItem*> itemSelectionList = mp_inBasketForm
         ->inBasketListWidget->selectedItems();
   for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end();
         ++itr)
   {
      // Store and pass back the row so it can be used to ID the node to move
      const QString rowStr((*itr)->text());
      if (rowStr == itemNameStr)
      {
         const int row = mp_inBasketForm->inBasketListWidget->row((*itr));
         string stdRowStr;
         UserData::getInst().ReadStrAtRow(EnumGTDCategory::kInBasket,
               row, stdRowStr);
         assert(stdRowStr == rowStr.toStdString());
         mp_inBasketForm->inBasketListWidget->takeItem(
               mp_inBasketForm->inBasketListWidget->row((*itr)));
         UserData::getInst().MoveNthStrBetweenCategories(stdRowStr,
               EnumGTDCategory::kInBasket, EnumGTDCategory::kMoveQueue, row);
      }
   }
}

void InBasketForm::ClearWorkspace()
{
   mp_inBasketForm->inBasketTextEdit->clear();
   mp_inBasketForm->inBasketListWidget->clear();
   UserData::getInst().Clear();
}

bool InBasketForm::LoadFromFile(const QString& jsonFileName)
{
   if (!UserData::getInst().LoadFromJSONFile(
         jsonFileName.toStdString(), false))
   {
      return false;
   }
   mp_inBasketForm->inBasketTextEdit->clear();
   mp_inBasketForm->inBasketListWidget->clear();
   for (auto itr : UserData::getInst().getGtdNodeTree()) //Possible race condition here
   {
      const QString nodeNameStr(
            (*UserData::getInst().getGtdFixedCatMap().find(itr.first))
                  .second.c_str());
      const TCatTreeNodeVectPair& pair = itr;

      if (nodeNameStr == QString("In Basket"))
          {
          for(auto inBItr: pair.second.getChildren())
          {
            mp_inBasketForm->inBasketListWidget->addItem(
                  QString(inBItr.getMpNodeNameStr().c_str()));
          }
      }
      else
      {
         QList<QTreeWidgetItem*> gtdTreeList = mp_gtdTree->findItems(
               nodeNameStr, Qt::MatchExactly | Qt::MatchRecursive, 0);
         mp_gtdTree->AddNode(itr.second, itr.first);
      }
   }
   return true;
}

void InBasketForm::SetFocusInTextEdit()
{
   mp_inBasketForm->inBasketTextEdit->setFocus();
}

void InBasketForm::SetFocusInListWidget()
{
   mp_inBasketForm->inBasketListWidget->setFocus();
}

void InBasketForm::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton
        && mp_inBasketForm->inBasketListWidget->geometry().contains(event->pos())) {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

//        mimeData->setText(commentEdit->toPlainText());
        drag->setMimeData(mimeData);
//        drag->setPixmap(iconPixmap);

//        Qt::DropAction dropAction = drag->exec();
//        ...
    }
    else
    {
       QWidget::mousePressEvent(event);
    }
}

void InBasketForm::keyPressEvent(QKeyEvent *event)
{
   QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
   if((event->key() == Qt::Key_1) && (event->modifiers() == Qt::ALT))
   {
      SetFocusInTextEdit();
   }
   else if((event->key() == Qt::Key_2) && (event->modifiers() == Qt::ALT))
   {
       SetFocusInListWidget();
   }
}

void InBasketForm::dragEnterEvent(QDragEnterEvent *event)
{
   event->acceptProposedAction();
   QWidget::dragEnterEvent(event);
}

void InBasketForm::dragMoveEvent(QDragMoveEvent *event)
{
    QWidget::dragMoveEvent(event);
}

void InBasketForm::dragLeaveEvent(QDragLeaveEvent *event)
{
    QWidget::dragLeaveEvent(event);
}

void InBasketForm::dropEvent(QDropEvent *event)
{
    event->acceptProposedAction();
    QWidget::dropEvent(event);
}

void InBasketForm::on_inBasketTextEdit_textChanged()
{
   if (0 == mp_inBasketForm->inBasketTextEdit->toPlainText().size())
   {
      return;
   }
   QString text(mp_inBasketForm->inBasketTextEdit->toPlainText());
   if ('\n' == text[text.size() - 1])
   {
//      cout << "BEGIN InBasketForm::on_inBasketTextEdit_textChanged()" << endl;
//      mp_mainWindow->getUserData().DumpAllGTD();
      text.resize(text.size() - 1);
      // parse text & strip out all '\n's
      int start(0);
      int end(0);
      do
      {
         while ((text.size() > end) && ('\n' != text[end]))
         {
            ++end;
         }
         QString subtext;
         for (int i = start; i < end; ++i)
         {
            subtext[i - start] = text[i];
         }
         mp_inBasketForm->inBasketListWidget->addItem(subtext);
         UserData::getInst().AddStrToCategory(subtext.toStdString());
         start = ++end;
      } while (text.size() > end);
      mp_inBasketForm->inBasketTextEdit->selectAll();
      mp_inBasketForm->inBasketTextEdit->cut();
//      cout << "END InBasketForm::on_inBasketTextEdit_textChanged()" << endl;
//      mp_mainWindow->getUserData().DumpAllGTD();
   }
}

void InBasketForm::on_reEditSelectionButton_clicked()
{
   QList<QListWidgetItem*> itemSelectionList;
   GetSelectionOutOfGTDBasketList(itemSelectionList);
   QString editText;
   for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end();
         ++itr)
   {
      const QListWidgetItem* qwi = (*itr);
      if (itemSelectionList.begin() != itr)
      {
         editText.append("\n");
      }
      editText.append(qwi->text());
   }
   mp_inBasketForm->inBasketTextEdit->insertPlainText(editText);
}

void InBasketForm::on_somedayMaybeButton_clicked()
{
   MoveFromGTDBasketListToTree(QString("Someday Maybe"));
}

void InBasketForm::on_referenceButton_clicked()
{
   MoveFromGTDBasketListToTree(QString("Reference"));
}

void InBasketForm::on_trashButton_clicked()
{
   MoveFromGTDBasketListToTree(QString("Trash"));
}

void InBasketForm::on_doItButton_clicked()
{
   MoveFromGTDBasketListToTree(QString("Do It!"));
}

void InBasketForm::on_waitingOnSomeoneButton_clicked()
{
   MoveFromGTDBasketListToTree(QString("Waiting for Another Person"));
}

void InBasketForm::on_calendarButton_clicked()
{
   QList<QListWidgetItem*> itemList, removeItemList, tmpItemList;
   GetSelectionOutOfGTDBasketList(itemList, false);

   bool exit(false);
   while (!exit)
   {
      {
         KanbanCalendarDialog kbcalDlg;
         kbcalDlg.PopulateList(itemList);
         kbcalDlg.exec();

         switch (kbcalDlg.GetResult())
         {
         case kbcd_ScheduleNow:
         {
            // Ask for the date/time for each selected item
            QList<QListWidgetItem*> dlgItemSelectionList;
            kbcalDlg.GetSelectedItemsList(dlgItemSelectionList);
            for (auto itr = dlgItemSelectionList.begin();
                  dlgItemSelectionList.end() != itr; ++itr)
            {
               QMessageBox msgBox;
               msgBox.setWindowTitle("Schedule Item");
               const QDate date(kbcalDlg.GetSelectedDate());
               QString dateText(date.toString("MMM dd, yyyy"));
               QString text("\"");
               text.append((*itr)->text()).append("\" on ").append(dateText);
               QTime time;
               if (kbcalDlg.GetSelectedTime(time))
               {
                  text.append(" @ ").append(time.toString());
               }
               msgBox.setText(text);
               msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
               if (msgBox.exec() == QMessageBox::Yes)
               {
                  kbcalDlg.RemoveSelectedItem(*itr);
                  removeItemList.append(*itr);
               }
            }
            MoveFromListToTree(removeItemList, "Calendar");
            exit = (0 == kbcalDlg.GetListSize());
            break;
         }
         case kbcd_ScheduleLater:
            GetSelectionOutOfGTDBasketList(tmpItemList);
            MoveFromListToTree(itemList, "Calendar");
            exit = true;
            break;
         case kbcd_Cancel:
            exit = true;
            break;
         case kbcd_UNKNOWN:
            exit = true;
            break;
         }
      }
//      for (auto itr = removeItemList.begin(); removeItemList.end() != itr;
//            ++itr)
//      {
//         for (auto itr2 = itemList.begin(); itemList.end() != itr2; ++itr2)
//         {
//            if ((*itr)->text() == (*itr2)->text())
//            {
//               itemList.erase(itr2);
//               mp_ui->InBasketListWidget->takeItem(
//                     mp_ui->InBasketListWidget->row((*itr2)));
//               break;
//            }
//         }
//      }
   }
}

void InBasketForm::on_nextActionsButton_clicked()
{
   MoveFromGTDBasketListToTree(QString("Next Actions"));
}

void InBasketForm::on_projectsToPlanButton_clicked()
{
   MoveFromGTDBasketListToTree(QString("Projects-to-Plan"));
}

void InBasketForm::on_projectPlansButton_clicked()
{
   MoveFromGTDBasketListToTree(QString("Project Plans"));
}

void InBasketForm::on_gtdMinMaxButton_clicked()
{
   if (100 < height())
   {
      setFixedHeight(41);
      mp_inBasketForm->gtdMinMaxButton->setArrowType(Qt::DownArrow);
   }
   else
   {
      setFixedHeight(480);
      mp_inBasketForm->gtdMinMaxButton->setArrowType(Qt::UpArrow);
   }
}
