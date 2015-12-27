#include "inbasketform.h"
#include "ui_inbasketform.h"
#include "kanbancalendardialog.h"
#include <QMessageBox>
#include <QDate>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

InBasketForm::InBasketForm(QWidget *parent)
      : QWidget(parent),
        ui(new Ui::InBasketForm),
        mp_gtdTree(nullptr)
{
   ui->setupUi(this);
   ui->InBasketListWidget->setSelectionMode(
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

   ui->inBasketTextEdit->setText(inBasket);
   ui->inBasketTextEdit->setAcceptDrops(true);
//    ui->inBasketTextEdit->set
//    m_gtdTree.setAcceptDrops(true);
//    m_gtdTree.setDragEnabled(true);
//    m_gtdTree.setDragDropMode(QTreeWidget::InternalMove);
}

InBasketForm::~InBasketForm()
{
   delete ui;
}

void InBasketForm::SetGTDTreeWidget(QTreeWidget* gtdTree)
{
   mp_gtdTree = gtdTree;
}

void InBasketForm::GetSelectionOutOfGTDBasketList(
      QList<QListWidgetItem*>& itemSelectionList, bool move)
{
   itemSelectionList = ui->InBasketListWidget->selectedItems();
   if (move)
   {
      for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end();
            ++itr)
      {
         ui->InBasketListWidget->takeItem(ui->InBasketListWidget->row((*itr)));
      }
   }
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
   QTreeWidgetItem* gtdTreeItem = gtdTreeList.front();
   QList<QListWidgetItem*> itemSelectionList;
   GetSelectionOutOfGTDBasketList(itemSelectionList);
   for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end();
         ++itr)
   {
      QTreeWidgetItem* qti = new QTreeWidgetItem((QTreeWidget*) 0,
            QStringList((*itr)->text()));
      static const QBrush b(QColor(255, 255, 128));
      qti->setBackground(0, b);
      gtdTreeItem->addChild(qti);
   }
}

void InBasketForm::on_inBasketTextEdit_textChanged()
{
   if (0 == ui->inBasketTextEdit->toPlainText().size())
   {
      return;
   }
   QString text(ui->inBasketTextEdit->toPlainText());
   if ('\n' == text[text.size() - 1])
   {
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
         ui->InBasketListWidget->addItem(subtext);
         start = ++end;
      } while (text.size() > end);
      ui->inBasketTextEdit->selectAll();
      ui->inBasketTextEdit->cut();
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
   ui->inBasketTextEdit->insertPlainText(editText);
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
   QList<QListWidgetItem*> itemSelectionList;
   GetSelectionOutOfGTDBasketList(itemSelectionList, false);

   KanbanCalendarDialog kbcalDlg;
   kbcalDlg.PopulateList(itemSelectionList);
   kbcalDlg.exec();

   switch (kbcalDlg.GetResult())
   {
   case kbcd_ScheduleNow:
   {
      QList<QListWidgetItem*> dlgItemSelectionList;
      kbcalDlg.GetSelectedItemsList(dlgItemSelectionList);
      for (auto itr = dlgItemSelectionList.begin();
            dlgItemSelectionList.end() != itr; ++itr)
      {
         QMessageBox msgBox;
         msgBox.setWindowTitle("Schedule Item");
         const QDate date(kbcalDlg.GetSelectedDate());
//         QString dateText(date.toString("yyyy/MM/dd"));
         QString dateText(date.toString("MMM dd, yyyy"));
         cout << dateText.toStdString() << endl;
         QString text("\"");
         text.append((*itr)->text()).append("\" on ").append(dateText);
         QTime time;
         if(kbcalDlg.GetSelectedTime(time))
         {
            text.append(" @ ").append(time.toString());
         }
         msgBox.setText(text);
         msgBox.setStandardButtons(QMessageBox::Yes);
         msgBox.addButton(QMessageBox::No);
         msgBox.setDefaultButton(QMessageBox::No);
         if (msgBox.exec() == QMessageBox::Yes)
         {
            // do something
         }
         else
         {
            // do something else
         }
      }
   }
      break;
   case kbcd_ScheduleLater:
      MoveFromGTDBasketListToTree(QString("Calendar"));
      break;
   case kbcd_Cancel:
      break;
   case kbcd_UNKNOWN:
      break;
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
      setFixedHeight(40);
      ui->gtdMinMaxButton->setArrowType(Qt::DownArrow);
   }
   else
   {
      setFixedHeight(471);
      ui->gtdMinMaxButton->setArrowType(Qt::UpArrow);
   }
}
