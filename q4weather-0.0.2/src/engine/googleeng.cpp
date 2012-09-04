#include <QDomDocument>
#include <QDomDocumentType>
#include <QFile>
#include <QDebug>

#include "googleeng.h"

GoogleEngine::GoogleEngine()
{
	mManager = new QNetworkAccessManager(this);
	connect(mManager, SIGNAL(finished(QNetworkReply*)), 
			this, SLOT(handleData(QNetworkReply*)));

	mCount = 0;
	
	mState = StateLocation;
	QUrl url;
	url = mLocationHost;;
	mManager->get(QNetworkRequest(url));
}

GoogleEngine::~GoogleEngine()
{}


void GoogleEngine::update(const QString& location)
{
	QUrl url;

	mState = StateWeather;
	mCount = 0;
	mListForecast.clear();
	mListForePixmap.clear();

	url = mHost + "/ig/api";
	url.addEncodedQueryItem("weather", location.toLatin1());

	mManager->get(QNetworkRequest(url));
}
	
QString GoogleEngine::getDataAttr(QXmlStreamReader& xml)
{
	return xml.attributes().value("data").toString();
}

void GoogleEngine::handleData(QNetworkReply* reply)
{
	switch (mState) {
		case StateLocation:
			handleLocation(reply);
			break;

		case StateWeather:
			handleWeather(reply);
			break;

		case StateIcon:
			handleIcon(reply);
			break;

		default:
			break;
	}
}

void GoogleEngine::handleLocation(QNetworkReply* reply)
{
	QString location;

	if (reply->error() == QNetworkReply::NoError) {
		QXmlStreamReader xml(reply->readAll());
		while (!xml.atEnd()) {
			xml.readNext();
			if (xml.tokenType() == QXmlStreamReader::StartElement) {
				if (xml.name() == "City") {
					location = xml.readElementText();
					break;
				}
			}
		}

		update(location);
	} else {
		mState = StateIdle;
		emit weatherError();
	}
}

void GoogleEngine::handleWeather(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError) {
		QXmlStreamReader xml(reply->readAll());
		while (!xml.atEnd()) {
			xml.readNext();
			if (xml.tokenType() == QXmlStreamReader::StartElement) {
						// Start of forecast_information
						// get location
				if (xml.name() == "forecast_information") {
					while(!xml.atEnd()) {
						xml.readNext();
				
						if (xml.tokenType() == QXmlStreamReader::StartElement) {
							if (xml.name() == "city") {
								mCurrentLocation.mCity = getDataAttr(xml).section(",",0,0);
							}
						}
 
						// End of forecast_information
						if (xml.name() == "forecast_information") {
							break;
						}
					}
				}
						// Start of current_conditions
				if (xml.name() == "current_conditions") {
					while(!xml.atEnd()) {
						xml.readNext();

						if (xml.tokenType() == QXmlStreamReader::StartElement) {
							if (xml.name() == "condition") {
								mCurrentWeather.mCondition = getDataAttr(xml);
							}
	
							if (xml.name() == "temp_f") {
								mCurrentWeather.mTemperature = getDataAttr(xml).toInt();
							}
	
							if (xml.name() == "icon") {
								mCurrentPixmapPath = mHost + getDataAttr(xml);
							}
						}

						// End of current_conditions
						if (xml.name() == "current_conditions") {
							break;
						}
					}
				}
					// Start of forecast_conditions
				if (xml.name() == "forecast_conditions") {
					Weather weather;
					while (!xml.atEnd()) {
						xml.readNext();

						if (xml.tokenType() == QXmlStreamReader::StartElement) {
							if (xml.name() == "day_of_week") {
								weather.mDay = getDataAttr(xml).toUpper();
							}
	
							if (xml.name() == "low") {
								weather.mLowTemperature = getDataAttr(xml).toInt();
							}
						
							if (xml.name() == "high") {
								weather.mHighTemperature = getDataAttr(xml).toInt();
							}
						
							if (xml.name() == "icon") {
								mListForePixmap.append(mHost + getDataAttr(xml));
							}
						}

						// End of forecst_conditions
						if (xml.name() == "forecast_conditions") {
							mListForecast.append(weather);
							break;
						}
					}
				}
			}
		}

		qDebug() << mCurrentWeather.mCondition;
		qDebug() << mCurrentWeather.mTemperature;
		qDebug() << mCurrentPixmapPath;
		for (int i = 0; i < mListForecast.count(); i++) {
			qDebug() << mListForecast[i].mLowTemperature;
			qDebug() << mListForecast[i].mHighTemperature;
			qDebug() << mListForePixmap[i];
		}

		mState = StateIcon;
		QUrl url = mCurrentPixmapPath;
		mManager->get(QNetworkRequest(url));
	} else {
		mState = StateIdle;
		emit weatherError();
	}
}

void GoogleEngine::handleIcon(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError) {
		QFile file("/tmp/condition.gif");
		file.open(QIODevice::ReadWrite | QIODevice::Truncate);
		file.write(reply->readAll());
		file.close();
		QPixmap pixmap(file.fileName());
	
		if (mCount == 0) {
			mCurrentWeather.mConditionPixmap = pixmap;
			QUrl url(mListForePixmap.at(mCount));
			mManager->get(QNetworkRequest(url));
			mCount++;
		} else if (mCount <= mListForecast.count()) {
			mListForecast[mCount - 1].mConditionPixmap = pixmap;
			mCount++;
			if (mCount > mListForecast.count()) {
				mCount = 0;
				mState = StateIdle;
				emit weatherReady();
			} else {
				QUrl url(mListForePixmap[mCount - 1]);
				mManager->get(QNetworkRequest(url));
			}
		}
	} else {
		mState = StateIdle;
		emit weatherError();
	}
}

const QString GoogleEngine::mHost = QString("http://www.google.com");
const QString GoogleEngine::mLocationHost = QString("http://ipinfodb.com/ip_query.php?");
