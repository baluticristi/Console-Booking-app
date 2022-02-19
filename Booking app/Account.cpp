#include "Account.h"

bool Account::CheckUser(string u) {
	if (username == u)return true;
	return false;
  }
bool Account::CheckPass(string p) {
	if (password == p)return true;
	return false;
}