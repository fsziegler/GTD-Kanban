#include "inbasketform.h"
#include "ui_inbasketform.h"
#include <QMessageBox>

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

void InBasketForm::on_inBasketTextEdit_textChanged()
{
    if(0 == ui->inBasketTextEdit->toPlainText().size())
    {
        return;
    }
    QString text(ui->inBasketTextEdit->toPlainText());
    if('\n' == text[text.size()-1])
    {
        text.resize(text.size()-1);
        ui->InBasketListWidget->addItem(text);
        ui->inBasketTextEdit->selectAll();
        ui->inBasketTextEdit->cut();
    }
}
