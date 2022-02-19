#include "Reservation.h"
#include "Unit.h"
#include <cmath>


void Reservation::addToConf() {
	ofstream fout;
	string filename;
	filename = U.getName() + "_" + user.getName() + "_" + to_string(Room);
	filename = filename + ".txt";

	fout.open("Reservations/config.txt", std::ios_base::app);
	fout << endl << filename;
	fout.close();
}
void Reservation::createFile() {
	ofstream file, fout;
	string filename;
	filename = U.getName() + "_" + user.getName() + "_" + to_string(Room);
	filename = filename + ".txt";
	filename = "Reservations/" + filename;

	file.open(filename);
	file << user.getName()<<endl;
	file << status << endl;
	file << U.getName() << endl;
	file << Room << endl;
	file << price;

	file.close();

}
void Reservation::setup(string filename, vector<Account>&users, vector<Unit>&units) {
	filename = "Reservations/" + filename;
	//(Nume unit)_(nume user)_camera.txt
	ifstream file;
	file.open(filename);
	string line;
	getline(file, line);
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getName() == line) {
			user = users[i];
			getline(file, line);
			status = line;
			if (status != "Denied") users[i].NrReservations++;
			break;
		}
	}
	getline(file, line);
	for (int i = 0; i < units.size(); i++) {
		if (units[i].getName() == line) {
			U = units[i];
			getline(file, line);
			Room = stoi(line);
			if (status != "Done" && status != "Denied")
				units[i].lockInRoom(Room);
			break;
		}
	}
	getline(file, line);
	price = stof(line);
}
void Reservation::addDiscount() {
	if (user.NrReservations > 1 && user.NrReservations < 6) {
		cout << "You have " << 2 + (4 * (user.NrReservations-1)) << "% discount for being a loyal customer!"<<endl;
		price = price - (price * (0.02 + (0.04 * (user.NrReservations - 1))));
	}
	else if (user.NrReservations == 1) {
		price = price - (price * 0.02);
		cout << "You have 2% discount for being a loyal customer!"<<endl;
	}
	else if (user.NrReservations > 5) {
		price = price - (price * 0.18);
		cout << "You have a 18% discount for being a loyal customer!"<<endl;
	}
}

bool Reservation::StartARe(Unit x, int r) {
	U = x;
	Room = r;
	system("CLS");
	float time, wknd;
	if (x.checkRoom(r) == false) {
		return false;
	}
	else {
		cout << "The room you have chosen is still available!" << endl;
		cout << "For how long do you wish to stay ?" << endl;
		cin >> time;
		cout << "Out of these days, how many are weekends?" << endl;
		cin >> wknd;
		float check;
		if (time > 7)check = time / 7;
		while (time > 7 && wknd < (2 * floor(check)) || time == 7 && wknd != 2||time==6&&wknd<1||time<6&&wknd>2||wknd>time||time>7&&wknd>((2*floor(check))+2)) {
			cout << "It looks like your input is invalid... You should have more weekends there!" << endl;
			cin >> wknd;
		}
		//calcul pret

		price = (x.getPrice(r - 1) * (time - wknd)) + (x.getPrice(r - 1) * 1.25 * wknd);
		if (U.areThereMeals())
		{
			cout << "Do you want to add some extra services?(yes/no)" << endl;
			string choice;
			cin >> choice;
			if (choice == "yes" || choice == "Yes" || choice == "YES" || choice == "y") {
				cout << endl << "These are the available services: " << endl;
				if (U.Breakfast == true) {
					cout << "Would you like Breakfast at " << U.getPriceB() << " lei/day, or " << U.getPriceB() * 1.25 << " lei/day during the weekends?(yes/no)" << endl;
					cin >> choice;
					if (choice == "yes" || choice == "Yes" || choice == "YES" || choice == "y") {
						price = price + (U.getPriceB() * (time - wknd)) + (U.getPriceB() * 1.25 * wknd);
					}
				}
				if (U.Lunch == true) {
					cout << "Would you like Lunch at " << U.getPriceL() << " lei/day, or " << U.getPriceL() * 1.25 << " lei/day during the weekends?(yes/no)" << endl;
					cin >> choice;
					if (choice == "yes" || choice == "Yes" || choice == "YES" || choice == "y") {
						price = price + (U.getPriceL() * (time - wknd)) + (U.getPriceL() * 1.25 * wknd);
					}

				}
				if (U.Dinner == true) {
					cout << "Would you like Dinner at " << U.getPriceD() << " lei/day, or " << U.getPriceD() * 1.25 << " lei/day during the weekends?(yes/no)" << endl;
					cin >> choice;
					if (choice == "yes" || choice == "Yes" || choice == "YES" || choice == "y") {
						price = price + (U.getPriceD() * (time - wknd)) + (U.getPriceD() * 1.25 * wknd);
					}
				}
			}
		}
		addDiscount();
		cout << "Great! Your price for the stay is gonna be: " << price << " lei. " << endl;

	}
	return true;
}
