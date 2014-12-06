/*
 * cparking.vol1.cpp
 *
 * Created on: 2014.11.27
 * Author: Team WL
 * Release: WDD@SCST
 */
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAXSIZE 8

//Max width of a car LICENSE

#define MAXCAR 2150
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

const int CS1WIDTH = 100;
const int CS1LENGTH = 20;
const int CS2WIDTH = 5;
const int CS2LENGTH = 10;
const int CS3WIDTH = 10;
const int CS3LENGTH = 10;

string ADMINPASSWD = "0";
string ENTPASSWD = "0";
string EXITPASSWD = "0";

Customer CUST[MAXCUST];
int custnum = 0;

double CHARGETABLE[3] = { 10, 5, 5 };
double TEACHERDISCOUNT = 0.8;
double STUDENTDISCOUNT = 0.6;

//Basic Function [Including Parking Algorithm]
bool isFull(Slot *p, int, int); //to judge the Parking area if full
int Random(int, int); //to Generate a random number between [a,b]
void RandomSlot(Slot *p, int, int, int &, int &);
int ParkIn(Object &, Slot *p, int, int);
int GoOut(Slot *, int, int, int, int);

//Welcome
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
void ChangeExitPasswd();
void LetObjectOut();
void AccountOut();
void GuestOut();

/*
 * Basic Function Start
 */
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

int ParkIn(Object &temp, Slot *p, int mx, int my) {
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
	int tmp = 0;
	p[my * x + y].ispark = 0;
	for (int i = 0; i < carnum; i++) {
		if (cars[i].place[1] == x && cars[i].place[2] == y) {
			tmp = i;
			break;
		}
	}
	for (int i = tmp; i < carnum - 1; i++) {
		cars[i] = cars[i + 1];
	}
	carnum--;
	return 1;
}

/*
 * Basic Function End
 */

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
			ExitLogin();
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

/*
 * Admin Mod Start
 */
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
	printf("Please input the Discount of the Student: ");
	setbuf(stdin, NULL);
	scanf("%lf", &STUDENTDISCOUNT);
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
	temp.tool = tool;
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

/*
 * Admin Mod End
 */

/*
 * Enterance Desk Mod Start
 */

