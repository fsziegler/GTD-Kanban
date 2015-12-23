#include "gtdtreewidget.h"
#include<QMessageBox>

GTDTreeWidget::GTDTreeWidget()
    : m_nonActionableTWI((QTreeWidget*)0, QStringList(QString("Non-Actionable"))),
      m_SomedayMaybeTWI((QTreeWidget*)0, QStringList(QString("Someday Maybe"))),
      m_ReferenceTWI((QTreeWidget*)0, QStringList(QString("Reference"))),
      m_TrashTWI((QTreeWidget*)0, QStringList(QString("Trash"))),
      m_actionableTWI((QTreeWidget*)0, QStringList(QString("Actionable"))),
      m_tasksTWI((QTreeWidget*)0, QStringList(QString("Tasks"))),
      m_DoItTWI((QTreeWidget*)0, QStringList(QString("Do It!"))),
      m_WaitingOnSomeoneTWI((QTreeWidget*)0, QStringList(QString("Waiting on someone"))),
      m_CalendarTWI((QTreeWidget*)0, QStringList(QString("Calendar"))),
      m_NextActionsTWI((QTreeWidget*)0, QStringList(QString("Next Actions"))),
      m_projectsTWI((QTreeWidget*)0, QStringList(QString("Projects"))),
      m_projectsToPlanTWI((QTreeWidget*)0, QStringList(QString("Projects-to-Plan"))),
      m_projectPlansTWI((QTreeWidget*)0, QStringList(QString("Project Plans")))
{
    setColumnCount(1);
    setHeaderLabel(QString("GTD Tree"));
    setSortingEnabled(false);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QTreeWidget::InternalMove);

    m_nonActionableTWI.addChild(&m_SomedayMaybeTWI);
    m_nonActionableTWI.addChild(&m_ReferenceTWI);
    m_nonActionableTWI.addChild(&m_TrashTWI);
    m_actionableTWI.addChild(&m_tasksTWI);
    insertTopLevelItem(0, &m_actionableTWI);
    insertTopLevelItem(0, &m_nonActionableTWI);
    m_tasksTWI.addChild(&m_DoItTWI);
    m_tasksTWI.addChild(&m_WaitingOnSomeoneTWI);
    m_tasksTWI.addChild(&m_CalendarTWI);
    m_tasksTWI.addChild(&m_NextActionsTWI);
    m_actionableTWI.addChild(&m_projectsTWI);
    m_projectsTWI.addChild(&m_projectsToPlanTWI);
    m_projectsTWI.addChild(&m_projectPlansTWI);
    expandAll();
}

GTDTreeWidget::~GTDTreeWidget()
{
}

bool GTDTreeWidget::IsPosInMemberTWI(const QPoint& pos) const
{
    bool retVal(false);
    retVal = retVal || visualItemRect(&m_SomedayMaybeTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_ReferenceTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_TrashTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_actionableTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_tasksTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_DoItTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_WaitingOnSomeoneTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_CalendarTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_NextActionsTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_projectsTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_projectsToPlanTWI).contains(pos);
    retVal = retVal || visualItemRect(&m_projectPlansTWI).contains(pos);
    return retVal;
}

void GTDTreeWidget::dropEvent(QDropEvent * event)
{
    bool copy(Qt::CopyAction == event->proposedAction());
    bool move(Qt::MoveAction == event->proposedAction());
    if(move && IsPosInMemberTWI(event->pos()))
    {
        repaint();
        return;
    }
    QTreeWidget::dropEvent(event);
}

