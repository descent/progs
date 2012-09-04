#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>

#include "yahooeng.h"

YahooEngine::YahooEngine()
{
	// create a QNetworkAccessManager for network communication
	mManager = new QNetworkAccessManager(this);
	connect(mManager, SIGNAL(finished(QNetworkReply*)), 
			this, SLOT(handleData(QNetworkReply*)));

	mCount = 0;

	mState = StateLocation;
	QUrl url = mLocationHost;
	mManager->get(QNetworkRequest(url));
}

YahooEngine::~YahooEngine()
{}

void YahooEngine::update(const QString& location)
{
	// get WOEID first
	mWOEID.clear();
	mState = StateWOEID;;
	mListForecast.clear();
	mListForePixmap.clear();

	QString strurl = mWOEIDHost + 
					 "/v1/places.q('" + location + 
					 "')?appid=[" + mAppId + 
					 "]";
	QUrl url(strurl);
	mManager->get(QNetworkRequest(url));
}

void YahooEngine::handleData(QNetworkReply* reply)
{
	switch (mState) {
		case StateIdle:
			break;

		case StateLocation:
			handleLocation(reply);
			break;
		
		case StateWOEID:
			handleWOEID(reply);
			break;

		case StateWeather:
			handleWeather(reply);
			break;

		case StateIcon:
			handleIcons(reply);
	}
}

void YahooEngine::handleLocation(QNetworkReply* reply)
{
	QString location;

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
}

void YahooEngine::handleWOEID(QNetworkReply* reply)
{
	QString strurl;

	QXmlStreamReader xml(reply->readAll());
	while (!xml.atEnd()) {
		xml.readNext();

		if (xml.tokenType() == QXmlStreamReader::StartElement) {
			// get woeid
			if (xml.name() == "woeid") {
				mWOEID = xml.readElementText();
				strurl = mWeatherHost + "/forecastrss?w=" + mWOEID;
				qDebug() << "WOEID: " << mWOEID;
			}

			// get city name
			if (xml.name() == "name") {
				mCurrentLocation.mCity = xml.readElementText();
				qDebug() << "City: " << mCurrentLocation.mCity;
			}
		}
	}
			
	mState = StateWeather;
	QUrl url(strurl);
	mManager->get(QNetworkRequest(url));
}

void YahooEngine::handleWeather(QNetworkReply* reply)
{
	QXmlStreamReader xml(reply->readAll());

	while (!xml.atEnd()) {
		xml.readNext();

		if (xml.tokenType() == QXmlStreamReader::StartElement) {
			// get current condition
			if (xml.name() == "condition") {
				mCurrentWeather.mCondition = xml.attributes().value("text").toString();
				mCurrentWeather.mTemperature = xml.attributes().value("temp").toString().toInt();
				mCurrentPixmapPath = mIconHost + xml.attributes().value("code").toString() + ".gif";
				qDebug() << "Condition: " << mCurrentWeather.mCondition;
				qDebug() << "Temperature: " << mCurrentWeather.mTemperature;
				qDebug() << "Pixmap path: " << mCurrentPixmapPath;
			}

                        if (xml.name() == "guid") {
                                QString datetime;
                                int y,m,d;
                                datetime = xml.readElementText();
                                y = datetime.mid(9,4).toInt();
                                m = datetime.mid(14,2).toInt();
                                d = datetime.mid(17,2).toInt();
                                mCurrentWeather.mDate = QDate(y,m,d);
                        }
			
			// get forecasted conditions
			if (xml.name() == "forecast") {
				Weather weather;
                                weather.mDay = xml.attributes().value("day").toString();
				weather.mCondition = xml.attributes().value("text").toString();
				weather.mLowTemperature = xml.attributes().value("low").toString().toInt();
				weather.mHighTemperature = xml.attributes().value("high").toString().toInt();

				mListForecast.append(weather);
				mListForePixmap.append(mIconHost + 
									xml.attributes().value("code").toString() + 
									".gif");
				qDebug() << "Forecast"
						 << mListForecast.count()
						 << weather.mCondition 
						 << weather.mLowTemperature
						 << weather.mHighTemperature
						 << mListForePixmap.last();
			}
		}
	}

	mState = StateIcon;
	QUrl url(mCurrentPixmapPath);
	mManager->get(QNetworkRequest(url));
}

void YahooEngine::handleIcons(QNetworkReply* reply)
{
	QFile file("/tmp/condition.png");
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
}


const QString 
	YahooEngine::mAppId = "haTzKIjV34HahDrw6_GbuQAbk.XcusfU5PIYLScLMh7_ILx9FsjulhlC8lZaNTk-";

const QString YahooEngine::mWOEIDHost = "http://where.yahooapis.com";

const QString YahooEngine::mWeatherHost = "http://weather.yahooapis.com";

const QString YahooEngine::mIconHost = "http://l.yimg.com/a/i/us/we/52/";

const QString YahooEngine::mLocationHost = "http://ipinfodb.com/ip_query.php?";
