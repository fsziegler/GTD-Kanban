#ifndef GTDTEXTEDIT_H
#define GTDTEXTEDIT_H

#include<QTextEdit>

class GTDTextEdit : public QTextEdit
{
public:
    explicit GTDTextEdit(QWidget* parent = 0);

private:
    GTDTextEdit();

    QWidget* mp_parentWidget;
};

#endif // GTDTEXTEDIT_H
