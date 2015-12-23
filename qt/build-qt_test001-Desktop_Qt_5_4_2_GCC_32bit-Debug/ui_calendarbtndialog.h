/********************************************************************************
** Form generated from reading UI file 'calendarbtndialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDARBTNDIALOG_H
#define UI_CALENDARBTNDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GTDCalendarDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *GTDCalendarDialog)
    {
        if (GTDCalendarDialog->objectName().isEmpty())
            GTDCalendarDialog->setObjectName(QStringLiteral("GTDCalendarDialog"));
        GTDCalendarDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(GTDCalendarDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(290, 176, 71, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
        listWidget = new QListWidget(GTDCalendarDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 40, 256, 251));
        label = new QLabel(GTDCalendarDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 261, 41));
        label->setWordWrap(true);
        label_2 = new QLabel(GTDCalendarDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 40, 111, 41));
        label_2->setWordWrap(true);
        pushButton = new QPushButton(GTDCalendarDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(280, 100, 101, 23));
        pushButton_2 = new QPushButton(GTDCalendarDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(280, 140, 101, 23));
        QWidget::setTabOrder(listWidget, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);

        retranslateUi(GTDCalendarDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GTDCalendarDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GTDCalendarDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GTDCalendarDialog);
    } // setupUi

    void retranslateUi(QDialog *GTDCalendarDialog)
    {
        GTDCalendarDialog->setWindowTitle(QApplication::translate("GTDCalendarDialog", "Dialog", 0));
        label->setText(QApplication::translate("GTDCalendarDialog", "You may move your calendar items into the GTD Calendar list, or schedule them now", 0));
        label_2->setText(QApplication::translate("GTDCalendarDialog", "Select items and choose an action below", 0));
        pushButton->setText(QApplication::translate("GTDCalendarDialog", "Schedule now", 0));
        pushButton_2->setText(QApplication::translate("GTDCalendarDialog", "Schedule later", 0));
    } // retranslateUi

};

namespace Ui {
    class GTDCalendarDialog: public Ui_GTDCalendarDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDARBTNDIALOG_H
