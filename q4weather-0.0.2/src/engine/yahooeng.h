#ifndef YAHOOENG_H
#define YAHOOENG_H

#include <QNetworkReply>

#include "engine.h"

class YahooEngine : public Engine
{
	Q_OBJECT

public:
	YahooEngine();
	~YahooEngine();

	void update(const QString& location);
	QString name() { return "Yahoo!"; }

private slots:
	void handleData(QNetworkReply*);
	void handleLocation(QNetworkReply*);
	void handleWOEID(QNetworkReply*);
	void handleWeather(QNetworkReply*);
	void handleIcons(QNetworkReply*);

private:
	QString mWOEID;
	QNetworkAccessManager* mManager;
	enum {
		StateIdle,
		StateLocation,
		StateWOEID,
		StateWeather,
		StateIcon
	} mState;

	int mCount;
	QString mCurrentPixmapPath;
	QList<QString> mListForePixmap;

	static const QString mAppId;
	static const QString mWOEIDHost;
	static const QString mWeatherHost;
	static const QString mIconHost;
	static const QString mLocationHost;
};

#endif
