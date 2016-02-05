#include "kanbanwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QFontMetrics>
#include <QTreeWidget>

KanbanWidget::KanbanWidget(QWidget *parent) : QWidget(parent)
{
   setAutoFillBackground(true);
   QPalette Pal(palette());
   Pal.setColor(QPalette::Background, QColor(255, 255, 128));
   setPalette(Pal);
}

void KanbanWidget::paintEvent(QPaintEvent *pntEvent)
{
   QRect rect = pntEvent->rect();
   QWidget::paintEvent(pntEvent);

   QPainter painter(this);
   painter.save();
   painter.setPen(Qt::lightGray);
   painter.setFont(QFont("Arial", 48));
   painter.drawText(rect, Qt::AlignCenter, "Kanban Graph");

   painter.setPen(QColor(0, 49, 83));
   painter.setFont(QFont("Arial", 24, QFont::DemiBold));

   QFontMetrics fMetrics(painter.font());
   int height = fMetrics.height() * 1.5;
   QPoint lhsColHrd(rect.left(), height);
   QPoint rhsColHrd(rect.right(), height);

   QRect readyRect(rect.left(), rect.top(), rect.right()/3, height);
   static const QBrush b(Qt::white);
   painter.setBackground(b);
   painter.fillRect(QRect(QPoint(0,0), rhsColHrd), b);

   // Draw outline rect & section dividers
   QBrush lineBrush(Qt::darkGray);
   painter.setPen(QPen(lineBrush, 6, Qt::SolidLine, Qt::SquareCap));
   painter.drawRect(rect);
   painter.setPen(QPen(lineBrush, 4, Qt::DashDotLine, Qt::RoundCap));
   QPoint top1_3(rect.right()/3, rect.top());
   QPoint bottom1_3(rect.right()/3, rect.bottom());
   QPoint top2_3(2*rect.right()/3, rect.top());
   QPoint bottom2_3(2*rect.right()/3, rect.bottom());
   painter.drawLine(top1_3, bottom1_3);
   painter.drawLine(top2_3, bottom2_3);

   // Draw Kanban header line
   painter.setPen(QPen(lineBrush, 3, Qt::SolidLine, Qt::SquareCap));
   painter.drawLine(lhsColHrd, rhsColHrd);

   // Draw Kanban header text
   painter.setPen(QColor(0, 49, 83));
   painter.drawText(readyRect, Qt::AlignCenter, "Ready");
   readyRect.setLeft(readyRect.right());
   readyRect.setRight(2*readyRect.left());
   painter.drawText(readyRect, Qt::AlignCenter, "Doing");
   readyRect.setLeft(readyRect.right());
   readyRect.setRight(rect.right());
   painter.drawText(readyRect, Qt::AlignCenter, "Done!");

   painter.restore();
}
