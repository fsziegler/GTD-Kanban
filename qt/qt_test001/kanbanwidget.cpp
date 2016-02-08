#include "kanbanwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QFontMetrics>
#include <QTreeWidget>
#include <QtDebug>

KanbanWidget::KanbanWidget(QWidget *parent)
   : QWidget(parent),
     UpdateTimer(this)
{
   setAutoFillBackground(true);
   QPalette Pal(palette());
   Pal.setColor(QPalette::Background, QColor(64, 128, 64));
   setPalette(Pal);

   m_readyList.append(new KanbanTask(this));
   KanbanTask* testChild = m_readyList.front();
   testChild->setText("Kanban Task\n(I am draggable)\n(I am draggable)\n(I am draggable)");
   m_readyList.front()->move(testChild->x() + 10, testChild->y() + 70);
   m_readyList.front()->show();
   m_readyList.front()->setFocus();
   connect(&UpdateTimer, SIGNAL(timeout()), this, SLOT(repaint()));
   UpdateTimer.start(100);
}

const QPoint& KanbanWidget::childPos() const
{
   return m_readyList.front()->pos();
}

const QRegion& KanbanWidget::GetKanbanStateRegion(EnumKanbanState state)
{
   UpdateRegions();
   switch(state)
   {
   case kReady:
      return m_readyRegion;
   case kDoing:
      return m_doingRegion;
   case kDone:
      return m_doneRegion;
   default:
      break;
   }
   throw;
}

void KanbanWidget::paintEvent(QPaintEvent *pntEvent)
{
   QRect rect = pntEvent->rect();

   QPainter painter(this);
   painter.save();
   painter.setPen(Qt::lightGray);
   painter.setFont(QFont("Arial", 48));
   painter.drawText(rect, Qt::AlignCenter, "Kanban Graph");

   painter.setPen(QColor(0, 49, 83));
   painter.setFont(QFont("Arial", 24, QFont::DemiBold));

   static bool firstPaint(true);
   if(firstPaint)
   {
      QFontMetrics fMetrics(painter.font());
      QRect titleRect(rect);
      titleRect.setHeight(fMetrics.height() * 1.5);
      m_titleRegion = titleRect;
      firstPaint = false;
   }
   UpdateRegions();

   QRect readyRect(rect.left(), rect.top(), rect.right()/3,
                   m_titleRegion.boundingRect().height());
   static const QBrush b(Qt::white);
   painter.setBackground(b);
   painter.setBackgroundMode(Qt::BGMode::OpaqueMode);
   painter.fillRect(m_titleRegion.boundingRect(), b);

   // Draw outline rect & section dividers
   QBrush lineBrush(Qt::darkGray);
   painter.setPen(QPen(lineBrush, 6, Qt::SolidLine, Qt::SquareCap));
   painter.drawRect(rect);
   painter.setPen(QPen(lineBrush, 2, Qt::DotLine, Qt::SquareCap));

   QPoint top1_3(m_readyRegion.boundingRect().right(), rect.top());
   QPoint top2_3(m_doingRegion.boundingRect().right(), rect.top());
   painter.drawLine(top1_3, m_readyRegion.boundingRect().bottomRight());
   painter.drawLine(top2_3, m_doingRegion.boundingRect().bottomRight());

   // Draw Kanban header line
   painter.setPen(QPen(lineBrush, 3, Qt::SolidLine, Qt::SquareCap));
   painter.drawLine(m_titleRegion.boundingRect().bottomLeft(),
                    m_titleRegion.boundingRect().bottomRight());

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
   QWidget::paintEvent(pntEvent);
}

void KanbanWidget::UpdateRegion(const QRect& inRect, QRegion& outRegion)
{
   QRegion tmpRegion(inRect);
   outRegion.swap(tmpRegion);
}

void KanbanWidget::UpdateRegions()
{
   QRect currRect(rect());
   {
      QRect tmpRect(currRect);
      tmpRect.setBottom(m_titleRegion.boundingRect().height() - 1);
      UpdateRegion(tmpRect, m_titleRegion);
   }

   currRect.setTop(m_titleRegion.boundingRect().height());
   const int x1 = currRect.width() / 3;
   const int x2 = currRect.width() - x1;
   const int x3 = currRect.width();
   QRect tmpRect(currRect);
   tmpRect.setRight(x1);
   UpdateRegion(tmpRect, m_readyRegion);
   tmpRect.setLeft(x1);
   tmpRect.setRight(x2);
   UpdateRegion(tmpRect, m_doingRegion);
   tmpRect.setLeft(x2);
   tmpRect.setRight(x3);
   UpdateRegion(tmpRect, m_doneRegion);
}
