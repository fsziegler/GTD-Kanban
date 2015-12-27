#include "kanbancalendardialog.h"
#include "ui_kanbancalendardialog.h"
#include<iostream>

using namespace std;

KanbanCalendarDialog::KanbanCalendarDialog(QWidget *parent)
      : QDialog(parent),
        ui(new Ui::KanbanCalendarDialog),
        m_rslt(kbcd_Cancel)
{
   ui->setupUi(this);
   ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
   ui->timeEdit->setEnabled(false);
}

KanbanCalendarDialog::~KanbanCalendarDialog()
{
   delete ui;
}

void KanbanCalendarDialog::PopulateList(
      const QList<QListWidgetItem*>& itemSelectionList)
{
   for (auto itr = itemSelectionList.begin(); itemSelectionList.end() != itr;
         ++itr)
   {
      ui->listWidget->addItem((*itr)->text());
   }
}

void KanbanCalendarDialog::GetSelectedItemsList(
        QList<QListWidgetItem*>& selectedItemsList) const
{
   selectedItemsList = ui->listWidget->selectedItems();
}

const QDate& KanbanCalendarDialog::GetSelectedDate() const
{
    return ui->calendarWidget->selectedDate();
}

bool KanbanCalendarDialog::GetSelectedTime(QTime& time) const
{
    if(ui->specifyTimeCheckBox->isChecked())
    {
        time = ui->timeEdit->time();
        return true;
    }
    return false;
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

void KanbanCalendarDialog::on_specifyTimeCheckBox_clicked()
{
    ui->timeEdit->setEnabled(ui->specifyTimeCheckBox->isChecked());
}
