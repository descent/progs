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


class Widget:public QWidget 
{ 
    Q_OBJECT public: 
    Widget():m_label(new QLabel), m_button(new QPushButton("Button")), m_worker(new Worker) 
    { 
        QVBoxLayout * vbox = new QVBoxLayout(this); 
        vbox->addWidget(m_label); 
        vbox->addWidget(m_button); 
        setLayout(vbox); 
         QThread * thread = new QThread(this); 
        m_worker->moveToThread(thread); 
         connect(m_button,SIGNAL(clicked()),this,SLOT(onButtonClicked())); 
        connect(this,SIGNAL(clicked(int)),m_worker,SLOT(slot1(int))); 
        connect(m_worker,SIGNAL(sig1(QString)),m_label,SLOT(setText(QString))); 
        thread->start(); 
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
    QPushButton * m_button; 
    Worker * m_worker; 
};


#endif
