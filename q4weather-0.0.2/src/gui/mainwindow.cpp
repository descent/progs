#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QInputDialog>

#include "mainwindow.h"
#include "../engine/weather.h"

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
	// Mainwindow's size is fixed
	setFixedWidth(236);
	setFixedHeight(235);

	// Use a background
	setAutoFillBackground(true);
	QPalette pal = palette();
        pal.setBrush(QPalette::Window, QBrush(QPixmap(":pics/background.png")));
	setPalette(pal);

	// A engine to retrieve weather information
    //mEngine = new YahooEngine();
    mEngine = new GoogleEngine();
	connect(mEngine, SIGNAL(weatherReady()), this, SLOT(handleData()));
	connect(mEngine, SIGNAL(weatherError()), this, SLOT(handleError()));
	setWindowTitle("Weather - " + mEngine->name());

	mReady = false;

	// For test
	retrieve();
}

MainWindow::~MainWindow()
{
	delete mEngine;
}

void MainWindow::retrieve()
{
	// Update the weather of specified location
//    mEngine->update("Shanghai");
	setWindowTitle("Loading... - " + mEngine->name());
}

void MainWindow::handleData()
{
	mCurrentLocation = mEngine->location();
	mCurrentWeather = mEngine->weather();
	mListForecast = mEngine->forecast();
	
	setWindowTitle(mCurrentLocation.city() + " - " + mEngine->name());

    mReady = true;

	update();
}

void MainWindow::handleError()
{
	setWindowTitle("Error - " + mEngine->name());
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    if (mReady) {
        Q_UNUSED(event);
		QPainter painter(this);
        painter.setRenderHints(QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);

        // draw condition pixmap
        painter.drawPixmap(QRect(50,35,50,50),mCurrentWeather.pixmap());

        // draw current temperature
		painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 28));
        painter.drawText(QRect(150,30,40,40), Qt::AlignCenter,
					 QString::number(mCurrentWeather.temperature()));
        painter.setFont(QFont("Arial", 10));
        painter.drawText(QRect(188,35,10,10), Qt::AlignCenter, "o");

        // draw location's city name
        painter.setFont(QFont("Tarablus", 10));
        painter.drawText(QRect(130,62,70,25), Qt::AlignCenter, mCurrentLocation.city());

        for (int i = 0; i < mListForecast.count(); i++) {
            Weather weather = mListForecast.at(i);

            // draw forecast day
            painter.setFont(QFont("Tarablus", 10));
            painter.drawText(QRect(27+(i%3)*60,86+(i/3)*57,60,14), Qt::AlignCenter, weather.day().toUpper());

            // draw condition pixmap
            painter.drawPixmap(QRect(50+(i%3)*60,105+(i/3*57),33,33), weather.pixmap());

            // draw forecast low and high temperature
            painter.setFont(QFont("Tarablus", 10));
            painter.drawText(QRect(34+(i%3)*60,105+(i/3)*57,12,12), Qt::AlignCenter, QString::number(weather.lowTemp()));
            painter.drawText(QRect(34+(i%3)*60,125+(i/3)*57,12,12), Qt::AlignCenter, QString::number(weather.highTemp()));

        }
			
		mReady = false;
    } else {
		QWidget::paintEvent(event);
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	Q_UNUSED(event);

	QString location;
	location = QInputDialog::getText(this, mEngine->location().city(), tr("Input location:"));

	setWindowTitle("Loading... - " + mEngine->name());
	mEngine->update(location);
}
