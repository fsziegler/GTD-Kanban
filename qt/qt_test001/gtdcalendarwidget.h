#ifndef QKANBANCALENDARWIDGET_H
#define QKANBANCALENDARWIDGET_H

#include <QCalendarWidget>
#include <QTime>

class GTDCalendarWidget : public QCalendarWidget
{
public:
    GTDCalendarWidget(QWidget *parent = 0);
    ~GTDCalendarWidget();

protected:
    virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;
private:
    QTime m_inited;
};

#endif // QKANBANCALENDARWIDGET_H
