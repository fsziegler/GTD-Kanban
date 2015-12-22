#ifndef INBASKETFORM_H
#define INBASKETFORM_H

#include <QWidget>

namespace Ui {
class InBasketForm;
}

class InBasketForm : public QWidget
{
    Q_OBJECT

public:
    explicit InBasketForm(QWidget *parent = 0);
    ~InBasketForm();

private slots:
    void on_nonActionableBtn_clicked();

    void on_actionableBtn_clicked();

    void on_inBasketTextEdit_textChanged();

    void on_NonActionableBtn_clicked();

    void on_somedayMaybeButton_clicked();

    void on_referenceButton_clicked();

    void on_trashButton_clicked();

    void on_ActionableBtn_clicked();

    void on_doItButton_clicked();

    void on_waitingOnSomeoneButton_clicked();

    void on_calendarButton_clicked();

    void on_nextActionsButton_clicked();

    void on_projectsToPlanButton_clicked();

    void on_projectPlansButton_clicked();

    void on_reEditSelectionButton_clicked();

private:
    Ui::InBasketForm *ui;
};

#endif // INBASKETFORM_H
