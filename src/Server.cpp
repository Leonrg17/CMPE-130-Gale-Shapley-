/*
 * Server.cpp
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
#include "Server.h"
using namespace std;

server::server() {
	serverNum = 0;
	Coordinates place;
}

void server::operator=(const server& temp){

	serverNum = temp.serverNum;
    place.latitude = temp.place.latitude;
    place.longitude = temp.place.longitude;

}

ostream& operator<<(ostream& out, const server& test){
    out<<"Latitude: "<<test.place.latitude<<endl<< "Longitude: "<<test.place.longitude<<endl;
    return out;
}

