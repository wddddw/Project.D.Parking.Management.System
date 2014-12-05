/*
 * cparking.vol1.cpp
 *
 * Created on: 2014.11.27
 * Author: WDD(SCST HBU)
 * School of Computer Science and Technology, Hebei University
 */
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAXSIZE 8 //Max width of a car license#define MAXCAR 2150
#define MAXCUST 10000
struct Customer;

struct Object {
	Customer * cust;
	char kind; //Recording the kind of the object
	string license; //Recording the License of the Car or eBike
	int place[3]; //[0] to Record CS[Where], [1] to Record x, [2] to Record y
};

struct Slot {
	Object * pCAR; //a Point to the element Object
	bool ispark; //Recording the status of the Slot
};

struct Customer {
	string name;
	string address;
	char level;	//Level 't' is teacher, level 's' is student , 'v' is visitor
	Object tool;		//Customer own a car
};

int carnum = 0;
Object cars[MAXCAR];

Slot CS1[2000];
Slot CS2[50];
Slot CS3[100];

const int CS1WIDTH=100;
const int CS1LENGTH=20;
const int CS2WIDTH=5;
const int CS2LENGTH=10;
const int CS3WIDTH=10;
const int CS3LENGTH=10;

string ADMINPASSWD = "0";
string ENTPASSWD = "0";
string EXITPASSWD = "0";

Customer CUST[MAXCUST];
int custnum = 0;

double CHARGETABLE[3];
double TEACHERDISCOUNT;

bool isFull(Slot *p, int, int); //to judge the Parking area if full
int Random(int, int); //to Generate a random number between [a,b]
void RandomSlot(Slot *p, int, int, int &, int &);
int ParkIn(Object, Slot *p, int, int);
int GoOut(Object, Slot, int, int);

void Welcome();

//Functions of Admin Login Mod
void AdminLogin();
void Admin();
void ChangeAdminPasswd();
void SetChargeTable();
void CreateAnAccount();
void SetObject(Object &);

//Functions of Enterance Desk Mod
void EnterLogin();
void Enter();
void ObjectIn();
void AccountIn();
void GuestIn();
void ChangeEntrancePasswd();

//Functions of Exit Desk Mod
void ExitLogin();
void Exit();

bool isFull(Slot *p, int mx, int my) {
	for (int i = 0; i < mx * my; i++)
		if (p[i].ispark == 0)
			return 0;
	return 1;
}

int Random(int m, int n) {
	srand((int) time(NULL));
	int pos, dis;
	if (m == n) {
		return m;
	} else if (m > n) {
		pos = n;
		dis = m - n + 1;
		return rand() % dis + pos;
	} else {
		pos = m;
		dis = n - m + 1;
		return rand() % dis + pos;
	}
}

void RandomSlot(Slot *p, int mx, int my, int & outx, int & outy) {
	int x, y;
	do {
		x = Random(0, mx);
		y = Random(0, my);
	} while (p[my * x + y].ispark == 1);
	outx = x;
	outy = y;
}

int ParkIn(Object temp, Slot *p, int mx, int my) {
	int x, y;
	if (isFull(p, mx, my))
		return -1; //Error Code -1 Parking Area Full
	else {
		RandomSlot(p, mx, my, x, y);
		temp.place[1] = x;
		temp.place[2] = y;
		cars[carnum] = temp;
		p[my * x + y].pCAR = &cars[carnum];
		p[my * x + y].ispark = 1;
		if (carnum <= MAXCAR)
			carnum++;
		return 1; //Return Code 1 Parking Success!
	}
}

int GoOut(Slot *p, int mx, int my, int x, int y) {
	p[my * x + y].ispark = 0;
	return 1;
}

void Welcome() {
	char c;
	while (1) {
		system("cls");
		printf("\t\t----Parking System---\n");
		printf("\t1. Admin Login\n");
		printf("\t2. Entrance Desk\n");
		printf("\t3. Exit Desk\n");
		printf("\tq. Exit\n");
		printf("\tPlease Choose: ");
		setbuf(stdin, NULL);
		scanf("%c", &c);
		switch (c) {
		case '1':
			AdminLogin();
			break;
		case '2':
			EnterLogin();
			break;
		case '3':
			break;
		case 'q':
			return;
			break;
		case 'Q':
			return;
			break;
		default:
			break;
		}
	}
}

