#pragma once
#include "Account.h"
class Admin:public Account
{
private:
	Admin(string pass) :Account("Admin", pass) {};
public:
	static Admin& getInstance(string pass) {
		static Admin instance(pass);
		return instance;
	};
	string addUnit();
};

