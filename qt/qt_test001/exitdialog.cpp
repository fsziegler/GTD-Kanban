#include "exitdialog.h"
#include "ui_exitdialog.h"
#include <QMessageBox>
#include <QKeyEvent>

ExitDialog::ExitDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::ExitDialog),
   m_btn(QDialogButtonBox::NoButton)
{
   ui->setupUi(this);
   mp_yesButton
      = (QAbstractButton*)ui->buttonBox->button(QDialogButtonBox::Yes);
   mp_noButton
      = (QAbstractButton*)ui->buttonBox->button(QDialogButtonBox::No);
   connect(mp_yesButton,
           SIGNAL(released()),
           this,
           SLOT(on_yes_clicked()));
   connect(mp_noButton,
           SIGNAL(released()),
           this,
           SLOT(on_no_clicked()));
}

ExitDialog::~ExitDialog()
{
   delete ui;
}

QDialogButtonBox::StandardButton ExitDialog::ReadButton() const
{
   return m_btn;
}

void ExitDialog::SetLabelText(const QString& newText)
{
   ui->label->setText(newText);
}

void ExitDialog::keyPressEvent(QKeyEvent *event)
{
   if ((event->type() == QEvent::KeyPress)
         && event->key())
   {
      const QString str = event->text();
      if(("Y" == str) || ("y" == str))
      {
         on_yes_clicked();
         QDialog::close();
      }
      else if(("N" == str) || (QString("n") == str))
      {
         on_no_clicked();
         QDialog::close();
      }
   }
   QDialog::keyPressEvent(event);
}

void ExitDialog::on_yes_clicked()
{
   m_btn = QDialogButtonBox::Yes;
}

void ExitDialog::on_no_clicked()
{
   m_btn = QDialogButtonBox::No;
}
