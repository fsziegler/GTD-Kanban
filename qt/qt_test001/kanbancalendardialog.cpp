#include "kanbancalendardialog.h"
#include "ui_kanbancalendardialog.h"

KanbanCalendarDialog::KanbanCalendarDialog(QWidget *parent)
      : QDialog(parent),
        ui(new Ui::KanbanCalendarDialog),
        m_rslt(kbcd_Cancel)
{
   ui->setupUi(this);
}

KanbanCalendarDialog::~KanbanCalendarDialog()
{
   delete ui;
}

void KanbanCalendarDialog::PopulateList(
        const QList<QListWidgetItem*>& itemSelectionList)
{
    for(auto itr = itemSelectionList.begin(); itemSelectionList.end() != itr;
        ++itr)
    {
        ui->listWidget->addItem((*itr)->text());
    }
}

KanbanCalendarDialogResult KanbanCalendarDialog::GetResult() const
{
   return m_rslt;
}

void KanbanCalendarDialog::on_scheduleNowButton_clicked()
{
   m_rslt = kbcd_ScheduleNow;
   done(kbcd_ScheduleNow);
}

void KanbanCalendarDialog::on_scheduleLaterButton_clicked()
{
   m_rslt = kbcd_ScheduleLater;
   done(kbcd_ScheduleLater);
}
