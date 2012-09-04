#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

#include "weather.h"
#include "location.h"

class Engine : public QObject
{
	Q_OBJECT

public:
	Engine() {;}
	virtual ~Engine() {;}

	// Engine's name
	virtual QString name() = 0;

	// Update location's weather
	virtual void update(const QString& location) = 0;

	// get location's current weather
	Weather weather() const { return mCurrentWeather; }

	// get location's information
	Location location() const { return mCurrentLocation; }

	// get the list of forecast
	QList<Weather> forecast() const { return mListForecast; }

signals:
	void weatherReady();  // emit this when weather data is ready
	void weatherError();  // emit this when weahter data is wrong

protected:
	Location mCurrentLocation;
	Weather mCurrentWeather;
	QList<Weather> mListForecast;
};

#endif
