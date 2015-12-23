#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QTextStream>
#include <QDockWidget>

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
    mp_inBasketForm->setAcceptDrops(true);
    mp_gtdSplitter->addWidget(mp_inBasketForm);
    mp_gtdSplitter->addWidget(&m_gtdTree);
    mp_gtdSplitter->setChildrenCollapsible(true);
    mp_inBasketForm->setFixedHeight(471);
    mp_inBasketForm->setFixedWidth(501);

    // Create main splitter window & add GTD and Kanban windows to it
    mp_lrSplitter = new QSplitter(Qt::Horizontal);
    mp_lrSplitter->addWidget(mp_gtdSplitter);
//    mp_lrSplitter->addWidget(dock);

    mp_kanbanSplitter = new QSplitter(Qt::Vertical);
    mp_kanbanSplitter->setWindowTitle(QString("Kanban Calendar"));
//    QDockWidget *dock = new QDockWidget(QString("Kanban"), this);
    QToolBar *toolBar = new QToolBar(QString("Kanban"), this);
//    toolBar->addAction(QIcon(QPixmap(QSize(22, 22))), QString("Actionsss"));
//    QList<QAction*> actions;
//    actions.append(new QAction(QString("Day"), (QObject*)0));
//    actions.append(new QAction(QString("Week"), (QObject*)0));
//    toolBar->setWindowTitle(QString("Kanban Calendar"));
////    toolBar->
//    toolBar->addActions(actions);
//    toolBar->addAction(QString("Day"));
//    toolBar->addAction(QString("Week"));
//    toolBar->addAction(QString("Month"));
//    toolBar->addAction(QString("Year"));
//    toolBar->setOrientation(Qt::Vertical);
    m_kanbanCalendar.setDateEditEnabled(true);
    m_kanbanCalendar.setDateEditEnabled(true);
    toolBar->addWidget(&m_kanbanCalendar);
//    mp_kanbanSplitter->addWidget(&m_kanbanCalendar);
    mp_kanbanSplitter->addWidget(toolBar);
    mp_kanbanSplitter->addWidget(&m_kanbanEditor);
    mp_lrSplitter->addWidget(mp_kanbanSplitter);
    setCentralWidget(mp_lrSplitter);
//    setCentralWidget(dock);

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
