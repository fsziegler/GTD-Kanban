/********************************************************************************
** Form generated from reading UI file 'kanbancalendardialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KANBANCALENDARDIALOG_H
#define UI_KANBANCALENDARDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_KanbanCalendarDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QListWidget *listWidget;
    QLabel *label_2;
    QPushButton *scheduleNowButton;
    QPushButton *scheduleLaterButton;
    QCalendarWidget *calendarWidget;
    QTimeEdit *timeEdit;
    QCheckBox *specifyTimeCheckBox;

    void setupUi(QDialog *KanbanCalendarDialog)
    {
        if (KanbanCalendarDialog->objectName().isEmpty())
            KanbanCalendarDialog->setObjectName(QStringLiteral("KanbanCalendarDialog"));
        KanbanCalendarDialog->resize(401, 410);
        KanbanCalendarDialog->setAcceptDrops(true);
        buttonBox = new QDialogButtonBox(KanbanCalendarDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(279, 376, 81, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
        label = new QLabel(KanbanCalendarDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 170, 241, 41));
        label->setWordWrap(true);
        listWidget = new QListWidget(KanbanCalendarDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 210, 241, 192));
        listWidget->setFocusPolicy(Qt::StrongFocus);
        listWidget->setAlternatingRowColors(true);
        listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        label_2 = new QLabel(KanbanCalendarDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 250, 131, 41));
        label_2->setWordWrap(true);
        scheduleNowButton = new QPushButton(KanbanCalendarDialog);
        scheduleNowButton->setObjectName(QStringLiteral("scheduleNowButton"));
        scheduleNowButton->setGeometry(QRect(270, 300, 101, 23));
        scheduleLaterButton = new QPushButton(KanbanCalendarDialog);
        scheduleLaterButton->setObjectName(QStringLiteral("scheduleLaterButton"));
        scheduleLaterButton->setGeometry(QRect(270, 340, 101, 23));
        calendarWidget = new QCalendarWidget(KanbanCalendarDialog);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setGeometry(QRect(10, 10, 381, 161));
        timeEdit = new QTimeEdit(KanbanCalendarDialog);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setGeometry(QRect(260, 220, 118, 24));
        specifyTimeCheckBox = new QCheckBox(KanbanCalendarDialog);
        specifyTimeCheckBox->setObjectName(QStringLiteral("specifyTimeCheckBox"));
        specifyTimeCheckBox->setGeometry(QRect(260, 190, 101, 21));
        QWidget::setTabOrder(calendarWidget, listWidget);
        QWidget::setTabOrder(listWidget, specifyTimeCheckBox);
        QWidget::setTabOrder(specifyTimeCheckBox, timeEdit);
        QWidget::setTabOrder(timeEdit, scheduleNowButton);
        QWidget::setTabOrder(scheduleNowButton, scheduleLaterButton);

        retranslateUi(KanbanCalendarDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), KanbanCalendarDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), KanbanCalendarDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(KanbanCalendarDialog);
    } // setupUi

    void retranslateUi(QDialog *KanbanCalendarDialog)
    {
        KanbanCalendarDialog->setWindowTitle(QApplication::translate("KanbanCalendarDialog", "Dialog", 0));
        label->setText(QApplication::translate("KanbanCalendarDialog", "You may move your calendar items into the GTD Calendar list, or schedule them now", 0));
        label_2->setText(QApplication::translate("KanbanCalendarDialog", "Select items and choose an action below", 0));
        scheduleNowButton->setText(QApplication::translate("KanbanCalendarDialog", "Schedule &now", 0));
        scheduleLaterButton->setText(QApplication::translate("KanbanCalendarDialog", "Schedule &later", 0));
        specifyTimeCheckBox->setText(QApplication::translate("KanbanCalendarDialog", "Specify &time?", 0));
    } // retranslateUi

};

namespace Ui {
    class KanbanCalendarDialog: public Ui_KanbanCalendarDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KANBANCALENDARDIALOG_H
