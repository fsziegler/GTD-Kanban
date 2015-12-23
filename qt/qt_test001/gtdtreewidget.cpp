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
    const Qt::ItemFlags flags(Qt::ItemIsSelectable | Qt::ItemIsDropEnabled
                              | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    m_nonActionableTWI.setFlags(flags);
    m_SomedayMaybeTWI.setFlags(flags);
    m_ReferenceTWI.setFlags(flags);
    m_TrashTWI.setFlags(flags);
    m_actionableTWI.setFlags(flags);
    m_tasksTWI.setFlags(flags);
    m_DoItTWI.setFlags(flags);
    m_WaitingOnSomeoneTWI.setFlags(flags);
    m_CalendarTWI.setFlags(flags);
    m_NextActionsTWI.setFlags(flags);
    m_projectsTWI.setFlags(flags);
    m_projectsToPlanTWI.setFlags(flags);
    m_projectPlansTWI.setFlags(flags);

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
