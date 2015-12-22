#include "inbasketform.h"
#include "ui_inbasketform.h"
#include <QMessageBox>
#include <set>
#include <vector>

InBasketForm::InBasketForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InBasketForm)
{
    ui->setupUi(this);
    ui->InBasketListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    // TEMPORARY FOR QUICK TESTING
    ui->inBasketTextEdit->setText(QString("doctor\nlawyer\ntinker\ntaylor\nsoldier spy"));
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
        // parse text & strip out all '\n's
        int start(0);
        int end(0);
        do
        {
            while((text.size() > end) && ('\n' != text[end]))
            {
                ++end;
            }
            QString subtext;
            for(int i=start; i < end; ++i)
            {
                subtext[i-start] = text[i];
            }
            ui->InBasketListWidget->addItem(subtext);
            start = ++end;
        } while(text.size() > end);
        ui->inBasketTextEdit->selectAll();
        ui->inBasketTextEdit->cut();
    }
}

void InBasketForm::on_NonActionableBtn_clicked()
{

}

void InBasketForm::on_somedayMaybeButton_clicked()
{

}

void InBasketForm::on_referenceButton_clicked()
{

}

void InBasketForm::on_trashButton_clicked()
{

}

void InBasketForm::on_ActionableBtn_clicked()
{

}

void InBasketForm::on_doItButton_clicked()
{

}

void InBasketForm::on_waitingOnSomeoneButton_clicked()
{

}

void InBasketForm::on_calendarButton_clicked()
{

}

void InBasketForm::on_nextActionsButton_clicked()
{

}

void InBasketForm::on_projectsToPlanButton_clicked()
{

}

void InBasketForm::on_projectPlansButton_clicked()
{

}

void InBasketForm::on_reEditSelectionButton_clicked()
{
    auto selection = ui->InBasketListWidget->selectedItems();
    QString editText;
    for (auto itr = selection.begin(); itr != selection.end(); ++itr)
    {
        const QListWidgetItem* qwi = (*itr);
        if(selection.begin() != itr)
        {
            editText.append("\n");
        }
        editText.append(qwi->text());
        ui->InBasketListWidget->takeItem(ui->InBasketListWidget->row(qwi));
    }
    ui->inBasketTextEdit->insertPlainText(editText);
}