void AdminLogin() {
	string temp;
	for (int i = 0; i < 3; i++) {
		system("cls");
		printf("Please Input Admin Password: ");
		cin >> temp;
		if (temp == ADMINPASSWD) {
			Admin();
			return;
		} else {
			if (i == 1)
				printf("Input Error, You have %d time to try!\n", 2 - i);
			else {
				if (i != 2)
					printf("Input Error, You have %d times to try!\n", 2 - i);
			}
			system("pause");
		}
	}
	return;
}

void Admin() {
	char c;
	while (1) {
		system("cls");
		printf("\t\t----Parking System(Admin)---\n");
		printf("\t1. Create An Account\n");
		printf("\t2. Set Charge Table\n");
		printf("\tp. Change Password\n");
		printf("\tq. Admin Exit\n");
		printf("\tPlease Choose: ");
		setbuf(stdin, NULL);
		scanf("%c", &c);
		switch (c) {
		case '1':
			CreateAnAccount();
			break;
		case '2':
			SetChargeTable();
			break;
		case '3':
			break;
		case 'p':
			ChangeAdminPasswd();
			break;
		case 'q':
			return;
			break;
		case 'Q':
			return;
			break;
		default:
			break;
		}
	}
	system("pause");
}

void ChangeAdminPasswd() {
	string temp1, temp2;
	system("cls");
	printf("Please Input the New Password: \n");
	cin >> temp1;
	printf("Please Input Again: \n");
	cin >> temp2;
	if (temp1 == temp2)
		ADMINPASSWD = temp2;
	else {
		system("cls");
		printf("Not Matched! \n");
	}
	return;
}

void SetChargeTable() {
	int area;
	double charge;
	system("cls");
	printf("Please Select Which Area to Change (1 is CS1,2 is CS2,3 is CS3):");
	setbuf(stdin, NULL);
	scanf("%d", &area);
	if (area < 1 || area > 3) {
		system("cls");
		printf("Error!");
		system("pause");
		SetChargeTable();
	} else {
		system("cls");
		printf("Please input the Charge of CS%d: ", area);
		setbuf(stdin, NULL);
		scanf("%lf", &charge);
		switch (area) {
		case 1:
			if (charge > CHARGETABLE[1])
				CHARGETABLE[0] = charge;
			else {
				system("cls");
				printf("Error!");
				system("pause");
			}
			break;
		case 2:
			if (charge > CHARGETABLE[2] && charge < CHARGETABLE[0])
				CHARGETABLE[1] = charge;
			else {
				system("cls");
				printf("Error!");
				system("pause");
			}
			break;
		case 3:
			if (charge < CHARGETABLE[1])
				CHARGETABLE[2] = charge;
			else {
				system("cls");
				printf("Error!");
				system("pause");
			}
			break;
		default:
			break;
		}
	}
	system("cls");
	printf("Please input the Discount of the Teacher: ");
	setbuf(stdin, NULL);
	scanf("%lf", &TEACHERDISCOUNT);
}

void CreateAnAccount() {
	Customer temp;
	string name;
	string address;
	char level;
	Object tool;
	system("cls");
	printf("\t\t---Create Account--\n");
	printf("Please input Username: ");
	setbuf(stdin, NULL);
	cin >> name;
	printf("Pless input user %s's Address: ", name.c_str());
	setbuf(stdin, NULL);
	cin >> address;
	setbuf(stdin, NULL);
	system("cls");
	printf("\t\t---Choose Account Identity--\n");
	printf("\tt.Teacher.\n");
	printf("\ts.Student.\n");
	printf("\tv.Visitor.\n");
	char c;
	scanf("%c", &c);
	switch (c) {
	case 't':
		level = 't';
		break;
	case 's':
		level = 's';
		break;
	case 'v':
		level = 'v';
		break;
	default:
		printf("error!");
		return;
		break;
	}
	temp.name = name;
	temp.level = level;
	temp.address = address;
	SetObject(tool);
	temp.tool=tool;
	tool.cust = &temp;
	CUST[custnum] = temp;
	system("pause");
	custnum++;
}

void SetObject(Object & obj) {
	string licence;
	system("cls");
	printf("\t\t---Please Choose the Kind of the Vehicle---\n");
	printf("\tc.Car.\n");
	printf("\te.e-Bike.\n");
	char c;
	setbuf(stdin, NULL);
	scanf("%c", &c);
	switch (c) {
	case 'c':
		obj.kind = c;
		break;
	case 'e':
		obj.kind = c;
		break;
	default:
		printf("error!");
		system("pause");
		break;
	}
	setbuf(stdin, NULL);
	system("cls");
	printf("Input the licence:");
	cin >> licence;
	obj.license = licence;
}









