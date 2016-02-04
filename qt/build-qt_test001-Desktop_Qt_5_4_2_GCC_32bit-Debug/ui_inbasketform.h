/********************************************************************************
** Form generated from reading UI file 'inbasketform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INBASKETFORM_H
#define UI_INBASKETFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <gtdlistwidget.h>
#include "gtdtextedit.h"

QT_BEGIN_NAMESPACE

class Ui_InBasketForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *somedayMaybeButton;
    QPushButton *referenceButton;
    QPushButton *trashButton;
    QPushButton *waitingOnSomeoneButton;
    QPushButton *calendarButton;
    QPushButton *projectsToPlanButton;
    QPushButton *projectPlansButton;
    QPushButton *nextActionsButton;
    GTDListWidget *inBasketListWidget;
    GTDTextEdit *inBasketTextEdit;
    QLabel *label_3;
    QPushButton *reEditSelectionButton;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGroupBox *tasksGroupBox;
    QPushButton *doItButton;
    QGroupBox *ProjectsGroupBox;
    QToolButton *gtdMinMaxButton;
    QLabel *label_4;

    void setupUi(QWidget *InBasketForm)
    {
        if (InBasketForm->objectName().isEmpty())
            InBasketForm->setObjectName(QStringLiteral("InBasketForm"));
        InBasketForm->resize(510, 501);
        InBasketForm->setFocusPolicy(Qt::ClickFocus);
        InBasketForm->setAcceptDrops(true);
        label = new QLabel(InBasketForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 261, 32));
        label->setWordWrap(true);
        label_2 = new QLabel(InBasketForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 127, 271, 48));
        label_2->setWordWrap(true);
        somedayMaybeButton = new QPushButton(InBasketForm);
        somedayMaybeButton->setObjectName(QStringLiteral("somedayMaybeButton"));
        somedayMaybeButton->setGeometry(QRect(330, 70, 141, 23));
        referenceButton = new QPushButton(InBasketForm);
        referenceButton->setObjectName(QStringLiteral("referenceButton"));
        referenceButton->setGeometry(QRect(330, 100, 141, 23));
        trashButton = new QPushButton(InBasketForm);
        trashButton->setObjectName(QStringLiteral("trashButton"));
        trashButton->setGeometry(QRect(330, 130, 141, 23));
        waitingOnSomeoneButton = new QPushButton(InBasketForm);
        waitingOnSomeoneButton->setObjectName(QStringLiteral("waitingOnSomeoneButton"));
        waitingOnSomeoneButton->setGeometry(QRect(330, 260, 141, 41));
        calendarButton = new QPushButton(InBasketForm);
        calendarButton->setObjectName(QStringLiteral("calendarButton"));
        calendarButton->setGeometry(QRect(330, 310, 141, 23));
        projectsToPlanButton = new QPushButton(InBasketForm);
        projectsToPlanButton->setObjectName(QStringLiteral("projectsToPlanButton"));
        projectsToPlanButton->setGeometry(QRect(330, 410, 141, 23));
        projectPlansButton = new QPushButton(InBasketForm);
        projectPlansButton->setObjectName(QStringLiteral("projectPlansButton"));
        projectPlansButton->setGeometry(QRect(330, 440, 141, 23));
        nextActionsButton = new QPushButton(InBasketForm);
        nextActionsButton->setObjectName(QStringLiteral("nextActionsButton"));
        nextActionsButton->setGeometry(QRect(330, 340, 141, 23));
        inBasketListWidget = new GTDListWidget(InBasketForm);
        inBasketListWidget->setObjectName(QStringLiteral("inBasketListWidget"));
        inBasketListWidget->setGeometry(QRect(20, 260, 271, 221));
        inBasketListWidget->setFocusPolicy(Qt::StrongFocus);
        inBasketListWidget->setAcceptDrops(false);
        inBasketListWidget->setAlternatingRowColors(true);
        inBasketListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        inBasketTextEdit = new GTDTextEdit(InBasketForm);
        inBasketTextEdit->setObjectName(QStringLiteral("inBasketTextEdit"));
        inBasketTextEdit->setGeometry(QRect(20, 50, 271, 70));
        inBasketTextEdit->setFocusPolicy(Qt::StrongFocus);
        inBasketTextEdit->setTabChangesFocus(true);
        label_3 = new QLabel(InBasketForm);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 180, 271, 49));
        label_3->setWordWrap(true);
        reEditSelectionButton = new QPushButton(InBasketForm);
        reEditSelectionButton->setObjectName(QStringLiteral("reEditSelectionButton"));
        reEditSelectionButton->setGeometry(QRect(160, 230, 131, 23));
        reEditSelectionButton->setBaseSize(QSize(0, 0));
        groupBox = new QGroupBox(InBasketForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(310, 40, 181, 121));
        groupBox_2 = new QGroupBox(InBasketForm);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(310, 170, 181, 311));
        tasksGroupBox = new QGroupBox(groupBox_2);
        tasksGroupBox->setObjectName(QStringLiteral("tasksGroupBox"));
        tasksGroupBox->setGeometry(QRect(10, 30, 161, 171));
        doItButton = new QPushButton(InBasketForm);
        doItButton->setObjectName(QStringLiteral("doItButton"));
        doItButton->setGeometry(QRect(330, 230, 141, 23));
        ProjectsGroupBox = new QGroupBox(InBasketForm);
        ProjectsGroupBox->setObjectName(QStringLiteral("ProjectsGroupBox"));
        ProjectsGroupBox->setGeometry(QRect(320, 380, 161, 91));
        gtdMinMaxButton = new QToolButton(InBasketForm);
        gtdMinMaxButton->setObjectName(QStringLiteral("gtdMinMaxButton"));
        gtdMinMaxButton->setGeometry(QRect(470, 10, 23, 22));
        gtdMinMaxButton->setArrowType(Qt::UpArrow);
        label_4 = new QLabel(InBasketForm);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(413, 14, 54, 15));
        groupBox_2->raise();
        groupBox->raise();
        ProjectsGroupBox->raise();
        label->raise();
        label_2->raise();
        somedayMaybeButton->raise();
        referenceButton->raise();
        trashButton->raise();
        waitingOnSomeoneButton->raise();
        calendarButton->raise();
        projectsToPlanButton->raise();
        projectPlansButton->raise();
        nextActionsButton->raise();
        inBasketListWidget->raise();
        inBasketTextEdit->raise();
        label_3->raise();
        reEditSelectionButton->raise();
        doItButton->raise();
        gtdMinMaxButton->raise();
        label_4->raise();
        QWidget::setTabOrder(inBasketTextEdit, reEditSelectionButton);
        QWidget::setTabOrder(reEditSelectionButton, inBasketListWidget);
        QWidget::setTabOrder(inBasketListWidget, somedayMaybeButton);
        QWidget::setTabOrder(somedayMaybeButton, referenceButton);
        QWidget::setTabOrder(referenceButton, trashButton);
        QWidget::setTabOrder(trashButton, doItButton);
        QWidget::setTabOrder(doItButton, waitingOnSomeoneButton);
        QWidget::setTabOrder(waitingOnSomeoneButton, calendarButton);
        QWidget::setTabOrder(calendarButton, nextActionsButton);
        QWidget::setTabOrder(nextActionsButton, projectsToPlanButton);
        QWidget::setTabOrder(projectsToPlanButton, projectPlansButton);

        retranslateUi(InBasketForm);

        QMetaObject::connectSlotsByName(InBasketForm);
    } // setupUi

    void retranslateUi(QWidget *InBasketForm)
    {
        InBasketForm->setWindowTitle(QApplication::translate("InBasketForm", "Form", 0));
        label->setText(QApplication::translate("InBasketForm", "<u>1</u>. GTD In Basket - Start by entering issues here, separated by carriage return (<Enter>)", 0));
        label_2->setText(QApplication::translate("InBasketForm", "Text entered in the edit box above will automatically move to the list box below, where you can select and act upon it.", 0));
#ifndef QT_NO_TOOLTIP
        somedayMaybeButton->setToolTip(QApplication::translate("InBasketForm", "Tickler file; hold for review", 0));
#endif // QT_NO_TOOLTIP
        somedayMaybeButton->setText(QApplication::translate("InBasketForm", "Someday Ma&ybe", 0));
#ifndef QT_NO_TOOLTIP
        referenceButton->setToolTip(QApplication::translate("InBasketForm", "Retrievable when required", 0));
#endif // QT_NO_TOOLTIP
        referenceButton->setText(QApplication::translate("InBasketForm", "&Reference", 0));
#ifndef QT_NO_TOOLTIP
        trashButton->setToolTip(QApplication::translate("InBasketForm", "Throw this away!", 0));
#endif // QT_NO_TOOLTIP
        trashButton->setText(QApplication::translate("InBasketForm", "Trash(&X)", 0));
#ifndef QT_NO_TOOLTIP
        waitingOnSomeoneButton->setToolTip(QApplication::translate("InBasketForm", "You have or will delegate this to someone else", 0));
#endif // QT_NO_TOOLTIP
        waitingOnSomeoneButton->setText(QApplication::translate("InBasketForm", "&Waiting for \n"
"Another Person", 0));
#ifndef QT_NO_TOOLTIP
        calendarButton->setToolTip(QApplication::translate("InBasketForm", "You will do this at a specific time", 0));
#endif // QT_NO_TOOLTIP
        calendarButton->setText(QApplication::translate("InBasketForm", "&Calendar", 0));
#ifndef QT_NO_TOOLTIP
        projectsToPlanButton->setToolTip(QApplication::translate("InBasketForm", "You need to plan this project before taking action", 0));
#endif // QT_NO_TOOLTIP
        projectsToPlanButton->setText(QApplication::translate("InBasketForm", "Pro&jects-to-Plan", 0));
#ifndef QT_NO_TOOLTIP
        projectPlansButton->setToolTip(QApplication::translate("InBasketForm", "You need to review this plan for Next Actions", 0));
#endif // QT_NO_TOOLTIP
        projectPlansButton->setText(QApplication::translate("InBasketForm", "Project &Plans", 0));
#ifndef QT_NO_TOOLTIP
        nextActionsButton->setToolTip(QApplication::translate("InBasketForm", "This is one of your next actions", 0));
#endif // QT_NO_TOOLTIP
        nextActionsButton->setText(QApplication::translate("InBasketForm", "Next &Actions", 0));
        label_3->setText(QApplication::translate("InBasketForm", "<u>2</u>. Highlight one or more issues below (you can use the Ctrl key to select more than one) and choose an action on the right.", 0));
#ifndef QT_NO_TOOLTIP
        reEditSelectionButton->setToolTip(QApplication::translate("InBasketForm", "Move selected issue below to In-Basket for editing", 0));
#endif // QT_NO_TOOLTIP
        reEditSelectionButton->setText(QApplication::translate("InBasketForm", "Re-edit &Selection", 0));
        groupBox->setTitle(QApplication::translate("InBasketForm", "Non-Actionable", 0));
        groupBox_2->setTitle(QApplication::translate("InBasketForm", "Actionable", 0));
        tasksGroupBox->setTitle(QApplication::translate("InBasketForm", "Tasks", 0));
#ifndef QT_NO_TOOLTIP
        doItButton->setToolTip(QApplication::translate("InBasketForm", "You can take care of this right now", 0));
#endif // QT_NO_TOOLTIP
        doItButton->setText(QApplication::translate("InBasketForm", "&Do It!", 0));
        ProjectsGroupBox->setTitle(QApplication::translate("InBasketForm", "Projects", 0));
        gtdMinMaxButton->setText(QApplication::translate("InBasketForm", "...", 0));
        label_4->setText(QApplication::translate("InBasketForm", "<u>M</u>in/Max", 0));
    } // retranslateUi

};

namespace Ui {
    class InBasketForm: public Ui_InBasketForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INBASKETFORM_H
