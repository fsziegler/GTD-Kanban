#ifndef GTDLISTWIDGET_H
#define GTDLISTWIDGET_H

#include <QListWidget>

class GTDListWidget : public QListWidget
{
public:
    explicit GTDListWidget(QWidget *parent = 0);
    GTDListWidget();

Q_SIGNALS:
protected:
    virtual bool dropMimeData(int index, const QMimeData *data, Qt::DropAction action);
    virtual void dragMoveEvent(QDragMoveEvent *e);
    virtual void dragLeaveEvent(QDragLeaveEvent *e);
    virtual void dropEvent(QDropEvent *e);
    virtual void startDrag(Qt::DropActions supportedActions);
};

#endif // GTDLISTWIDGET_H
