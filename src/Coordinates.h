/*
 * Coordinates.h
 *
 *  Created on: Apr 24, 2021
 *      Author: darren
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;
#ifndef COORDINATES_H_
#define COORDINATES_H_

class Coordinates { //coordinates based on latitude and longitude
public:
	Coordinates();
	//Coordinates(double lat = 0, double lon = 0);

	friend ostream& operator<<(ostream& outs, const Coordinates &temp);
	friend istream& operator>>(istream& ins, Coordinates &temp);

	double distance(double lat2, double lon2);
	double getLatitude();
	double getLongitude();


	double latitude;
	double longitude;

};



#endif /* COORDINATES_H_ */
