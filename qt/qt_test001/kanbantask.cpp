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

   setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void KanbanTask::setText(const QString& newText)
{
   static const int kMinLines(2);
   m_text = newText;
   const int lines = kMinLines + m_text.count(QLatin1Char('\n'));
   int maxLen(0);
   int cnt(0);
   if(kMinLines == lines)
   {
      maxLen = m_text.length();
   }
   else
   {
      for(auto itr: m_text)
      {
         if('\n' != itr)
         {
            ++cnt;
         }
         else
         {
            maxLen = (maxLen < cnt ? cnt : maxLen);
            cnt = 0;
         }
      }
   }
   QSize newSize(25 + maxLen * 8, lines * 20);
   resize(newSize);
}

const QString& KanbanTask::getText() const
{
   return m_text;
}

void KanbanTask::Center(const QPoint& centerPoint)
{
   int deltaX = centerPoint.x() - rect().center().x();
   int deltaY = centerPoint.y() - rect().center().y();
   move(rect().x() + deltaX, rect().y() + deltaY);
}

void KanbanTask::mousePressEvent(QMouseEvent* event)
{
   m_initPos = event->pos();
   m_currPos = event->pos();
   m_initRegion = rect();
   m_currRegion = rect();
   setFocus();
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
   setFocus();
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
   setFocus();
}

void KanbanTask::paintEvent(QPaintEvent* pntEvent)
{
   QRect rect = pntEvent->rect();
   QWidget::paintEvent(pntEvent);

   QPainter painter(this);
   painter.save();

   painter.setPen(Qt::darkGray);
   painter.setFont(QFont("Arial", 11));
   painter.drawText(rect, Qt::AlignCenter, m_text);
   painter.setBackgroundMode(Qt::BGMode::OpaqueMode);

   QBrush lineBrush(Qt::black);
   if(hasFocus())
   {
      painter.setPen(QPen(lineBrush, 4, Qt::SolidLine, Qt::SquareCap));
   }
   else
   {
      painter.setPen(QPen(lineBrush, 2, Qt::SolidLine, Qt::SquareCap));
   }
   painter.drawRect(rect);

   painter.restore();
}
