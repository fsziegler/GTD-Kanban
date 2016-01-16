#ifndef KANBANWIDGET_H
#define KANBANWIDGET_H

#include <QWidget>

class KanbanWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KanbanWidget(QWidget *parent = 0);

signals:

public slots:

Q_SIGNALS:
protected:
    // Event handlers
    virtual void paintEvent(QPaintEvent *);

};

#endif // KANBANWIDGET_H
