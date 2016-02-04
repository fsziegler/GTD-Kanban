#include "gtdtextedit.h"
#include "mainwindow.h"
#include "inbasketform.h"
#include <QDropEvent>
#include <QApplication>

GTDTextEdit::GTDTextEdit(QWidget* parent)
   : QTextEdit(parent),
     mp_inBasketForm((InBasketForm*)parent)
{

}

void GTDTextEdit::keyPressEvent(QKeyEvent *event)
{
   MainWindow * win = (MainWindow *) QApplication::activeWindow();
   if((event->key() == Qt::Key_2) && (event->modifiers() == Qt::ALT))
   {
      win->SetFocusInListWidget();
      return;
   }
   else if((event->key() == Qt::Key_3) && (event->modifiers() == Qt::ALT))
   {
      win->SetFocusInGTDTreeWidget();
      return;
   }
   else if((event->key() == Qt::Key_M) && (event->modifiers() == Qt::ALT))
   {
      mp_inBasketForm->on_gtdMinMaxButton_clicked();
      return;
   }

   const QTextCursor& initCursor(textCursor());
   QTextEdit::keyPressEvent(event);
   if(textCursor().position() == initCursor.position())
   {
      if(Qt::Key_Down == event->key())
      {
         QTextEdit::moveCursor(QTextCursor::MoveOperation::End);
      }
      else if(Qt::Key_Up == event->key())
      {
         QTextEdit::moveCursor(QTextCursor::MoveOperation::StartOfLine);
      }
   }
}
