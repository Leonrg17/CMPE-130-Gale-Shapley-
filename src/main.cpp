//============================================================================
// Name        : Test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <chrono>
#include "Coordinates.h"
#include "Person.h"
#include "Server.h"
#include "database.h"

#define ARRAY_SIZE 5

using namespace std;

//************* Helping Functions *******************

double distance(Person a, server b);
//Calculates the distance in kilometers between a person and server with given latitude and longitude values

void sortRowWise(int array[][ARRAY_SIZE], int rank[][ARRAY_SIZE], int size);
//first sorts each array of distances from closest to farthest,
//and at the same time sorts the "rank" array from closest server/person to farthest

void swap(int *xp, int *yp);


//************* Arrays with Distance between server and person ***************

void Rank(database d, int pArray[][ARRAY_SIZE], int sArray[][ARRAY_SIZE], int pRank[][ARRAY_SIZE], int sRank[][ARRAY_SIZE], int size);
//first calculates the distance between each server and person,
//then sorts each array from closest to farthest

void displayRanking(int pArray[][ARRAY_SIZE], int sArray[][ARRAY_SIZE], int size);
//displays the distances in kilometers of each person/server from each other

void fillPrefer(int prefer[2 * ARRAY_SIZE][ARRAY_SIZE], int pRank[][ARRAY_SIZE], int sRank[][ARRAY_SIZE]);
//array "prefer" hold each persons ranking of servers from indexes 0 to (ARRAY_SIZE - 1)
//and each server's ranking of people from indexes ARRAY_SIZE to 2*ARRAY_SIZE


void setPreferences(int pPreference[][ARRAY_SIZE], int sPreference[][ARRAY_SIZE]);
void displayPreferences(int pPreference[][ARRAY_SIZE], int sPreference[][ARRAY_SIZE]);
//displays each persons ranking by server #
//and each server's ranking by person #


//************* Main Algorithm: Stable Marriage *****************

bool serverPreference(int prefer[2 * ARRAY_SIZE][ARRAY_SIZE], int server, int person, int person1);
//checks if variable person1 or person is ranked closer in the servers preference list
// and chooses the closest ranking person of the two

void stableMarriage(int prefer[2 * ARRAY_SIZE][ARRAY_SIZE], database d);





int main() {

	srand((unsigned) time(0));

	int personRanking[ARRAY_SIZE][ARRAY_SIZE];
	int personPreference[ARRAY_SIZE][ARRAY_SIZE];

	int serverRanking[ARRAY_SIZE][ARRAY_SIZE];
	int serverPreference[ARRAY_SIZE][ARRAY_SIZE];

	int prefer[2*ARRAY_SIZE][ARRAY_SIZE];


	database earth(ARRAY_SIZE);
	earth.writetoFile(ARRAY_SIZE);
	earth.readfromFile(ARRAY_SIZE);



	setPreferences(personPreference, serverPreference);
	Rank(earth, personRanking, serverRanking, personPreference, serverPreference, ARRAY_SIZE);
	fillPrefer(prefer, personPreference, serverPreference);
	cout << endl << endl;

	stableMarriage(prefer, earth);


	return 0;
}





void Rank(database d, int pArray[][ARRAY_SIZE], int sArray[][ARRAY_SIZE], int pRank[][ARRAY_SIZE], int sRank[][ARRAY_SIZE], int size) {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			//sArray[j][i] = pArray[i][j] = distance(d.pArray[i], d.sArray[j]);
			sArray[j][i] = pArray[i][j] = distance(d.getPerson(i), d.getServer(j));
		}
	}


	for(int p = 0; p < size; p++) {
		sortRowWise(pArray, pRank, size);
		sortRowWise(sArray, sRank, size);
	}

}

double distance(Person a , server b) {
	double pi = 3.14159265358979323846;
	double dLat = (b.place.latitude - a.place.latitude) * pi / 180.0;
	double dLon = (b.place.longitude -a.place.longitude) * pi / 180.0;


	a.place.latitude = (a.place.latitude) * pi / 180.0;
	b.place.latitude = (b.place.latitude) * pi / 180.0;


	double z = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(a.place.latitude) * cos(b.place.latitude);
	double rad = 6371;
	double c = 2 * asin(sqrt(z));
	return rad * c;
}

