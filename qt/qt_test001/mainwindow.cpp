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
#include <fstream>
#include <sys/stat.h>

const string GTDKanbanFileHistoryFileName("../../GTDKanbanFileHistory.txt");
MainWindow::MainWindow(QWidget *parent)
      : QMainWindow(parent),
        ui(new Ui::MainWindow),
        m_gtdTree(this),
        m_currentFileNameStr("[None]")
{
   ui->setupUi(this);
   setWindowTitle(QString("GTD-Kanban, by Fred Ziegler"));
   setMouseTracking(true);

   // Set up In-Basket form
   mp_inBasketForm = new InBasketForm(this),
   mp_inBasketForm->SetGTDTreeWidget(&m_gtdTree);
   mp_inBasketForm->setAcceptDrops(true);
   mp_inBasketForm->setFixedHeight(471);
   mp_inBasketForm->setFixedWidth(501);

   // Create GTD splitter window & add in-basket and tree windows to it
   mp_gtdSplitter = new QSplitter(Qt::Vertical);
   mp_gtdSplitter->addWidget(mp_inBasketForm);
   mp_gtdSplitter->addWidget(&m_gtdTree);
   mp_gtdSplitter->setChildrenCollapsible(true);

   // Create main splitter window & add GTD splitter window to it
   mp_mainLRSplitter = new QSplitter(Qt::Horizontal);
   mp_mainLRSplitter->addWidget(mp_gtdSplitter);

   // Set up Kanban calendar & editor and add to Kanban splitter window
   mp_gtdCalendar = new GTDCalendarWidget(parent);
   mp_gtdCalendar->setDateEditEnabled(true);
   mp_gtdCalendar->setDateEditEnabled(true);
   mp_kanbanSplitter = new QSplitter(Qt::Vertical);
   mp_kanbanSplitter->setWindowTitle(QString("GTD Calendar"));
   mp_kanbanSplitter->addWidget(mp_gtdCalendar);

   mp_kanbanWindow = new KanbanWidget;
   mp_kanbanSplitter->addWidget(mp_kanbanWindow);
   QList<int> sizes = {1, 150};
   mp_kanbanSplitter->setSizes(sizes);

   // Add Kanban splitter window to main splitter window & set as central widget
   mp_mainLRSplitter->addWidget(mp_kanbanSplitter);
   setCentralWidget(mp_mainLRSplitter);

   ScaleAndCenterWindow(0.8);
   UpdateRecentFilesMenu();
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
   QMainWindow::mousePressEvent(event);
   mp_gtdCalendar->mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
   std::cout << "(" << event->pos().x() << ", " << event->pos().y() << "), ("
         << event->pos().rx() << ", " << event->pos().ry() << ")" << std::endl;
}

void MainWindow::OpenFile(const QString& fileName)
{
   m_gtdEditor.clear();
   m_gtdTree.ClearTree();
   mp_inBasketForm->ClearWorkspace();
   mp_gtdCalendar->repaint();

   if(mp_inBasketForm->LoadFromFile(fileName))
   {
       setWindowTitle(fileName);
       QString statusMsg("File \"");
       statusMsg.append(fileName).append("\" loaded ...");
       statusBar()->showMessage(statusMsg, 5000);
       m_currentFileNameStr = fileName;
       AddToFileHistory(fileName);
   }
}

void MainWindow::AddToFileHistory(const QString& fileName)
{
   m_recentFileList.prepend(fileName);
   m_recentFileList.removeDuplicates();
   while(10 < m_recentFileList.size())
   {
       m_recentFileList.pop_back();
   }
   std::ofstream recentFiles;
   recentFiles.open(GTDKanbanFileHistoryFileName,
                    std::ofstream::out | std::ofstream::trunc
                    );
   if (recentFiles.is_open())
   {
      for (auto itr : m_recentFileList)
      {
         recentFiles << (itr.toStdString()) << endl;
      }
      recentFiles.close();
   }
   UpdateRecentFilesMenu();
}

void MainWindow::UpdateRecentFilesMenu()
{
   std::ifstream recentFiles(GTDKanbanFileHistoryFileName, std::ifstream::in);
   if (recentFiles.is_open())
   {
      QList<QMenu*> menus = menuBar()->findChildren<QMenu*>();
      QMenu* first = menus[0];
      menus = first->findChildren<QMenu*>();
      QMenu* recentFileMenu = menus[0];
      recentFileMenu->clear();
      string line;
      int cnt(0);
      while (getline(recentFiles, line))
      {
         struct stat buffer;
         if (stat(line.c_str(), &buffer) == 0)
         {
            m_recentFileList.push_back(line.c_str());
            QAction* action = new QAction(line.c_str(), menus[0]);
            recentFileMenu->addAction(action);
            switch (cnt)
            {
            case 0:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile0()));
               break;
            case 1:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile1()));
               break;
            case 2:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile2()));
               break;
            case 3:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile3()));
               break;
            case 4:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile4()));
               break;
            case 5:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile5()));
               break;
            case 6:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile6()));
               break;
            case 7:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile7()));
               break;
            case 8:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile8()));
               break;
            case 9:
               connect(action, SIGNAL(triggered()), this,
                     SLOT(OpenRecentFile9()));
               break;
            default:
               break;
            }
            ++cnt;
            if (9 < cnt)
            {
               break;
            }
         }
      }
   }
   recentFiles.close();
}

void MainWindow::on_actionExit_triggered()
{
   QApplication::quit();
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
   mp_inBasketForm->ClearWorkspace();
   mp_gtdCalendar->repaint();
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
      mp_inBasketForm->GetUserData().DumpAllToJSONFile(
            m_currentFileNameStr.toStdString());
   }
}

void MainWindow::on_actionSave_As_triggered()
{
   QString fileName = QFileDialog::getSaveFileName(this, "Save file", "",
         ".json");
   if (0 < fileName.size())
   {
      if (!fileName.endsWith(".json"))
      {
         fileName.append(".json");
      }
      QString msg("Save As ");
      msg.append(fileName);
      statusBar()->showMessage(msg, 5000);
      mp_inBasketForm->GetUserData().DumpAllToJSONFile(fileName.toStdString());
      AddToFileHistory(fileName);
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

void MainWindow::on_action_Open_triggered()
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
          mp_inBasketForm->ClearWorkspace();
          mp_gtdCalendar->repaint();
          for (auto fileName : fileNames)
          {
             OpenFile(fileName);
          }
       }
    }
}

void MainWindow::OpenRecentFile0()
{
    OpenFile(m_recentFileList[0]);
}

void MainWindow::OpenRecentFile1()
{
    OpenFile(m_recentFileList[1]);
}

void MainWindow::OpenRecentFile2()
{
    OpenFile(m_recentFileList[2]);
}

void MainWindow::OpenRecentFile3()
{
    OpenFile(m_recentFileList[3]);
}

void MainWindow::OpenRecentFile4()
{
    OpenFile(m_recentFileList[4]);
}

void MainWindow::OpenRecentFile5()
{
    OpenFile(m_recentFileList[5]);
}

void MainWindow::OpenRecentFile6()
{
    OpenFile(m_recentFileList[6]);
}

void MainWindow::OpenRecentFile7()
{
    OpenFile(m_recentFileList[7]);
}

void MainWindow::OpenRecentFile8()
{
    OpenFile(m_recentFileList[8]);
}

void MainWindow::OpenRecentFile9()
{
    OpenFile(m_recentFileList[9]);
}
