#ifndef LOCATION_H
#define LOCATION_H

class Location
{
friend class YahooEngine;
friend class GoogleEngine;

public:
	Location() {;}
	~Location() {;}
	QString city() const { return mCity; }
	QString state() const { return mState; }
	QString country() const { return mCountry; }

private:
	QString mCity;
	QString mState;
	QString mCountry;
};

#endif
