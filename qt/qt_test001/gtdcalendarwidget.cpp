#include "gtdcalendarwidget.h"
#include <QMessageBox>
#include <iostream>

GTDCalendarWidget::GTDCalendarWidget(QWidget *parent)
  : QCalendarWidget(parent)
{
   m_inited.start();
}

GTDCalendarWidget::~GTDCalendarWidget()
{}

int cnt(0);
void GTDCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
   QCalendarWidget::paintCell(painter, rect, date);
   std::cout << "paint " << ++cnt << " " << date.toString(Qt::ISODate).toUtf8().constData();
   std::cout << "(" << rect.x() << ", " << rect.y() << ", " << rect.width() << ", " << rect.height() << ")"
   << std::endl;
}
