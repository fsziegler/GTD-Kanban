#include "gtdlistwidget.h"

GTDListWidget::GTDListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setAcceptDrops(true);
}

GTDListWidget::GTDListWidget()
{
   setAcceptDrops(true);
}

bool GTDListWidget::dropMimeData(int index, const QMimeData *data,
                                 Qt::DropAction action)
{
   return QListWidget::dropMimeData(index, data, action);
}

void GTDListWidget::dragMoveEvent(QDragMoveEvent *e)
{
   QListWidget::dragMoveEvent(e);
}

void GTDListWidget::dragLeaveEvent(QDragLeaveEvent *e)
{
   QListWidget::dragLeaveEvent(e);
}

void GTDListWidget::dropEvent(QDropEvent *e)
{
    QListWidget::dropEvent(e);
}

void GTDListWidget::startDrag(Qt::DropActions supportedActions)
{
    QListWidget::startDrag(supportedActions);
}
