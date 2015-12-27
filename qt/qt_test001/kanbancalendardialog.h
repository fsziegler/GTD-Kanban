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
   KanbanCalendarDialogResult GetResult() const;
private slots:
   void on_scheduleNowButton_clicked();

   void on_scheduleLaterButton_clicked();

private:
   Ui::KanbanCalendarDialog *ui;
   KanbanCalendarDialogResult m_rslt;
};

#endif // KANBANCALENDARDIALOG_H
