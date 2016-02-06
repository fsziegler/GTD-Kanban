#ifndef KANBANWIDGET_H
#define KANBANWIDGET_H

#include <QWidget>
#include <QTimer>
#include "kanbantask.h"

class KanbanWidget : public QWidget
{
Q_OBJECT

public:
   explicit KanbanWidget(QWidget *parent = 0);

   const QPoint& childPos() const;

signals:

public slots:

Q_SIGNALS:
protected:
   // Event handlers
   virtual void paintEvent(QPaintEvent *);

   KanbanTask m_testChild;
   QTimer UpdateTimer;
};

#endif // KANBANWIDGET_H
