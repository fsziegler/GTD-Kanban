#ifndef QKANBANCALENDARWIDGET_H
#define QKANBANCALENDARWIDGET_H

#include <QCalendarWidget>
#include <QTime>
#include <QMouseEvent>
#include <QPoint>
#include <QPen>
#include <QBrush>

class MainWindow;

class GTDCalendarWidget: public QCalendarWidget
{
Q_OBJECT
public:
   GTDCalendarWidget(QWidget *parent = 0);
   virtual ~GTDCalendarWidget();

//protected:
   virtual void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
   virtual void paintCell(QPainter *painter, const QRect &rect,
         const QDate &date) const;
private:
   MainWindow* mp_mainWindow;

   QTime m_timer;
   Qt::MouseButtons m_mouseBtns;
   QPoint m_leftClickPoint;

   QPen m_outlinePen;
   QBrush m_transparentBrush;
};

#endif // QKANBANCALENDARWIDGET_H
