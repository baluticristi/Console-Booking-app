#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Unit
{
private:
	string Name;
	string Type;
	string City;
	int rating;
	int NrOfRooms;
	vector<bool> available;
	vector<int> PersonsPerRoom;
	float priceB,priceL,priceD;
	vector<float> pricePerRoom;
	vector<string> Reviews;
	vector<string> ReviewWriter;
public:
	bool Breakfast;
	bool Lunch;
	bool Dinner;
	Unit() {};
	void setup(string filename);
	int checkAvailable();
	bool checkRoom(int i) {
		return available[i-1];
	};
	void displayAvailable();
	void display();
	void brief();
	string getName() { return Name; };
	string getType() { return Type; };
	string getCity() { return City; };
	int getRooms() { return NrOfRooms; };
	bool areThereMeals(){
		if (Breakfast == true || Lunch == true || Dinner == true) return true;
		return false;
	}
	float getPrice(int i) { return pricePerRoom[i]; }
	float getPriceB() { return priceB; }
	float getPriceL() { return priceL; }
	float getPriceD() { return priceD; }
	void lockInRoom(int i) { available[i-1] = false; }
	void ReverseLockInRoom(int i) { available[i-1] = true; }

	void addreview(string u);

};

