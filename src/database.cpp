/*
 * database.cpp
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
#include <ctime>
#include "Coordinates.h"
#include "Person.h"
#include "Server.h"
#include "database.h"
using namespace std;


database::database() {
	max_size = 10000;
	length = 0;
	pArray = new Person[max_size];
	sArray = new server[max_size];
}

database::database(int size) {
	max_size = size;
	length = 0;
	pArray = new Person[max_size];
	sArray = new server[max_size];
}

Person database::getPerson(int i) {
	return pArray[i];
}

server database::getServer(int i) {
	return sArray[i];
}

string database::getPersonName(int i) {
	return pArray[i].name;
}

string database::randomString(int n) {
	char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
			'h', 'i', 'j', 'k', 'l', 'm', 'n',
			'o', 'p', 'q', 'r', 's', 't', 'u',
			'v', 'w', 'x', 'y', 'z' };

	string name = "";
	for (int i = 0; i < n; i++)
		name = name + alphabet[rand() % 26];

	return name;
}

double database::randomLatitude() {
	double latitude = (rand() % 16000) - 8000;
	double divisor = (rand() % 20) + 88.89888;
	latitude = latitude / divisor;
	return latitude;
}

double database::randomLongitude() {

	double longitude = (rand() % 800) - 400;
	double divisor = (rand() % 20) + 2.322222;
	longitude = longitude / divisor;
	return longitude;
}


void database::writetoFile(int size) {
	string name;
	double lat;
	double lon;
	double lonServer;
	double latServer;
	ofstream fout;
	fout.open("database.txt");
	if(fout.fail()) {
		cout << "file failed to open" << endl;
		exit(1);
	}

	for(int i = 0; i < size; i++) {
		name = randomString(10);
		lat = randomLatitude();
		lon = randomLongitude();
		latServer = randomLatitude();
		lonServer = randomLongitude();

		fout << name << "   " << lat << " " << lon << " " << latServer << " " << lonServer << endl;
	}
}

void database::readfromFile(int size) {
	ifstream fin;
	string name;
	double personLatitude;
	double personLongitude;
	double serverLatitude;
	double serverLongitude;
	int count = 0;


	fin.open("database.txt");
	if(fin.fail()) {
		cout << "Failed to open file. " << endl;
		exit(1);
	}

	while(!fin.eof()) {
		fin >> name >> personLatitude >> personLongitude >> serverLatitude >> serverLongitude;

		pArray[count].name = name;
		pArray[count].place.latitude = personLatitude;
		pArray[count].place.longitude = personLongitude;

		sArray[count].place.latitude = serverLatitude;
		sArray[count].place.longitude = serverLongitude;

		count++;
	}

	for(int i = 0; i < size+1; i++){
		pArray[i].personNum = i;
		sArray[i].serverNum = i + size;
	}
}

void database::consoleOutput(int size) {
	for(int i = 0; i < size+1; i++) {
		cout << "#" << pArray[i].personNum << "  " << "Name: " << pArray[i].name << "  Latitude: " << pArray[i].place.latitude << "  Longitude: " << pArray[i].place.longitude << endl;
		cout << "#" << sArray[i].serverNum << "  " << "Server - Latitude: " << sArray[i].place.latitude << "  Longitude: " << sArray[i].place.longitude << endl;
		cout << endl;
	}
}



database::~database() {
	delete [] pArray;
	delete [] sArray;

}


/*
void database::swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void database::selectionSort(int arr[], int n)
{
	int i, j, min_idx;


	for (i = 0; i < n-1; i++)
	{
		min_idx = i;
		for (j = i+1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;
		swap(&arr[min_idx], &arr[i]);
	}
}


double database::distance(int p, int s) {

	double pi = 3.14159265358979323846;
	double dLat = (sArray[s].place.latitude - pArray[p].place.latitude) * pi / 180.0;
	double dLon = (sArray[s].place.longitude - pArray[p].place.longitude) * pi / 180.0;

	pArray[p].place.latitude = (pArray[p].place.latitude) * pi / 180.0;
	sArray[s].place.latitude = (sArray[s].place.latitude) * pi / 180.0;

	double z = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(pArray[p].place.latitude) * cos(sArray[s].place.latitude);
	double rad = 6371;
	double c = 2 * asin(sqrt(z));
	return rad * c;
}


void database::rankDistance(int size) {
	int tempPerson[max_size]; // hold person's server ranking number max_size - 2*max_size
	int tempServer[max_size]; // hold server's person ranking number 0 - max_size -1

	for(int p = 0; p < size; p++) {
		for(int s = 0; s < size; s++) {
			preference[s+size][p] = preference[p][s] = distance(p, s); //people's ranking of servers
		}
	}

	//sort list from least distance to greatest
	for(int p = 0; p < 2*size; p++) {
		selectionSort(preference[p], size);

	}
}



void database::displayRanking(int size) {
	for(int p = 0; p < size; p++) {
		cout << "Person " << p << " Ranking: ";
		for(int s = 0; s < size; s++) {
			cout << preference[p][s] << ", ";
		}
		cout << endl;
	}

	for(int p = 0; p < size; p++) {
		cout << "Server " << p << " Ranking: ";
		for(int s = 0; s < size; s++) {
			cout << preference[p+size][s] << ", ";
		}
		cout << endl;
	}
}
*/
