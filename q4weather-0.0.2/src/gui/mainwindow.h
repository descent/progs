#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#include "../engine/yahooeng.h"
#include "../engine/googleeng.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);
	~MainWindow();

protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);

private slots:
	void retrieve();
	void handleData();
	void handleError();

private:
	Engine* mEngine;
	bool mReady;

	Location mCurrentLocation;
	Weather mCurrentWeather;
	QList<Weather> mListForecast;
};

#endif
