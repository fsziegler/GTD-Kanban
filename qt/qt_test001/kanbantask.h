#ifndef KANBANTASK_H
#define KANBANTASK_H

#include <QWidget>
#include <QTimer>

class KanbanWidget;

class KanbanTask : public QWidget
{
   Q_OBJECT
public:
   explicit KanbanTask(QWidget* parent = 0);

   void setText(const QString& newText);
   const QString& getText() const;

   void Center(const QPoint& centerPoint);

signals:

public slots:

Q_SIGNALS:
protected:
    // Event handlers
//    bool event(QEvent* );
    virtual void mousePressEvent(QMouseEvent* );
    virtual void mouseReleaseEvent(QMouseEvent* );
//    virtual void mouseDoubleClickEvent(QMouseEvent* );
    virtual void mouseMoveEvent(QMouseEvent* );
   virtual void paintEvent(QPaintEvent* pntEvent);

private:
   QPoint         m_initPos;
   QPoint         m_currPos;
   QRegion        m_initRegion;
   QRegion        m_currRegion;
   QString        m_text;
   QTimer         m_updateTimer;
   KanbanWidget*  mp_kanbanParent;
};

#endif // KANBANTASK_H
