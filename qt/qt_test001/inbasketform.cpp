#include "inbasketform.h"
#include "ui_inbasketform.h"
#include <QMessageBox>
#include <set>
#include <vector>

InBasketForm::InBasketForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InBasketForm),
    mp_gtdTree(nullptr)
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

void InBasketForm::SetGTDTreeWidget(QTreeWidget* gtdTree)
{
    mp_gtdTree = gtdTree;
}

void InBasketForm::GetSelectionOutOfGTDBasketList(QList<QListWidgetItem*>& itemSelectionList)
{
    itemSelectionList = ui->InBasketListWidget->selectedItems();
    for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end(); ++itr)
    {
        ui->InBasketListWidget->takeItem(ui->InBasketListWidget->row((*itr)));
    }
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

void InBasketForm::on_reEditSelectionButton_clicked()
{
    QList<QListWidgetItem*> itemSelectionList;
    GetSelectionOutOfGTDBasketList(itemSelectionList);
    QString editText;
    for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end(); ++itr)
    {
        const QListWidgetItem* qwi = (*itr);
        if(itemSelectionList.begin() != itr)
        {
            editText.append("\n");
        }
        editText.append(qwi->text());
    }
    ui->inBasketTextEdit->insertPlainText(editText);
}

void InBasketForm::on_somedayMaybeButton_clicked()
{
    if(nullptr == mp_gtdTree)
    {
        return;
    }
    QList<QTreeWidgetItem*> list = mp_gtdTree->findItems(QString("Someday Maybe"), Qt::MatchExactly|Qt::MatchRecursive, 0);
    if(0 == list.size())
    {
        QMessageBox msg(QMessageBox::Warning, "Error:", "Someday Maybe not found!", QMessageBox::Ok);
        msg.exec();
        return;
    }
    QTreeWidgetItem* nonActTree = list.front();

    QList<QListWidgetItem*> itemSelectionList;
    GetSelectionOutOfGTDBasketList(itemSelectionList);
    for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end(); ++itr)
    {
        const QListWidgetItem* qwi = (*itr);
        nonActTree->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(qwi->text())));
    }
}

void InBasketForm::on_referenceButton_clicked()
{

}

void InBasketForm::on_trashButton_clicked()
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
