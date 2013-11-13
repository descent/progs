#ifndef TESTCLIENT_H
#define TESTCLIENT_H

#include <QtGui>

#include "ui_testclient.h"

class PlayTicker : public QObject
{
  Q_OBJECT
  public:
    PlayTicker (QObject * parent = 0 )
    {
    }

  signals:
    void sig_play_done();
  public slots:
    void thread_play()
    {
      qDebug() << "currentThreadId(): " <<  QThread::currentThreadId();
      while(1);
    }

  private:
};


class TestClient: public QWidget {
Q_OBJECT
public:
    TestClient(QWidget *parent=0);
    virtual ~TestClient();
public slots:
    void sendRequest();
private slots:
    void processReturnValue( int requestId, QVariant value );
    void processFault( int requestId, int errorCode, QString errorString );

  signals:
    void begin_thread();
private:
    Ui::TestClient ui;

    int requestIdSum;
    int requestIdDiff;
    PlayTicker *play_ticker_;
};

#endif
