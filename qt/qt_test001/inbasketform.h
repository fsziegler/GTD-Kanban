#ifndef INBASKETFORM_H
#define INBASKETFORM_H

#include <QWidget>
#include <QTreeWidget>
#include <QListWidgetItem>

namespace Ui
{
class InBasketForm;
}

class InBasketForm: public QWidget
{
   Q_OBJECT

public:
   explicit InBasketForm(QWidget *parent = 0);
   ~InBasketForm();

   void SetGTDTreeWidget(QTreeWidget* gtdTree);
   void GetSelectionOutOfGTDBasketList(
         QList<QListWidgetItem*>& itemSelectionList, bool move = true);
   void MoveFromGTDBasketListToTree(const QString& nodeNameStr);

private slots:
   void on_inBasketTextEdit_textChanged();

   void on_reEditSelectionButton_clicked();

   void on_somedayMaybeButton_clicked();

   void on_referenceButton_clicked();

   void on_trashButton_clicked();

   void on_doItButton_clicked();

   void on_waitingOnSomeoneButton_clicked();

   void on_calendarButton_clicked();

   void on_nextActionsButton_clicked();

   void on_projectsToPlanButton_clicked();

   void on_projectPlansButton_clicked();

   void on_gtdMinMaxButton_clicked();

private:
   Ui::InBasketForm *ui;
   QTreeWidget* mp_gtdTree;
};

#endif // INBASKETFORM_H
