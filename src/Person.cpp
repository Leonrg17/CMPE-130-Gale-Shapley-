/*
 * Person.cpp
 *
 *  Created on: Apr 24, 2021
 *      Author: darren
 */

#include <iostream>
#include <string>
#include "Coordinates.h"
#include "Person.h"

Person::Person() {
	personNum = 0;
	name = "N/A";
	Coordinates place;
}
ostream& operator<<(ostream& out, const Person& test){
    out<<"Name: "<< test.name << endl << "Latitude: "<<test.place.latitude<<endl<< "Longitude: "<<test.place.longitude<<endl;
    return out;
}

void Person::operator=(const Person& temp){

    name = temp.name;
    personNum = temp.personNum;
    place.latitude = temp.place.latitude;
    place.longitude = temp.place.longitude;

}