void EnterLogin(){
	string temp;
	for (int i = 0; i < 3; i++) {
		system("cls");
		printf("Please Input Enter Password: ");
		cin >> temp;
		if (temp == ENTPASSWD) {
			Enter();
			return;
		} else {
			if (i == 1)
				printf("Input Error, You have %d time to try!\n", 2 - i);
			else {
				if (i != 2)
					printf("Input Error, You have %d times to try!\n", 2 - i);
			}
			system("pause");
		}
	}
	return;
}

void Enter(){
	char c;
	while (1) {
		system("cls");
		printf("\t\t----Parking System(Enterance Desk)---\n");
		printf("\t1. Vehicle In\n");
		printf("\tp. Change Password\n");
		printf("\tq. Enterance Exit\n");
		printf("\tPlease Choose: ");
		setbuf(stdin, NULL);
		scanf("%c", &c);
		switch (c) {
		case '1':ObjectIn();
			break;
		case 'p':ChangeEntrancePasswd();
			break;
		case 'q':
			return;
			break;
		case 'Q':
			return;
			break;
		default:
			break;
		}
	}
	system("pause");
}

void ObjectIn(){
	char c;
	while(1){
		system("cls");
		setbuf(stdin, NULL);
		printf("\t\t---Way to Enter---\n");
		printf("\ta. Account\n");
		printf("\tb. Guest\n");
		printf("Please Choose: ");
		scanf("%c",&c);
		switch(c){
		case 'a':
			AccountIn();
			return;
			break;
		case 'b':
			GuestIn();
			return;
			break;
		default:printf("\nError!");system("pause");break;
		}
	}
}

void AccountIn(){
	string acc;
	int flag=-1;
	while(flag==-1){
		system("cls");
		setbuf(stdin, NULL);
		printf("Please Enter Your Account Name:");
		cin>>acc;
		for(int i=0;i<custnum;i++){
			if(acc==CUST[i].name){
				flag=i;
				break;
			}
		}
		if(flag==-1){
			printf("Account Not Found, Please reEnter");
			system("pause");
		}
	}
	if(CUST[flag].tool.kind=='c'){
		ParkIn(CUST[flag].tool,CS1,CS1LENGTH,CS1WIDTH);
		printf("Parkin Success!");
	}
	if(CUST[flag].tool.kind=='e'){
		char c;
		while(c!='2'&&c!='3'){
			system("cls");
			setbuf(stdin, NULL);
			printf("Please Choose Which Parking Space(2 for CS2, 3 for CS3):");
			scanf("%c",&c);
			switch(c){
			case'2':ParkIn(CUST[flag].tool,CS2,CS2LENGTH,CS2WIDTH);break;
			case'3':ParkIn(CUST[flag].tool,CS3,CS3LENGTH,CS3WIDTH);break;
			default:printf("\nError!");system("pause");break;
			}
		}
		printf("Parking Success!");
		system("pause");
	}
}

void GuestIn(){
	bool flag=1;
	char c;
	string lic;
	Object temp;
	while(flag){
		system("cls");
		setbuf(stdin, NULL);
		printf("Please Enter the Vehicle type(c for Car, e for eBike):");
		scanf("%c",&c);
		switch(c){
		case 'c':temp.kind=c;flag=0;break;
		case 'e':temp.kind=c;flag=0;break;
		default:printf("\nError!");system("pause");break;
		}
	}
	system("cls");
	setbuf(stdin, NULL);
	printf("Please Enter The Licence: ");
	cin>>lic;
	temp.license=lic;
	temp.cust=NULL;
	if(temp.kind=='c'){
		ParkIn(temp,CS1,CS1LENGTH,CS1WIDTH);
	}
	else{
		char c;
		while(1){
			system("cls");
			setbuf(stdin, NULL);
			printf("Please Choose Which Parking Space(2 for CS2, 3 for CS3):");
			scanf("%c",&c);
			switch(c){
			case'2':ParkIn(temp,CS2,CS2LENGTH,CS2WIDTH);break;
			case'3':ParkIn(temp,CS3,CS3LENGTH,CS3WIDTH);break;
			default:printf("\nError!");system("pause");break;
			}
		}
	}
}

void ChangeEntrancePasswd() {
	string temp1, temp2;
	system("cls");
	printf("Please Input the New Password: \n");
	cin >> temp1;
	printf("Please Input Again: \n");
	cin >> temp2;
	if (temp1 == temp2)
		ENTPASSWD = temp2;
	else {
		system("cls");
		printf("Not Matched! \n");
		system("pause");
	}
	return;
}

int main() {
	Welcome();
	system("pause");
}
