/********************************************************************************
** Form generated from reading UI file 'exitdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXITDIALOG_H
#define UI_EXITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ExitDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *ExitDialog)
    {
        if (ExitDialog->objectName().isEmpty())
            ExitDialog->setObjectName(QStringLiteral("ExitDialog"));
        ExitDialog->resize(282, 120);
        ExitDialog->setContextMenuPolicy(Qt::PreventContextMenu);
        buttonBox = new QDialogButtonBox(ExitDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(60, 70, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::No|QDialogButtonBox::Yes);
        label = new QLabel(ExitDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 241, 31));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        retranslateUi(ExitDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExitDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExitDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExitDialog);
    } // setupUi

    void retranslateUi(QDialog *ExitDialog)
    {
        ExitDialog->setWindowTitle(QApplication::translate("ExitDialog", "Dialog", 0));
        label->setText(QApplication::translate("ExitDialog", "The file has changed since your last save.\n"
"Would you like to save before exiting?", 0));
    } // retranslateUi

};

namespace Ui {
    class ExitDialog: public Ui_ExitDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXITDIALOG_H
