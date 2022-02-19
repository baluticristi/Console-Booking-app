#include "Admin.h"
#include <fstream>

string Admin::addUnit() {
	string aux, name;
	ofstream file;
	ofstream config;
	config.open("Units/config.txt", std::ios_base::app);
	bool hotel;
	cout << "What is the name of the unit?" << endl;
	getline(std::cin, aux);
	getline(std::cin, aux);
	name = aux;
	for (int i = 0; i < name.size(); i++) {
		if (name[i] == ' ')name[i] = '_';
	}
	name += ".txt";
	string adder=name;
	config << endl;
	config << name;
	config.close();
	name = "Units/" + name;
	file.open(name);
	file << aux << endl;
	bool ok = false;
	while (ok == false) {
		cout << "What is the type of unit you want to add? (Hotel/Pensiune)" << endl;
		cin >> aux;
		if (aux == "Hotel"||aux=="Pensiune") ok = true;
	}
	file << aux << endl;
	if (aux == "Hotel") hotel = true;
	else hotel = false;
	
	cout << "Where is it located?" << endl;
	cin >> aux;
	file << aux << endl;

	ok = false;
	while (ok == false) {
		if (hotel) cout << "Cate stele are hotelul?" << endl;
		else cout << "Cate margarete are pensiunea?" << endl;
		cin >> aux;
		if (isdigit(aux[0]) != 0) ok = true;
	}
	file << aux[0] << endl;
	ok = false;
	while (ok == false) {

		cout << "How many rooms are there?" << endl;
		cin >> aux;
		if (isdigit(aux[0]) != 0) ok = true;
	}
	file << aux << endl;

	int nr = stoi(aux);
	for (int i = 0; i < nr; i++) {
		ok = false;
		while (ok == false) {
			cout << "Cate persoane pot fi acomodate in camera cu numarul " << i + 1 << "?" << endl;
			cin >> aux;
			if (isdigit(aux[0]) != 0) ok = true;
		}
		file << aux;
		if (i != nr - 1)file << " ";
		else file << endl;
	}
	for (int i = 0; i < nr; i++) {
		ok = false;
		while (ok == false) {
			cout << "Care este pretul camerei cu numarul " << i + 1 << "?" << endl;
			cin >> aux;
			if (isdigit(aux[0]) != 0) ok = true;
		}
		file << aux;
		if (i != nr - 1)file << " ";
		else file << endl;
	}
	float priceB=0, priceL=0, priceD=0;
	cout << "Does the unit offer Breakfast?(yes/no)" << endl;
	cin >> aux;
	if (aux == "yes" || aux == "Yes" || aux == "YES" || aux == "y") {
		ok = false;
		while (ok == false) {
			cout << "What is the price for it?" << endl;
			cin >> aux;
			if (isdigit(aux[0]) != 0) ok = true;
		}
		priceB = stoi(aux);
		file << "Breakfast";
	}
	cout << "Does the unit offer Lunch?(yes/no)" << endl;
	cin >> aux;
	if (aux == "yes" || aux == "Yes" || aux == "YES" || aux == "y") {
		ok = false;
		while (ok == false) {
		cout << "What is the price for it?" << endl;
		cin >> aux;
		if (isdigit(aux[0]) != 0) ok = true;
		}

		priceL = stoi(aux);
		if (priceB != 0 && priceL != 0 ) file << " ";
		file << "Lunch";
	}

	cout << "Does the unit offer Dinner?(yes/no)" << endl;
	cin >> aux;
	if (aux == "yes" || aux == "Yes" || aux == "YES"||aux=="y") {
		ok = false;
		while (ok == false) {
			cout << "What is the price for it?" << endl;
			cin >> aux;
			if (isdigit(aux[0]) != 0) ok = true;

		}

		priceD = stoi(aux);
		if (priceL != 0 && priceD != 0 || priceB != 0 && priceD != 0) file << " ";
		file << "Dinner";
	}

	file << endl;
	if (priceB != 0) file << priceB;
	if (priceB != 0&&priceL!=0||priceB!=0&&priceD!=0) file << " ";
	if (priceL != 0) file << priceL;
	if (priceL != 0&&priceD!=0) file << " ";
	if (priceD != 0) file << priceD;
	file.close();
	return adder;
}