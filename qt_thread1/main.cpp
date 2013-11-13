#include <QtGui>

#include "w.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);   
  qDebug()<<"main: "<<QThread::currentThreadId(); 
  Widget w;
  w.show();
  return app.exec();
}
