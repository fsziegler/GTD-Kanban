#include "inbasketform.h"
#include "ui_inbasketform.h"
#include <QMessageBox>

InBasketForm::InBasketForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InBasketForm)
{
    ui->setupUi(this);

//    QListWidget is created, call setSelectionMode() with one of the multiple selection types passed in, probably QAbstractItemView::ExtendedSelection
    ui->InBasketListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
        // parse text & strip out '\n'
        text.resize(text.size()-1);
        ui->InBasketListWidget->addItem(text);
        ui->inBasketTextEdit->selectAll();
        ui->inBasketTextEdit->cut();
    }
}

void InBasketForm::on_pushButton_10_clicked()
{
    QList<QListWidgetItem*> selection = ui->InBasketListWidget->selectedItems();
    QList<QListWidgetItem*>::iterator itr;
    for (itr = selection.begin(); itr != selection.end(); ++itr)
    {
        QListWidgetItem* qwi = (*itr);
        qwi->text();
        ui->inBasketTextEdit->insertPlainText((*itr)->text());
    }
}
