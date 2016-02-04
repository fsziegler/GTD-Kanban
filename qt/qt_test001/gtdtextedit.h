#ifndef GTDTEXTEDIT_H
#define GTDTEXTEDIT_H

#include<QTextEdit>

class InBasketForm;

class GTDTextEdit : public QTextEdit
{
Q_OBJECT

public:
   explicit GTDTextEdit(QWidget* parent = 0);

Q_SIGNALS:
protected:
   virtual void keyPressEvent(QKeyEvent *e);

private:
   GTDTextEdit();

   InBasketForm*    mp_inBasketForm;
};

#endif // GTDTEXTEDIT_H
