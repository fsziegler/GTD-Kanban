#include "inbasketform.h"
#include "ui_inbasketform.h"

InBasketForm::InBasketForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InBasketForm)
{
    ui->setupUi(this);
}

InBasketForm::~InBasketForm()
{
    delete ui;
}

void InBasketForm::on_nonActionableBtn_clicked()
{

}

void InBasketForm::on_actionableBtn_clicked()
{

}
