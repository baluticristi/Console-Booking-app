#pragma once
#include <iostream>
#include <string>

using namespace std;
class Account
{
private:
	string username;
	string password;
public:
	int NrReservations;
	Account() {};
	Account(string u, string p) { username = u; password = p; NrReservations = 0; };
	void Create(string u, string p) { username = u; password = p; NrReservations = 0;};
	bool CheckUser(string u);
	bool CheckPass(string p);
	string getName() { return username; };

};

