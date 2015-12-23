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
    QString inBasket("Call Fred re tel. # for the garage he recommended.\nDraft"
                     " thoughts for the budget-meeting agenda.\nTalk to Angela "
                     "about the filing system we need to set up.\nResearch "
                     "database-management software on the Web.\nGet new staff "
                     "person on board August\nvacation Staff off-site retreat\n"
                     "Publish book\nFinalize computer upgrades\nUpdate will\n"
                     "Finalize budgets\nFinalize new product line\nGet "
                     "comfortable with new contact-management software\nGet "
                     "reprints of Fortune article\nGet a publicist\nFinish new "
                     "orchard planting\nR&D joint-venture video project\n"
                     "Produce new training compact disk\nEstablish next year’s "
                     "seminar schedule\nOrchestrate a one-hour keynote "
                     "presentation\nGet proficient with videoconferencing "
                     "access\nFinalize employment agreements\nInstall new "
                     "backyard lights");
//    Allen, David (2002-12-31). Getting Things Done: The Art of Stress-Free Productivity (p. 34). Penguin Group. Kindle Edition.

    ui->inBasketTextEdit->setText(inBasket);
    ui->inBasketTextEdit->setAcceptDrops(true);
//    ui->inBasketTextEdit->set
//    m_gtdTree.setAcceptDrops(true);
//    m_gtdTree.setDragEnabled(true);
//    m_gtdTree.setDragDropMode(QTreeWidget::InternalMove);
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

void InBasketForm::MoveFromGTDBasketListToTree(const QString& nodeNameStr)
{
    if(nullptr == mp_gtdTree)
    {
        return;
    }
    QList<QTreeWidgetItem*> list = mp_gtdTree->findItems(nodeNameStr, Qt::MatchExactly|Qt::MatchRecursive, 0);
    if(0 == list.size())
    {
        QString errMsg(nodeNameStr);
        errMsg.append(QString(" not found!"));
        QMessageBox msg(QMessageBox::Warning, "Error:", errMsg, QMessageBox::Ok);
        msg.exec();
        return;
    }
    QTreeWidgetItem* nonActTree = list.front();

    QList<QListWidgetItem*> itemSelectionList;
    GetSelectionOutOfGTDBasketList(itemSelectionList);
    for (auto itr = itemSelectionList.begin(); itr != itemSelectionList.end(); ++itr)
    {
        QListWidgetItem* qwi = (*itr);
        qwi->setTextColor(QColor(255,64,64));
        qwi->setBackgroundColor(QColor(32,32,32));
        nonActTree->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(qwi->text())));
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
    MoveFromGTDBasketListToTree(QString("Someday Maybe"));
}

void InBasketForm::on_referenceButton_clicked()
{
    MoveFromGTDBasketListToTree(QString("Reference"));
}

void InBasketForm::on_trashButton_clicked()
{
    MoveFromGTDBasketListToTree(QString("Trash"));
}

void InBasketForm::on_doItButton_clicked()
{
    MoveFromGTDBasketListToTree(QString("Do It!"));
}

void InBasketForm::on_waitingOnSomeoneButton_clicked()
{
    MoveFromGTDBasketListToTree(QString("Waiting on someone"));
}

void InBasketForm::on_calendarButton_clicked()
{
    MoveFromGTDBasketListToTree(QString("Calendar"));
}

void InBasketForm::on_nextActionsButton_clicked()
{
    MoveFromGTDBasketListToTree(QString("Next Actions"));
}

void InBasketForm::on_projectsToPlanButton_clicked()
{
    MoveFromGTDBasketListToTree(QString("Projects-to-Plan"));
}

void InBasketForm::on_projectPlansButton_clicked()
{
    MoveFromGTDBasketListToTree(QString("Project Plans"));
}

void InBasketForm::on_gtdMinMaxButton_clicked()
{
    if(100 < height())
    {
        setFixedHeight(40);
        ui->gtdMinMaxButton->setArrowType(Qt::DownArrow);
    }
    else
    {
        setFixedHeight(471);
        ui->gtdMinMaxButton->setArrowType(Qt::UpArrow);
    }
}
