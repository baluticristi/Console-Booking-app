#include "Unit.h"
void Unit::setup(string filename) {
	available.clear();
	Reviews.clear();
	ReviewWriter.clear();
	PersonsPerRoom.clear();
	pricePerRoom.clear();

	filename = "Units/" + filename;
	ifstream file;
	file.open(filename);
	string line;
	getline(file, line);
	Name = line;
	getline(file, line);
	Type = line;
	getline(file, line);
	City = line;
	getline(file, line);
	rating = stoi(line);
	getline(file, line);
	NrOfRooms = stoi(line);
	for (int i = 0; i < NrOfRooms; i++) {
		file >> line;
		PersonsPerRoom.push_back(stoi(line));
	}
	for (int i = 0; i < NrOfRooms; i++) {
		file >> line;
		pricePerRoom.push_back(stoi(line));
	}
	for (int i = 0; i < NrOfRooms; i++) {
		available.push_back(true);
	}

		file >> line;
		if (line == "Breakfast") {
			Breakfast = true;
			file >> line;
		}
		else Breakfast = false;
		if (line == "Lunch") {
			Lunch = true;
			file >> line;
		}
		else Lunch = false;
		if (line == "Dinner") {
			Dinner = true;
			file >> line;
		}
		else Dinner = false;

		if (Breakfast) {
			priceB = stoi(line);
			file >> line;
		}
		if (Lunch) {
			priceL = stoi(line);
			file >> line;
		}
		if (Dinner) {
			priceD = stoi(line);
			file >> line;
		}

		while (!file.eof())
		{

			ReviewWriter.push_back(line);
			getline(file, line);
			if (line == "")getline(file, line);
			Reviews.push_back(line);
			if (!file.eof()) {
				getline(file, line);
				if (line == "")getline(file, line);
			}

		}

}

void Unit::displayAvailable()
{
	if (checkAvailable() > 0) {
		cout << Type << " " << Name << " - " << City << endl;
		if (Type == "Hotel")cout << "\t" << rating << " Stele!" << endl;
		else cout << "\t" << rating << " Margarete!" << endl;
		cout << "\t" << NrOfRooms << " rooms!";
		cout << " - " << "Out of which, " << checkAvailable() << " available!" << endl << endl;
	}
}
int Unit::checkAvailable() {
	int count = 0;
	for (int i = 0; i < available.size(); i++)
	{
		if (available[i] == true) count++;
	}
	return count;
}
void Unit::brief()
{
	cout << Type << " " << Name<<" - "<<City<<endl;
	if (Type == "Hotel")cout << "\t" << rating << " Stele!" << endl;
	else cout <<"\t"<< rating << " Margarete!" << endl;
	cout << "\t" << NrOfRooms << " rooms!";
	cout << " - " << "Out of which, " << checkAvailable() << " available!" << endl << endl;

}

void Unit::addreview(string u) {
	ReviewWriter.push_back(u);
	cout << "What do you wanna say about your stay? " << endl;
	string x, help;
	getline(std::cin, x);
	getline(std::cin, x);
	help = x;
	Reviews.push_back(x);
	x = Name;
	for (int i = 0; i < x.size(); i++) {
		if (x[i] == ' ')x[i] = '_';
	}

	x += ".txt";
	x = "Units/" + x;
	ofstream file;
	file.open(x, std::ios_base::app);
	file << endl<< u << endl;
	file << help;

	file.close();
	cout << "Success!";


}

void Unit::display()
{
	cout << Type << " " << Name << " - " << City << endl;
	if (Type == "Hotel")cout << "\t" << rating << " Stele!" << endl;
	else cout << "\t" << rating << " Margarete!" << endl;
	cout << "\t" << NrOfRooms << " rooms!";
	cout << " - " << "Out of which, " << checkAvailable() << " available!" << endl;
	cout << "The following rooms are available: " << endl;

	for (int i = 0; i < NrOfRooms; i++) {
		if (available[i] == true) {
			cout << "Room " << i + 1 << " that can accomodate " << PersonsPerRoom[i] << " persons." << endl;
			cout << "\tIt is priced at " << pricePerRoom[i] << " lei/night, or " << pricePerRoom[i] * 1.25 << " lei/night during the weekends." << endl;
		}
	}
	if (Breakfast == true || Lunch == true || Dinner == true) {
		cout <<endl<< "This unit does have these extra services: " << endl;
		if (Breakfast == true)cout << "Breakfast at " << priceB << " lei/day, or " << priceB * 1.25 << " lei/day during the weekends." << endl;
		if (Lunch == true)cout << "Lunch at " << priceL << " lei/day, or " << priceL * 1.25 << " lei/day during the weekends." << endl;
		if (Dinner == true)cout << "Dinner at " << priceD << " lei/day, or " << priceD * 1.25 << " lei/day during the weekends." << endl;
	}
	else cout <<endl<< "This unit does not offer meals or extra services!"<<endl;

	if (Reviews.size() > 0) {
		cout << endl << "This is what other people thought about the place: " << endl<<endl;
		for (int i = 0; i < Reviews.size(); i++) {
			cout << ReviewWriter[i] << " thought: " << endl;
			cout << Reviews[i] << endl<<endl;
		}
	}
}