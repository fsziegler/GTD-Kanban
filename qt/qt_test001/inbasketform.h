#ifndef INBASKETFORM_H
#define INBASKETFORM_H

#include "../../code/UserData.h"
#include "gtdtreewidget.h"
#include <QWidget>
#include <QTreeWidget>
#include <QListWidgetItem>

using namespace ZiegGTDKanban;

namespace Ui
{
class InBasketForm;
}
class MainWindow;

class InBasketForm: public QWidget
{
   Q_OBJECT

public:
   explicit InBasketForm(MainWindow* parent = 0);
   ~InBasketForm();

   void SetGTDTreeWidget(GTDTreeWidget* gtdTree);
   // GetSelectionOutOfGTDBasketList() copies all selected items from
   // InBasketListWidget into itemSelectionList and, iff move is true, moves
   // them into the move queue.
   void GetSelectionOutOfGTDBasketList(
         QList<QListWidgetItem*>& itemSelectionList, bool move = true);
   void MoveFromListToTree(QList<QListWidgetItem*> itemSelectionList,
         const QString& nodeNameStr);
   void MoveFromGTDBasketListToTree(const QString& nodeNameStr);
   void MoveFromGTDBasketListToTree(const QString& itemNameStr,
                                    const QString& nodeNameStr);
   void ClearWorkspace();
   bool LoadFromFile(const QString& jsonFileName);

   UserData& GetUserData();

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
   Ui::InBasketForm* mp_inBasketForm;
   MainWindow*       mp_mainWindow;
   GTDTreeWidget*    mp_gtdTree;
};

#endif // INBASKETFORM_H
