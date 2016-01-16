#include "kanbanwidget.h"
#include <QPainter>
#include <QPaintEvent>

KanbanWidget::KanbanWidget(QWidget *parent) : QWidget(parent)
{

}

void KanbanWidget::paintEvent(QPaintEvent *pntEvent)
{
   QRect rect = pntEvent->rect();
   QWidget::paintEvent(pntEvent);

   QPainter painter(this);
   painter.save();
   painter.setPen(Qt::blue);
   painter.setFont(QFont("Arial", 24));
   painter.drawText(rect, Qt::AlignCenter, "(Kanban Graph Goes here)");
   painter.restore();
}
