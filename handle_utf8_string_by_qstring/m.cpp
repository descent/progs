#include <QtGui>
#include <QString>
#include <QDebug>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QString str = QString::fromUtf8("中ab文");
  //QString str = QString::fromUtf8("abc");
  qDebug() << str;// << endl;
  //cout << str << endl;
  for (int i=0 ; i < str.length() ; ++i)
  {
    QChar qch = str[i];
    qDebug() << qch << endl;
  }

  return app.exec();

}
