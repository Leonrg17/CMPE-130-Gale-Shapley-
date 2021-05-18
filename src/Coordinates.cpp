/*
 * Coordinates.cpp
 *
 *  Created on: Apr 24, 2021
 *      Author: darren
 */


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include "Coordinates.h"
using namespace std;


Coordinates::Coordinates() {
	latitude = 0.0;
	longitude = 0.0;
}

/*Coordinates::Coordinates(double lat, double lon) {
	if (lat < -90 || lat > 90) {
		cout << "Invalid latitude..." << endl;
		return;
	}
	if (lon < -180 || lon > 180) {
		cout << "Invalid longitude..." << endl;
		return;
	}
	latitude = lat;
	longitude = lon;
}
*/

ostream& operator<<(ostream& outs, const Coordinates& temp) {
	outs << temp.latitude << ", " << temp.longitude << endl;
	return outs;
}



istream& operator>>(istream& ins, Coordinates &temp) { //read in format mm/dd/yyyy
	ins >> temp.latitude >> temp.longitude;
	if (temp.latitude < -90 || temp.latitude > 90) {
		cout << "Invalid latitude..." << endl;
	}
	if (temp.longitude < -180 || temp.longitude > 180) {
		cout << "Invalid longitude..." << endl;
	}
	return ins;
}

double Coordinates::distance(double lat2, double lon2) {
	double pi = 3.14159265358979323846;
	double dLat = (lat2 - latitude) * pi / 180.0;
	double dLon = (lon2 - longitude) * pi / 180.0;


	latitude = (latitude) * pi / 180.0;
	lat2 = (lat2) * pi / 180.0;


	double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(latitude) * cos(lat2);
	double rad = 6371;
	double c = 2 * asin(sqrt(a));
	return rad * c;
}

double Coordinates::getLatitude() {
	return latitude;
}
double Coordinates::getLongitude() {
	return longitude;
}


