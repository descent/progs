#ifndef TESTCLIENT_H
#define TESTCLIENT_H

#include <QtGui>

#include <unistd.h>

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
      sleep(10);
      qDebug() << "end thread_play()";
      emit sig_play_done();

      //while(1);
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
    void end_thread()
    {
      qDebug() << "thread exit";
      thread_ ->exit(0);
    }

  signals:
    void begin_thread();
private:
    Ui::TestClient ui;

    int requestIdSum;
    int requestIdDiff;
    PlayTicker *play_ticker_;
    QThread *thread_;
};

#endif
