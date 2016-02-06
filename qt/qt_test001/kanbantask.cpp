#include "kanbantask.h"
#include "kanbanwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <iostream>

using namespace std;

KanbanTask::KanbanTask(QWidget* parent)
: QWidget(parent)
{
   setAutoFillBackground(true);
   QPalette Pal(palette());
   Pal.setColor(QPalette::Background, QColor(255, 255, 128));
   setPalette(Pal);
   connect(&UpdateTimer, SIGNAL(timeout()), this, SLOT(repaint()));
   UpdateTimer.start(500);

   setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
   parentWidget()->rect();
//   setFixedWidth(1500);
//   setFixedWidth(parentWidget()->width()/3);
   setFixedSize(parentWidget()->width()/3, 100);

//   setFixedWidth(parentWidget()->rect().right() - parentWidget()->rect().left());
}

void KanbanTask::mousePressEvent(QMouseEvent* event)
{
   m_initPos = event->pos();
   m_currPos = event->pos();
   m_initRegion = rect();
   m_currRegion = rect();
}

void KanbanTask::mouseReleaseEvent(QMouseEvent* event)
{
   const QPoint& pPos = mapToParent(event->pos());
   cout << " : " << pPos.x() << ", " << pPos.y() << endl;
   QRegion pRegion(parentWidget()->rect());
   if((event->pos() != m_initPos) && (pRegion.contains(pPos)))
   {
      int deltaX(event->pos().x() - m_initPos.x());
      int deltaY(event->pos().y() - m_initPos.y());

      hide();
      move(pos().x() + deltaX, pos().y() + deltaY);
      m_currPos = event->pos();
      parentWidget()->repaint();
      m_initPos = event->pos();
      show();
   }
}

//    void KanbanTask::mouseDoubleClickEvent(QMouseEvent* event);

void KanbanTask::mouseMoveEvent(QMouseEvent* event)
{
   const QPoint& pPos = mapToParent(event->pos());
   cout << " : " << pPos.x() << ", " << pPos.y() << endl;
   QRegion pRegion(parentWidget()->rect());

   if((event->pos() != m_currPos) && (pRegion.contains(pPos)))
   {
      const int moveX(event->pos().x() - m_initPos.x());
      const int moveY(event->pos().y() - m_initPos.y());
      move(pos().x() + moveX, pos().y() + moveY);

      const int deltaX(event->pos().x() - m_currPos.x());
      const int deltaY(event->pos().y() - m_currPos.y());
      QRegion newRegion(m_currRegion);
      newRegion.translate(deltaX, deltaY);
      QRegion repaintRegion = m_currRegion.intersected(newRegion);
      repaintRegion = repaintRegion.intersected(m_initRegion);

      parentWidget()->repaint(repaintRegion);
      m_currPos = event->pos();
   }
}

void KanbanTask::paintEvent(QPaintEvent* pntEvent)
{
   QRect rect = pntEvent->rect();
   QWidget::paintEvent(pntEvent);

   QPainter painter(this);
   painter.save();

   painter.setPen(Qt::darkGray);
   painter.setFont(QFont("Arial", 11));
   painter.drawText(rect, Qt::AlignCenter, "Kanban Task\n(I am draggable)");
   painter.setBackgroundMode(Qt::BGMode::OpaqueMode);

   QBrush lineBrush(Qt::black);
   painter.setPen(QPen(lineBrush, 2, Qt::SolidLine, Qt::SquareCap));
   painter.drawRect(rect);

   painter.restore();
}