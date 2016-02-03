#include "gtdtextedit.h"
#include "mainwindow.h"
#include <QDropEvent>
#include <QApplication>

GTDTextEdit::GTDTextEdit(QWidget* parent)
: QTextEdit(parent)
{

}

void GTDTextEdit::keyPressEvent(QKeyEvent *event)
{
   if((event->key() == Qt::Key_2) && (event->modifiers() == Qt::ALT))
   {
       MainWindow * win = (MainWindow *) QApplication::activeWindow();
       win->SetFocusInListWidget();
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
