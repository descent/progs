#ifndef GOOGLEENGINE_H
#define GOOGLEENGINE_H

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QXmlStreamReader>

#include "engine.h"

class GoogleEngine : public Engine
{
	Q_OBJECT

public:
	GoogleEngine();
	~GoogleEngine();

	void update(const QString& location);
	QString name() { return "Google"; }

private slots:
	void handleData(QNetworkReply* reply);
	void handleLocation(QNetworkReply* reply);
	void handleWeather(QNetworkReply* reply);
	void handleIcon(QNetworkReply* reply);

private:
	QString getDataAttr(QXmlStreamReader& xml);

private:
	static const QString mLocationHost;
	static const QString mHost;
	QNetworkAccessManager* mManager;

	enum {
		StateIdle,
		StateLocation,
		StateWeather,
		StateIcon,
	} mState;
	int mCount;
	QString mCurrentPixmapPath;
	QList<QString> mListForePixmap;
};

#endif
