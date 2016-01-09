#include "inbasketform.h"
#include "ui_inbasketform.h"
#include "kanbancalendardialog.h"
#include <QMessageBox>
#include <QDate>
#include <QKeyEvent>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

InBasketForm::InBasketForm(QWidget *parent)
      : QWidget(parent),
        mp_ui(new Ui::InBasketForm),
        mp_gtdTree(nullptr)
{
   mp_ui->setupUi(this);
   mp_ui->inBasketListWidget->setSelectionMode(
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
//    Allen, David (2002-12-31). Getting Things Done: The Art of Stress-Free
//   Productivity (p. 34). Penguin Group. Kindle Edition.

   mp_ui->inBasketTextEdit->setText(inBasket);
   mp_ui->inBasketTextEdit->setAcceptDrops(true);
//    ui->inBasketTextEdit->set
//    m_gtdTree.setAcceptDrops(true);
//    m_gtdTree.setDragEnabled(true);
//    m_gtdTree.setDragDropMode(QTreeWidget::InternalMove);
   QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt,
         Qt::NoModifier);
   QCoreApplication::postEvent (this, event);
}

InBasketForm::~InBasketForm()
{
   delete mp_ui;
}

void InBasketForm::SetGTDTreeWidget(GTDTreeWidget* gtdTree)
{
   mp_gtdTree = gtdTree;
}

void InBasketForm::GetSelectionOutOfGTDBasketList(
      QList<QListWidgetItem*>& itemSelectionList, bool move)
{
   itemSelectionList = mp_ui->inBasketListWidget->selectedItems();
   if (move)
   {
      cout << "BEGIN InBasketForm::GetSelectionOutOfGTDBasketList()" << endl;
      m_userData.DumpAllGTD();
      for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end();
            ++itr)
      {
         // Store and pass back the row so it can be used to ID the node to move
         const QString rowStr((*itr)->text());
         const int row = mp_ui->inBasketListWidget->row((*itr));
         string stdRowStr;
         m_userData.ReadStrAtRow(EnumGTDCategory::kInBasket, row, stdRowStr);
         assert(stdRowStr == rowStr.toStdString());
         mp_ui->inBasketListWidget->takeItem(
               mp_ui->inBasketListWidget->row((*itr)));
         m_userData.MoveNthStrBetweenCategories(stdRowStr,
               EnumGTDCategory::kInBasket, EnumGTDCategory::kMoveQueue, row);
      }
      cout << "END InBasketForm::GetSelectionOutOfGTDBasketList()" << endl;
      m_userData.DumpAllGTD();
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
      static const QBrush b(QColor(255, 255, 128));
      qti->setBackground(0, b);
      gtdTreeItem->addChild(qti);
      if(mp_gtdTree->IsBranchCollapsed(nodeNameStr))
      {
          mp_gtdTree->collapseItem(gtdTreeItem);
      }
   }
   EnumGTDCategory tgtCat = m_userData.LookUpCategory(
         nodeNameStr.toStdString());
   m_userData.MoveAllBetweenCategories(EnumGTDCategory::kMoveQueue, tgtCat);
   cout << "END InBasketForm::MoveFromListToTree()" << endl;
   m_userData.DumpAllGTD();
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
    QList<QListWidgetItem*> itemSelectionList =
            mp_ui->inBasketListWidget->selectedItems();
    for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end();
          ++itr)
    {
       // Store and pass back the row so it can be used to ID the node to move
       const QString rowStr((*itr)->text());
       if(rowStr == itemNameStr)
       {
           const int row = mp_ui->inBasketListWidget->row((*itr));
           string stdRowStr;
           m_userData.ReadStrAtRow(EnumGTDCategory::kInBasket, row, stdRowStr);
           assert(stdRowStr == rowStr.toStdString());
           mp_ui->inBasketListWidget->takeItem(
                 mp_ui->inBasketListWidget->row((*itr)));
           m_userData.MoveNthStrBetweenCategories(stdRowStr,
                 EnumGTDCategory::kInBasket, EnumGTDCategory::kMoveQueue, row);
       }
    }
}

void InBasketForm::ClearWorkspace()
{
    mp_ui->inBasketTextEdit->clear();
    mp_ui->inBasketListWidget->clear();
}

void InBasketForm::on_inBasketTextEdit_textChanged()
{
   if (0 == mp_ui->inBasketTextEdit->toPlainText().size())
   {
      return;
   }
   QString text(mp_ui->inBasketTextEdit->toPlainText());
   if ('\n' == text[text.size() - 1])
   {
      cout << "BEGIN InBasketForm::on_inBasketTextEdit_textChanged()" << endl;
      m_userData.DumpAllGTD();
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
         mp_ui->inBasketListWidget->addItem(subtext);
         m_userData.AddStrToCategory(subtext.toStdString());
         start = ++end;
      } while (text.size() > end);
      mp_ui->inBasketTextEdit->selectAll();
      mp_ui->inBasketTextEdit->cut();
      cout << "END InBasketForm::on_inBasketTextEdit_textChanged()" << endl;
      m_userData.DumpAllGTD();
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
   mp_ui->inBasketTextEdit->insertPlainText(editText);
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
   MoveFromGTDBasketListToTree(QString("Waiting on someone"));
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
                  int size = kbcalDlg.GetListSize();
               }
            }
            MoveFromListToTree(removeItemList, "Calendar");
            int size = kbcalDlg.GetListSize();
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
      mp_ui->gtdMinMaxButton->setArrowType(Qt::DownArrow);
   }
   else
   {
      setFixedHeight(480);
      mp_ui->gtdMinMaxButton->setArrowType(Qt::UpArrow);
   }
}