void EnterLogin() {
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

void Enter() {
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
		case '1':
			ObjectIn();
			break;
		case 'p':
			ChangeEntrancePasswd();
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

void ObjectIn() {
	char c = 0;
	while (c != 'a' && c != 'b') {
		system("cls");
		printf("\t\t---Way to Enter---\n");
		printf("\ta. Account\n");
		printf("\tb. Guest\n");
		printf("Please Choose: ");
		setbuf(stdin, NULL);
		scanf("%c", &c);
		switch (c) {
		case 'a':
			AccountIn();
			return;
			break;
		case 'b':
			GuestIn();
			return;
			break;
		default:
			printf("\nError!");
			system("pause");
			break;
		}
	}
}

void AccountIn() {
	string acc;
	int flag = -1;
	while (flag == -1) {
		system("cls");
		setbuf(stdin, NULL);
		printf("Please Enter Your Account Name:");
		cin >> acc;
		for (int i = 0; i < custnum; i++) {
			if (acc == CUST[i].name) {
				flag = i;
				break;
			}
		}
		if (flag == -1) {
			setbuf(stdin, NULL);
			printf("Account Not Found, Please reEnter");
			system("pause");
		}
	}
	if (CUST[flag].tool.kind == 'c') {
		CUST[flag].tool.place[0] = 1;
		ParkIn(CUST[flag].tool, CS1, CS1LENGTH, CS1WIDTH);
		printf("Parkin Success!");
	}
	if (CUST[flag].tool.kind == 'e') {
		char c;
		while (c != '2' && c != '3') {
			system("cls");
			setbuf(stdin, NULL);
			printf("Please Choose Which Parking Space(2 for CS2, 3 for CS3):");
			scanf("%c", &c);
			switch (c) {
			case '2':
				CUST[flag].tool.place[0] = 2;
				ParkIn(CUST[flag].tool, CS2, CS2LENGTH, CS2WIDTH);
				break;
			case '3':
				CUST[flag].tool.place[0] = 3;
				ParkIn(CUST[flag].tool, CS3, CS3LENGTH, CS3WIDTH);
				break;
			default:
				printf("\nError!");
				system("pause");
				break;
			}
		}
	}
	setbuf(stdin, NULL);
	cout << CUST[flag].tool.place[1] << " " << CUST[flag].tool.place[2] << endl;
	printf("Parking Success!");
	system("pause");
}

void GuestIn() {
	bool flag = 1;
	char c;
	string lic;
	Object temp;
	while (flag) {
		system("cls");
		setbuf(stdin, NULL);
		printf("Please Enter the Vehicle type(c for Car, e for eBike):");
		scanf("%c", &c);
		switch (c) {
		case 'c':
			temp.kind = c;
			flag = 0;
			break;
		case 'e':
			temp.kind = c;
			flag = 0;
			break;
		default:
			printf("\nError!");
			system("pause");
			break;
		}
	}
	system("cls");
	setbuf(stdin, NULL);
	printf("Please Enter The Licence: ");
	cin >> lic;
	temp.license = lic;
	temp.cust = NULL;
	if (temp.kind == 'c') {
		temp.place[0] = 1;
		ParkIn(temp, CS1, CS1LENGTH, CS1WIDTH);
	} else {
		char c;
		while (c != '2' && c != '3') {
			system("cls");
			setbuf(stdin, NULL);
			printf("Please Choose Which Parking Space(2 for CS2, 3 for CS3):");
			scanf("%c", &c);
			switch (c) {
			case '2':
				temp.place[0] = 2;
				ParkIn(temp, CS2, CS2LENGTH, CS2WIDTH);
				break;
			case '3':
				temp.place[0] = 3;
				ParkIn(temp, CS3, CS3LENGTH, CS3WIDTH);
				break;
			default:
				printf("\nError!");
				system("pause");
				break;
			}
		}
	}
	printf("Parking Success!");
	system("pause");
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

/*
 * Enterance Desk Mod End
 */

/*
 * Exit Desk Mod Start
 */

void ExitLogin() {
	string temp;
	for (int i = 0; i < 3; i++) {
		system("cls");
		printf("Please Input Exit Desk Password: ");
		cin >> temp;
		if (temp == EXITPASSWD) {
			Exit();
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

void Exit() {
	char c;
	while (1) {
		system("cls");
		printf("\t\t----Parking System(Exit Desk)---\n");
		printf("\t1. Vehicle Out\n");
		printf("\tp. Change Password\n");
		printf("\tq. Exit Desk Exit\n");
		printf("\tPlease Choose: ");
		setbuf(stdin, NULL);
		scanf("%c", &c);
		switch (c) {
		case '1':
			LetObjectOut();
			break;
		case 'p':
			ChangeExitPasswd();
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

void ChangeExitPasswd() {
	string temp1, temp2;
	system("cls");
	printf("Please Input the New Password: \n");
	cin >> temp1;
	printf("Please Input Again: \n");
	cin >> temp2;
	if (temp1 == temp2)
		EXITPASSWD = temp2;
	else {
		system("cls");
		printf("Not Matched! \n");
	}
	return;
}

void LetObjectOut() {
	char c = 0;
	while (c != 'a' && c != 'b') {
		system("cls");
		setbuf(stdin, NULL);
		printf("\t\t---You have account or Guest---\n");
		printf("\ta. Account\n");
		printf("\tb. Guest\n");
		printf("Please Choose: ");
		scanf("%c", &c);
		switch (c) {
		case 'a':
			AccountOut();
			return;
			break;
		case 'b':
			GuestOut();
			return;
			break;
		default:
			printf("\nError!");
			system("pause");
			break;
		}
	}
}

void AccountOut() {
	string acc;
	double paypal;
	int flag = -1;
	while (flag == -1) {
		system("cls");
		setbuf(stdin, NULL);
		printf("Please Enter Your Account Name:");
		cin >> acc;
		for (int i = 0; i < custnum; i++) {
			if (acc == CUST[i].name) {
				for (int j = 0; i < carnum; j++) {
					if (CUST[i].tool.license == cars[j].license) {
						flag = i;
						break;
					}
				}
				break;
			}
		}
		if (flag == -1) {
			printf("Car Not Found, Please reEnter");
			system("pause");
			return;
		}
	}
	if (CUST[flag].tool.kind == 'c') {
		GoOut(CS1, CS1WIDTH, CS1LENGTH, CUST[flag].tool.place[1],
				CUST[flag].tool.place[2]);
	}
	if (CUST[flag].tool.kind == 'e') {
		switch (CUST[flag].tool.place[0]) {
		case 2:
			GoOut(CS2, CS2WIDTH, CS2LENGTH, CUST[flag].tool.place[1],
					CUST[flag].tool.place[2]);
			break;
		case 3:
			GoOut(CS3, CS3WIDTH, CS3LENGTH, CUST[flag].tool.place[1],
					CUST[flag].tool.place[2]);
			break;
		default:
			break;
		}
	}
	switch (CUST[flag].level) {
	case 't':
		paypal = CHARGETABLE[CUST[flag].tool.place[0] - 1] * TEACHERDISCOUNT;
		break;
	case 's':
		paypal = CHARGETABLE[CUST[flag].tool.place[0] - 1] * STUDENTDISCOUNT;
		break;
	case 'v':
		paypal = CHARGETABLE[CUST[flag].tool.place[0] - 1];
		break;
	}
	cout << "The Charge is $" << paypal << "!" << endl;
	system("pause");
}

void GuestOut() {
	string lic;
	char c;
	int flag = -1;
	printf(
			"Please Choose Your Parking Slot(1 for cs1, 2 for cs2, 3 for cs3): ");
	setbuf(stdin, NULL);
	scanf("%c", &c);
	printf("Please Input Your Vehicle's License:");
	setbuf(stdin, NULL);
	cin >> lic;
	for (int i = 0; i < carnum; i++) {
		if (cars[i].license == lic) {
			flag = i;
			break;
		}
	}
	if (flag != -1) {
		if (c == '1') {
			GoOut(CS1, CS1WIDTH, CS1LENGTH, cars[flag].place[1],
					cars[flag].place[2]);
		} else if (c == '2') {
			GoOut(CS2, CS2WIDTH, CS2LENGTH, cars[flag].place[1],
					cars[flag].place[2]);
		} else if (c == '3') {
			GoOut(CS3, CS3WIDTH, CS3LENGTH, cars[flag].place[1],
					cars[flag].place[2]);
		}
		printf("The Charge is $%.0lf!\n", CHARGETABLE[cars[flag].place[0] - 1]);
		printf("Thank U for Your Visiting!");
		system("pause");
	} else {
		printf("Input Error!");
		system("pause");
		return;
	}
}

/*
 * Exit Desk Mod End
 */

int main() {
	Welcome();
	system("pause");
}
