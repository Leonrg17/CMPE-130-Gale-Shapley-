/*
 * database.h
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
#include "Person.h"
#include "Server.h"
using namespace std;
#ifndef DATABASE_H_
#define DATABASE_H_


class database {

public:

	database();
	database(int size);

	void readfromFile(int size);
	void writetoFile(int size);
	string randomString(int n);
	double randomLatitude();
	double randomLongitude();

	void consoleOutput(int size);
	double distance(int p, int s);
	void rankDistance(int size);
	//void selectionSort(int arr[], int n);
	//void swap(int *xp, int *yp);

	void displayRanking(int size);

	Person getPerson(int i);
	server getServer(int i);
	string getPersonName(int i);
	~database();


private:
	Person *pArray;
	server *sArray;

	int max_size;
	int length;

};


#endif /* DATABASE_H_ */
