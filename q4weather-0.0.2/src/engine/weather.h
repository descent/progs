#ifndef WEATHER_H
#define WEATHER_H

#include <QString>
#include <QDate>
#include <QPixmap>

class Weather
{
friend class YahooEngine;
friend class GoogleEngine;

public:
	Weather() {;}
	~Weather() {;}

	QString condition() const { return mCondition; }
	int temperature() const { return mTemperature; }
	int lowTemp() const { return mLowTemperature; }
	int highTemp() const { return mHighTemperature; }
	QPixmap pixmap() const { return mConditionPixmap; }
        QString day() const { return mDay; }

private:
	QDate mDate;
        QString mDay;
	QString mCondition;
	int mTemperature;
	int mLowTemperature;
	int mHighTemperature;
	QPixmap mConditionPixmap;
};

#endif
