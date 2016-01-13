/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_8;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_6;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QStringLiteral("AboutDialog"));
        AboutDialog->resize(400, 341);
        buttonBox = new QDialogButtonBox(AboutDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(160, 290, 81, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        label = new QLabel(AboutDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 361, 41));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(AboutDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 260, 361, 21));
        label_8->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(AboutDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 140, 351, 21));
        label_2->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(AboutDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 180, 361, 20));
        label_4->setAlignment(Qt::AlignCenter);
        label_4->setOpenExternalLinks(true);
        label_3 = new QLabel(AboutDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 160, 361, 21));
        label_3->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(AboutDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 200, 361, 20));
        label_5->setAlignment(Qt::AlignCenter);
        label_5->setOpenExternalLinks(true);
        label_7 = new QLabel(AboutDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 80, 361, 20));
        label_7->setAlignment(Qt::AlignCenter);
        label_7->setOpenExternalLinks(true);
        label_6 = new QLabel(AboutDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 60, 361, 21));
        label_6->setAlignment(Qt::AlignCenter);
        line = new QFrame(AboutDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(20, 110, 361, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(AboutDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(20, 230, 361, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        retranslateUi(AboutDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AboutDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AboutDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "Dialog", 0));
        label->setText(QApplication::translate("AboutDialog", "GTD-Kanban", 0));
        label_8->setText(QApplication::translate("AboutDialog", "Copyright 2015, 2016 Frederick S. Ziegler", 0));
        label_2->setText(QApplication::translate("AboutDialog", "Based on \"Getting Things Done\" by David Allen and", 0));
        label_4->setText(QApplication::translate("AboutDialog", "<a href=\"https://en.wikipedia.org/wiki/Getting_Things_Done\">Wikipedia: Getting Things Done</a>", 0));
        label_3->setText(QApplication::translate("AboutDialog", "\"Personal Kanban\" by Jim Benson and Tonianne DeMaria Barry", 0));
        label_5->setText(QApplication::translate("AboutDialog", "<a href=\"http://www.personalkanban.com/pk/\">Personal Kanban</a>", 0));
        label_7->setText(QApplication::translate("AboutDialog", "<a href=\"https://github.com/fsziegler/GTD-Kanban\">https://github.com/fsziegler/GTD-Kanban</a>", 0));
        label_6->setText(QApplication::translate("AboutDialog", "An open-source project, hosted on GitHub:", 0));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
