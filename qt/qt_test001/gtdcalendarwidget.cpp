#include "gtdcalendarwidget.h"
#include <QMessageBox>
#include <QPainter>
#include <iostream>

using namespace std;

GTDCalendarWidget::GTDCalendarWidget(QWidget *parent)
      : QCalendarWidget(parent),
        m_mouseBtns(Qt::NoButton),
        m_leftClickPoint(0, 0)
{
   m_timer.start();
   setMouseTracking(true);
   m_outlinePen.setColor(Qt::red);
   m_transparentBrush.setColor(Qt::transparent);
}

GTDCalendarWidget::~GTDCalendarWidget()
{
}

enum kMouseClick
{
   Down,
   Up,
};

kMouseClick mouseClick(Down);
void ToggleMouseClick()
{
   mouseClick = (
         kMouseClick::Up == mouseClick ? kMouseClick::Down : kMouseClick::Up);
//    cout << mouseClick << endl;
}

void GTDCalendarWidget::mousePressEvent(QMouseEvent * event)
{
   ToggleMouseClick();
   m_mouseBtns = event->buttons();
   if (m_mouseBtns & Qt::LeftButton)
   {
      m_leftClickPoint = event->globalPos();
   }
   else
   {
      std::cout << " (" << event->globalPos().x() << ", "
            << event->globalPos().y() << ", " << event->pos().x() << ", "
            << event->pos().y() << ") " << endl;
   }
}

void CoutRect(const QRect &rect)
{
   cout << " (" << rect.x() << ", " << rect.y() << ", " << rect.width() << ", "
         << rect.height() << ") ";
}

int cnt(0);
QDate lastdate;
int lastElapsed(0);
void GTDCalendarWidget::paintCell(QPainter *painter, const QRect &rect,
      const QDate &date) const
{
//    ToggleMouseClick();
   QCalendarWidget::paintCell(painter, rect, date);
   painter->save();
//   if(selectedDate() == date)
//   if(kMouseClick::Up == mouseClick)
//   cout << abs(lastElapsed - m_timer.elapsed()) << endl;
   if ((date == selectedDate()) && (2 > abs(lastElapsed - m_timer.elapsed())))
   {
      std::cout << mouseClick << "paint " << ++cnt << " "
            << date.toString(Qt::ISODate).toUtf8().constData();
      if ((3000 < m_timer.elapsed()) /*&& (m_mouseBtns && Qt::LeftButton) && (rect.contains(m_leftClickPoint))*/)
      {
         painter->setPen(m_outlinePen);
         painter->setBrush(m_transparentBrush);
         painter->drawRect(rect.adjusted(0, 0, -1, -1));
      }
      //   else
      {
         cout << "[" << m_mouseBtns
               << (m_mouseBtns & Qt::NoButton ? "NoButton" : "")
               << (m_mouseBtns & Qt::LeftButton ? "LeftButton" : "")
               << (m_mouseBtns & Qt::RightButton ? "RightButton" : "") << "]";
      }
      CoutRect(rect);
      cout << m_timer.elapsed() << std::endl;
   }
   lastdate = date;
   lastElapsed = m_timer.elapsed();
   painter->restore();
}