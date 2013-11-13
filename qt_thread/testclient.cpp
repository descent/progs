#include <QApplication>
#include <QMessageBox>

#include "testclient.h"

TestClient::TestClient(QWidget *parent)
    :QWidget(parent)
{
    ui.setupUi(this);

    ui.x->setValidator( new QIntValidator( this ) );
    ui.y->setValidator( new QIntValidator( this ) );

    requestIdSum = -1;
    requestIdDiff = -1;

    connect( ui.callButton, SIGNAL(clicked()), SLOT(sendRequest()) );
    connect( ui.exitButton, SIGNAL(clicked()), qApp, SLOT(quit()) );
    
}

TestClient::~TestClient()
{
}

void TestClient::sendRequest()
{
  // create thread
  play_ticker_ = new PlayTicker();
 
  connect(this, SIGNAL(begin_thread() ), play_ticker_, SLOT(thread_play()));
  connect(play_ticker_, SIGNAL(sig_play_done() ), this, SLOT(end_thread()));

  thread_ = new QThread(this);
  play_ticker_->moveToThread(thread_);
  thread_->start();
  emit begin_thread();
}

void TestClient::processReturnValue( int requestId, QVariant value )
{
    Q_ASSERT( value.canConvert( QVariant::Int ) );
    
    if ( requestId == requestIdSum )
        ui.sum->setText( QString::number( value.toInt() ) );
    
    if ( requestId == requestIdDiff )
        ui.difference->setText( QString::number( value.toInt() ) );
}

void TestClient::processFault( int requestId, int errorCode, QString errorString )
{
    Q_UNUSED( requestId );

    QMessageBox::warning(this, tr("Request failed"),
            QString("XML-RPC request  failed.\n\nFault code: %1\n%2\n") \
            .arg(errorCode).arg(errorString),
            QMessageBox::Ok );

}


