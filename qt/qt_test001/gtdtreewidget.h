#ifndef GTDTREEWIDGET_H
#define GTDTREEWIDGET_H

#include <QTreeWidget>
#include <QDropEvent>

class GTDTreeWidget : public QTreeWidget
{
public:
    GTDTreeWidget();
    virtual ~GTDTreeWidget();
protected:
    bool IsPosInMemberTWI(const QPoint& pos) const;
    virtual void dropEvent(QDropEvent * event);
private:
    QTreeWidgetItem m_nonActionableTWI;
    QTreeWidgetItem m_SomedayMaybeTWI;
    QTreeWidgetItem m_ReferenceTWI;
    QTreeWidgetItem m_TrashTWI;

    QTreeWidgetItem m_actionableTWI;
    QTreeWidgetItem m_tasksTWI;
    QTreeWidgetItem m_DoItTWI;
    QTreeWidgetItem m_WaitingOnSomeoneTWI;
    QTreeWidgetItem m_CalendarTWI;
    QTreeWidgetItem m_NextActionsTWI;

    QTreeWidgetItem m_projectsTWI;
    QTreeWidgetItem m_projectsToPlanTWI;
    QTreeWidgetItem m_projectPlansTWI;
};

#endif // GTDTREEWIDGET_H
