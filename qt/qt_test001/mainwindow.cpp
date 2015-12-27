#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QTextStream>
#include <QDockWidget>
#include <QDebug>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
      : QMainWindow(parent),
        ui(new Ui::MainWindow),
        m_gtdCalendar(parent)
{
   ui->setupUi(this);
   setWindowTitle(QString("GTD-Kanban, by Fred Ziegler"));
   setMouseTracking(true);

   // Set up In-Basket form
   m_inBasketForm.SetGTDTreeWidget(&m_gtdTree);
   m_inBasketForm.setAcceptDrops(true);
   m_inBasketForm.setFixedHeight(471);
   m_inBasketForm.setFixedWidth(501);

   // Create GTD splitter window & add in-basket and tree windows to it
   mp_gtdSplitter = new QSplitter(Qt::Vertical);
   mp_gtdSplitter->addWidget(&m_inBasketForm);
   mp_gtdSplitter->addWidget(&m_gtdTree);
   mp_gtdSplitter->setChildrenCollapsible(true);

   // Create main splitter window & add GTD splitter window to it
   mp_mainLRSplitter = new QSplitter(Qt::Horizontal);
   mp_mainLRSplitter->addWidget(mp_gtdSplitter);

   // Set up Kanban calendar & editor and add to Kanban splitter window
   m_gtdCalendar.setDateEditEnabled(true);
   m_gtdCalendar.setDateEditEnabled(true);
   mp_kanbanSplitter = new QSplitter(Qt::Vertical);
   mp_kanbanSplitter->setWindowTitle(QString("GTD Calendar"));
   mp_kanbanSplitter->addWidget(&m_gtdCalendar);
   mp_kanbanSplitter->addWidget(&m_kanbanEditor);

   // Add Kanban splitter window to main splitter window & set as central widget
   mp_mainLRSplitter->addWidget(mp_kanbanSplitter);
   setCentralWidget(mp_mainLRSplitter);

   ScaleAndCenterWindow(0.8);
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
   QMainWindow::mousePressEvent(event);
   m_gtdCalendar.mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
   std::cout << "(" << event->pos().x() << ", " << event->pos().y() << "), ("
         << event->pos().rx() << ", " << event->pos().ry() << ")" << std::endl;
}

void MainWindow::on_actionExit_triggered()
{
   QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
         "/home", tr("JSON Files (*.json);;All Files (*.*)"));
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
