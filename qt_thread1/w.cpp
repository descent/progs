#include "w.h"

Widget::Widget():m_label(new QLabel), m_button(new QPushButton("Button")), m_worker(new Worker) 
{ 
  button_ = new QPushButton("Button2");  
  new MyWidget(this);
  new MyWidget(this);

        QVBoxLayout * vbox = new QVBoxLayout(this); 
        vbox->addWidget(m_label); 
        vbox->addWidget(m_button); 
        vbox->addWidget(button_); 
        setLayout(vbox); 
        thread = new QThread(this); 
        m_worker->moveToThread(thread); 
         connect(m_button,SIGNAL(clicked()),this,SLOT(onButtonClicked())); 
        connect(this,SIGNAL(clicked(int)),m_worker,SLOT(slot1(int))); 
        connect(m_worker,SIGNAL(sig1(QString)),m_label,SLOT(setText(QString))); 
        thread->start(); 
} 


MyWidget::MyWidget ( QWidget * parent, Qt::WindowFlags f)
  : QWidget(parent, f)
{
}

MyWidget::~MyWidget()
{
  qDebug() << "MyWidget::~MyWidget()";
}
