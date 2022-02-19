#pragma once
#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class Logs

{
private:
	string msg;
public:
	Logs() {};
	void Eroare() {
		msg = "EROARE: Error during the execution of the program";
		print();
	};
	void Alerta() {
		msg = "ALERTA: A user had a problem while authenticating";
		print();
	};
	void Rezervare() {
		msg = "REZERVARE: One user is trying to book a already booked room";
		print();
	};
	void print() {
		ofstream file;
		file.open("Logs/MyExceptions.log", ios_base::app);
		file << msg<<endl;

	}
};
//Rezervare
//Alerta
//Eroare
