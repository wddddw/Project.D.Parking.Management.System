/*
 * cparking.vol1.cpp
 *
 *  Created on: 2014.11.27
 *      Author: WDD
 */
#include <cstdio>
#include <string>
#include <cstdio>
#include <ctime>
using namespace std;
#define MAXSIZE 8			//Max width of a car license
#define MAXCAR 2150

struct Object{
	int rank;				//Recording Level of the Customer
	char kind;				//Recording the kind of the object
	string license;			//Recording the License of the Car or eBike
	int place[3];			//[0] to Record CS[Where], [1] to Record x, [2] to Record y
};

struct Slot{
	Object * pCAR;			//a Point to the element Object
	bool ispark;			//Recording the status of the Slot
};

Object cars[MAXCAR];

Slot CS1[100][20];
Slot CS2[5][10];
Slot CS3[10][10];

void Random(Slot *,int,int);









void Random(Slot ** p,int mx,int my){
	int x,y;
	while(p[x][y].ispark==1){

	}
}
