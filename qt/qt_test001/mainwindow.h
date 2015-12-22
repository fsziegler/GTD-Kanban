#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inbasketform.h"

#include <QMainWindow>
#include <QSplitter>
#include <QPointer>
#include <QTextEdit>
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

private:
    void ScaleAndCenterWindow(float scale);

    Ui::MainWindow *ui;
    QPointer<InBasketForm> mp_inBasketForm;
    QPointer<QSplitter> mp_gtdSplitter;
    QPointer<QSplitter> mp_lrSplitter;
    QTextEdit m_gtdEditor;
    QTreeWidget m_gtdTree;
    QTextEdit m_kanbanEditor;
};
#endif // MAINWINDOW_H