void sortRowWise(int array[][ARRAY_SIZE], int rank[][ARRAY_SIZE], int size) {
	for (int i = 0; i < size; i++)
	{
		// loop for column of matrix
		for (int j = 0; j < size; j++)
		{
			// loop for comparison and swapping
			for (int k = 0; k < size - j - 1; k++)
			{
				if (array[i][k] > array[i][k + 1])
				{
					// swapping of elements
					swap(array[i][k], array[i][k + 1]);
					swap(rank[i][k], rank[i][k + 1]);
				}
			}
		}
	}
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void displayRanking(int pArray[][ARRAY_SIZE], int sArray[][ARRAY_SIZE], int size) {
	for(int p = 0; p < size; p++) {
		cout << "Person " << p << " Ranking: ";
		for(int s = 0; s < size; s++) {
			cout << pArray[p][s] << ", ";
		}
		cout << endl;
	}

	cout << endl;

	for(int p = 0; p < size; p++) {
		cout << "Server " << p << " Ranking: ";
		for(int s = 0; s < size; s++) {
			cout << sArray[p][s]<< ", ";

		}
		cout << endl;
	}

}

void fillPrefer(int prefer[2*ARRAY_SIZE][ARRAY_SIZE], int pRank[][ARRAY_SIZE], int sRank[][ARRAY_SIZE]) {
	//0-4 is people, ARRAY_SIZE-9 is servers
	for (int i = 0; i < ARRAY_SIZE; i++) {
		//cout << "Person " << i << " Ranking: ";

		//fill with people ranking of servers
		for (int j = 0; j < ARRAY_SIZE; j++) {
			prefer[i][j] = pRank[i][j];
			//cout << prefer[i][j] - ARRAY_SIZE << ", ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < ARRAY_SIZE; i++) {
		//cout << "Server " << i << " Ranking: ";
		//fill with people ranking of servers

		for (int j = 0; j < ARRAY_SIZE; j++) {
			prefer[i+ARRAY_SIZE][j] = sRank[i][j];
			//cout << prefer[i+ARRAY_SIZE][j]<< ", ";
		}
		cout << endl;
	}

}

void setPreferences(int pPreference[][ARRAY_SIZE], int sPreference[][ARRAY_SIZE]){
	for(int i = 0; i < ARRAY_SIZE; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++){
			pPreference[i][j] = j + ARRAY_SIZE; // servers from ARRAY_SIZE-9
			sPreference[i][j] = j; // people from 0 - 4
		}
	}
}

void displayPreferences(int pPreference[][ARRAY_SIZE], int sPreference[][ARRAY_SIZE]) {
	for(int i = 0; i < ARRAY_SIZE; i++) {
		cout << "Person " << i<< ": ";
		for (int j = 0; j < ARRAY_SIZE; j++){
			cout << pPreference[i][j] << ", "; // servers from ARRAY_SIZE-9
		}
		cout << endl;
	}
	cout << endl;

	for(int i = 0; i < ARRAY_SIZE; i++) {
		cout << "Server " << i << ": ";
		for (int j = 0; j < ARRAY_SIZE; j++){
			cout << sPreference[i][j] << ", "; // servers from ARRAY_SIZE-9
		}
		cout << endl;
	}
	cout << endl;

}

bool serverPreference(int prefer[2 * ARRAY_SIZE][ARRAY_SIZE], int server, int person, int person1) {
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (prefer[server][i] == person1) {
			return true;
		}

		if (prefer[server][i] == person) {
			return false;
		}
	}
	return false;
}

void stableMarriage(int prefer[2 * ARRAY_SIZE][ARRAY_SIZE], database d) {
	int serverPartner[ARRAY_SIZE];

	bool peopleFree[ARRAY_SIZE];

	memset(serverPartner, -1, sizeof(serverPartner));
	memset(peopleFree, false, sizeof(peopleFree));



	int freeCount = ARRAY_SIZE;


	while (freeCount > 0)
	{
		int person;
		for (person = 0; person < ARRAY_SIZE; person++)
			if (peopleFree[person] == false)
				break;


		for (int i = 0; i < ARRAY_SIZE && peopleFree[person] == false; i++)
		{
			int server = prefer[person][i];


			if (serverPartner[server - ARRAY_SIZE] == -1)
			{
				serverPartner[server - ARRAY_SIZE] = person;
				peopleFree[person] = true;
				freeCount--;
			}

			else
			{

				int person1 = serverPartner[server - ARRAY_SIZE];
				if (serverPreference(prefer, server, person, person1) == false)
				{
					serverPartner[server - ARRAY_SIZE] = person;
					peopleFree[person] = true;
					peopleFree[person1] = false;
				}
			}
		}
	}

	/*
	for(int i = 0; i < ARRAY_SIZE; i++) {
		//cout << "Server " << i << " matches with " << d.pArray[serverPartner[i]].name << endl;
		cout << "Server " << i << " matches with " << d.getPersonName(serverPartner[i]) << endl;
	}

	cout << endl << "Server   Person" << endl;
	    for (int i = 0; i < ARRAY_SIZE; i++)
	       cout << " " << i << "\t   " << serverPartner[i] << endl;
	*/
}
