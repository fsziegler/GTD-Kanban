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

private:
    Ui::InBasketForm *ui;
};

#endif // INBASKETFORM_H
