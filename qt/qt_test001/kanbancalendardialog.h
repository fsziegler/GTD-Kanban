#ifndef KANBANCALENDARDIALOG_H
#define KANBANCALENDARDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui
{
class KanbanCalendarDialog;
}

enum KanbanCalendarDialogResult
{
   kbcd_ScheduleNow,
   kbcd_ScheduleLater,
   kbcd_Cancel,
   kbcd_UNKNOWN,
};

class KanbanCalendarDialog: public QDialog
{
   Q_OBJECT

public:
   explicit KanbanCalendarDialog(QWidget *parent = 0);
   ~KanbanCalendarDialog();

   void PopulateList(const QList<QListWidgetItem*>& itemSelectionList);
   void GetSelectedItemsList(QList<QListWidgetItem*>& selectedItemsList) const;
   void RemoveSelectedItem(QListWidgetItem* itemToRemove);
   const QDate& GetSelectedDate() const;
   bool GetSelectedTime(QTime& time) const;
   KanbanCalendarDialogResult GetResult() const;

private slots:
   void on_scheduleNowButton_clicked();

   void on_scheduleLaterButton_clicked();

   void on_specifyTimeCheckBox_clicked();

private:
   Ui::KanbanCalendarDialog *ui;
   KanbanCalendarDialogResult m_rslt;
};

#endif // KANBANCALENDARDIALOG_H
