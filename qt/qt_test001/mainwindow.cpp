#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"

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
        m_gtdCalendar(parent),
        m_currentFileNameStr("[None]")
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
   mp_kanbanSplitter->addWidget(&m_kanbanWindow);
   QList<int> sizes = {1, 150};
   mp_kanbanSplitter->setSizes(sizes);

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
   QFileDialog ofDialog(this, tr("Open Image"), "/home");
   ofDialog.setNameFilter(tr("JSON Files (*.json);;All Files (*.*)"));
   if (ofDialog.exec())
   {
      QStringList fileNames;
      fileNames = ofDialog.selectedFiles();
      if (0 < fileNames.size())
      {
         m_gtdEditor.clear();
         m_gtdTree.ClearTree();
         m_inBasketForm.ClearWorkspace();
         m_gtdCalendar.repaint();
         for (auto fileName : fileNames)
         {
            m_inBasketForm.LoadFromFile(fileName);
            setWindowTitle(fileName);
            QString statusMsg("File \"");
            statusMsg.append(fileName).append("\" loaded ...");
            statusBar()->showMessage(statusMsg, 5000);
            m_currentFileNameStr = fileName;
         }
      }
   }
}

void MainWindow::ScaleAndCenterWindow(float scale)
{
   QSize newSize(QDesktopWidget().availableGeometry(this).size() * scale);
   resize(newSize);
   const int x = (QApplication::desktop()->width() - newSize.width()) / 2;
   const int y = (QApplication::desktop()->height() - newSize.height()) / 2;
   move(x, y);
}

void MainWindow::on_action_New_triggered()
{
   statusBar()->showMessage("New File ...", 5000);
   m_gtdEditor.clear();
   m_gtdTree.ClearTree();
   m_inBasketForm.ClearWorkspace();
   m_gtdCalendar.repaint();
}

void MainWindow::on_actionSave_triggered()
{
   if (QString("[None]") == m_currentFileNameStr)
   {
      on_actionSave_As_triggered();
   }
   else
   {
      QString statusMsg("File \"");
      statusMsg.append(m_currentFileNameStr).append("\" saved.");
      statusBar()->showMessage(statusMsg, 5000);
      m_inBasketForm.GetUserData().DumpAllToJSONFile(
            m_currentFileNameStr.toStdString());
   }
}

void MainWindow::on_actionSave_As_triggered()
{
   QString filename = QFileDialog::getSaveFileName(this, "Save file", "", ".json");
   if(0 < filename.size())
   {
      if(!filename.endsWith(".json"))
      {
         filename.append(".json");
      }
      QString msg("Save As ");
      msg.append(filename);
      statusBar()->showMessage(msg, 5000);
      m_inBasketForm.GetUserData().DumpAllToJSONFile(
            filename.toStdString());
   }
   else
   {
      statusBar()->showMessage("File:Save As cancelled", 5000);
   }
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog abtDlg;
    abtDlg.exec();
}
