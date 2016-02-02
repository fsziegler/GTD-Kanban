#ifndef GTDTEXTEDIT_H
#define GTDTEXTEDIT_H

#include<QTextEdit>

class MainWindow;

class GTDTextEdit : public QTextEdit
{
public:
    explicit GTDTextEdit(QWidget* parent = 0);

Q_SIGNALS:
protected:
    virtual void keyPressEvent(QKeyEvent *e);

private:
    GTDTextEdit();

    QWidget* mp_parentWidget;
};

#endif // GTDTEXTEDIT_H
