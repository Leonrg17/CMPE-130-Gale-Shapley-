/*
 * Server.h
 *
 *  Created on: Apr 24, 2021
 *      Author: darren
 */
#include <iostream>
#include <string>
#include "Coordinates.h"
#ifndef SERVER_H_
#define SERVER_H_

class server{

public:

	//server(int serverNum = 0, Coordinates place = Coordinates(0,0)): serverNum(serverNum), place(place) {};

	server();
	friend ostream& operator<<(ostream& out,const server& test);
	void operator = (const server& temp);


	Coordinates place;
	int serverNum;

};




#endif /* SERVER_H_ */
