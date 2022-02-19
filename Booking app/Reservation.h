#pragma once
#include <iostream>
#include "Unit.h"
#include "Account.h"

using namespace std;

class Reservation
{
private:
	Account user;
	string status;
	Unit U;
	int Room;
	float price;
public:
	Reservation(Account u) {
		user = u;
		price = 0;
	};
	Reservation() {
		price = 0;
	};
	bool StartARe(Unit x, int r);
	void setStatus(string x) { status = x; createFile(); };
	void addToConf();
	string getStatus() { return status; };
	string getUsername() { return user.getName(); };
	bool getUser(string usr) { return user.CheckUser(usr); };
	string getname() {
		string x = U.getType() + " " + U.getName();
		return x;
	};
	Unit getUnit() { return U; }
	int getRoom() { return Room; };
	float getPrice() { return price; };
	void setup(string filename, vector<Account>&users, vector<Unit>&units);
	void addDiscount();
	void createFile();
};
//Pending placed reservation that has not yet received approval
//Approved approved reservation
//Denied denied reservation
//Done finished reservation