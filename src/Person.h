/*
 * Person.h
 *
 *  Created on: Apr 24, 2021
 *      Author: darren
 */
#include <iostream>
#include <string>
#include "Coordinates.h"

using namespace std;
#ifndef PERSON_H_
#define PERSON_H_

class Person{
public:

 //Person(int personNum = 0, string name = "N/A" , Coordinates place = Coordinates(0,0)  ): personNum(personNum), name(name), place(place) {};
 Person();

 friend ostream& operator<<(ostream& out,const Person& test);


 void operator=(const Person& temp);



 string name;
 Coordinates place;
 int personNum;
};




#endif /* PERSON_H_ */
