#ifndef W_H
#define W_H

#include <QtGui>

class Worker:public QObject 
{ 
    Q_OBJECT 
public: 
    Worker(){} 
public slots: 
    void slot1(int v) 
    { 
        qDebug()<<"slots1: "<<QThread::currentThreadId(); 
        emit sig1(QString::number(v*v*v)); 
    } 
signals: 
    void sig1(const QString& t); 
};

class MyWidget:public QWidget 
{
  Q_OBJECT 

  public: 
    MyWidget ( QWidget * parent = 0, Qt::WindowFlags f = 0 );
    ~MyWidget();

  private:

};

class Widget:public QWidget 
{ 
    Q_OBJECT public: 
    Widget();
    ~Widget()
    {
      qDebug() << "wait thread end" << objectName();
      thread->exit(0);
      while (thread->isFinished() == false);
      qDebug() << "delete thread";
    #if 0
      delete thread;
      #endif
    }
signals: 
    void clicked(int v); 
private slots: 
    void onButtonClicked() 
    { 
        static int v = 0; 
        emit clicked(v); 
        v++; 
    } 
private: 
    QLabel * m_label; 
    QPushButton * m_button, *button_;
    Worker * m_worker; 
    QThread *thread;
    MyWidget *my_widget_;
};


#endif
