#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>

namespace Ui {
class ExitDialog;
}

class ExitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExitDialog(QWidget *parent = 0);
    ~ExitDialog();

    QDialogButtonBox::StandardButton ReadButton() const;

public Q_SLOTS:
protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_yes_clicked();
    void on_no_clicked();

private:
    Ui::ExitDialog *ui;
    QAbstractButton* mp_yesButton;
    QAbstractButton* mp_noButton;
    QDialogButtonBox::StandardButton m_btn;
};

#endif // EXITDIALOG_H
