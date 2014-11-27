/*
 * cparking.vol1.cpp
 *
 *  Created on: 2014.11.27
 *      Author: WDD
 */
#include <cstdio>
#include <string>
#include <cstdlib>
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

int carnum=0;
Object cars[MAXCAR];

Slot CS1[2000];
Slot CS2[50];
Slot CS3[100];

bool isFull(Slot *p,int,int);	//to judge the Parking area if full
int Random(int , int );		//to Generate a random number between [a,b]
void RandomSlot(Slot *p,int,int,int &,int &);
int ParkIn(Object,Slot *p,int,int);







bool isFull(Slot *p,int mx,int my){
	for(int i=0;i<mx*my;i++)
		if(p[i].ispark==0) return 0;
	return 1;
}

int Random(int m, int n){
	srand((int)time(NULL));
    int pos, dis;
    if(m == n){
		return m;
	}
	else if(m > n){
		pos = n;
		dis = m - n + 1;
		return rand() % dis + pos;
	}
	else{
		pos = m;
		dis = n - m + 1;
		return rand() % dis + pos;
	}
}

void RandomSlot(Slot *p,int mx,int my,int & outx,int & outy){
	int x,y;
	do{
		x=Random(0,mx);
		y=Random(0,my);
	}while(p[my*x+y].ispark==1);
	outx=x;
	outy=y;
}

int ParkIn(Object temp,Slot *p,int mx,int my){
	int x,y;
	if(isFull(p,mx,my)) return -1;	//Error Code -1 Parking Area Full
	else{
		RandomSlot(p,mx,my,x,y);
		temp.place[1]=x;
		temp.place[2]=y;
		cars[carnum]=temp;
		p[my*x+y].pCAR=&cars[carnum];
		if(carnum<=MAXCAR) carnum++;
		return 1;					//Return Code 1 Parking Success!
	}
}


int main(){
	int t_num=0;
	Object temp;
	temp.kind='c';
	temp.license="wwyydd";
	temp.place[0]=1;
	temp.rank=1;
	//Test parking
	while(ParkIn(temp,CS1,100,20)!=-1){
		t_num++;
		printf("%d\n",t_num);
	}
	printf("%d\n",t_num);
	system("pause");
}
