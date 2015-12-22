#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("GTD-Kanban, by Fred Ziegler"));

    // Create GTD splitter window & add in-basket and tree windows to it
    mp_gtdSplitter = new QSplitter(Qt::Vertical);
    mp_inBasketForm = new InBasketForm();
    mp_inBasketForm->SetGTDTreeWidget(&m_gtdTree);
    mp_gtdSplitter->addWidget(mp_inBasketForm);
    mp_gtdSplitter->addWidget(&m_gtdTree);
    mp_gtdSplitter->setChildrenCollapsible(true);
    mp_inBasketForm->setFixedHeight(471);
    mp_inBasketForm->setFixedWidth(501);

    // Set up the tree window
    m_gtdTree.setColumnCount(1);
    m_gtdTree.setHeaderLabel(QString("GTD Tree"));
    m_gtdTree.setSortingEnabled(false);
    QTreeWidgetItem* nonActionableTI = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Non-Actionable")));
    nonActionableTI->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Someday Maybe"))));
    nonActionableTI->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Reference"))));
    nonActionableTI->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Trash"))));
    QTreeWidgetItem* actionableTI = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Actionable")));
    QTreeWidgetItem* tasksTI = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Tasks")));
    actionableTI->addChild(tasksTI);
    m_gtdTree.insertTopLevelItem(0, actionableTI);
    m_gtdTree.insertTopLevelItem(0, nonActionableTI);
    tasksTI->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Do It!"))));
    tasksTI->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Waiting on someone"))));
    tasksTI->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Calendar"))));
    tasksTI->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Next Actions"))));
    QTreeWidgetItem* projectsTI = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Projects")));
    actionableTI->addChild(projectsTI);
    projectsTI->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Projects-to-Plan"))));
    projectsTI->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Project Plans"))));
    m_gtdTree.expandAll();
    //    m_gtdTree.ins

    // Create main splitter window & add GTD and Kanban windows to it
    mp_lrSplitter = new QSplitter(Qt::Horizontal);
    mp_lrSplitter->addWidget(mp_gtdSplitter);
    mp_lrSplitter->addWidget(&m_kanbanEditor);
    setCentralWidget(mp_lrSplitter);

    ScaleAndCenterWindow(0.8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home", tr("JSON Files (*.json);;All Files (*.*)"));
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream ReadFile(&file);
    m_gtdEditor.setText(ReadFile.readAll());
    m_gtdEditor.parentWidget()->setWindowTitle(fileName);
}

void MainWindow::ScaleAndCenterWindow(float scale)
{
    QSize newSize(QDesktopWidget().availableGeometry(this).size() * scale);
    resize(newSize);
    const int x = (QApplication::desktop()->width() - newSize.width()) / 2;
    const int y = (QApplication::desktop()->height() - newSize.height()) / 2;
    move(x, y);
}
