#include "Admin.h"
#include"Unit.h"
#include "Reservation.h"
#include <algorithm>
#include"Logs.h"
vector<Account> Accounts;
vector<Unit> Units;
vector<Reservation> Reservations;
Admin Owner = Owner.getInstance("123");
Logs logs;
//Admin Owner = Owner.getInstance("mybesttryatapassword");

bool logged = false;
string user, pass;
void setDefault();
bool checkCredentials(string user, string pass);
void LogScreen();
void MainMenu();
void ShowAllMenu();
void ShowCities();
void ShowAvailableMenu();
void ShowAvailableByCityMenu(string city);
void Reserve(int x);
void check(int count);
void checkByCity(string city);
void CheckReservations();
void CheckUnnaprovedReservations();
void CheckApprovedReservations();
void CheckAllReservations();
int getnumber();
void GenerateStatistics();
void ShowTop();
void GradOcupare(Unit x);
void AveragePrice();


int main() {
	try {
		setDefault();
		LogScreen();
		cin.ignore();
		MainMenu();
		throw 404;
	}
	catch (int x) { if (x == 404) logs.Eroare(); }
	return 0;
}

void setDefault() {
	//accounts
	Account Aux;
	Aux.Create("ana.maria", "strongpass");	Accounts.push_back(Aux);
	Aux.Create("marcel.ciolacu", "password");	Accounts.push_back(Aux);
	Aux.Create("someone", "123456");	Accounts.push_back(Aux);
	Aux.Create("cristianbaluti", "unbreakablepass");	Accounts.push_back(Aux);
	Aux.Create("test", "1");	Accounts.push_back(Aux);

	//units
	Unit helper;
	string help;
	ifstream file;
	file.open("Units/config.txt");
	while (!file.eof()) {
		getline(file, help);
		helper.setup(help);
		Units.push_back(helper);
	}
	file.close();

	Reservation aux;
	file.open("Reservations/config.txt");
	while (!file.eof()) {
		getline(file, help);
		aux.setup(help, Accounts,Units);
		Reservations.push_back(aux);
	}

}

bool checkCredentials(string user, string pass) {
	if (user != "Admin") {
		for (int i = 0; i < Accounts.size(); i++)
		{
			if (Accounts[i].CheckUser(user))
				if (Accounts[i].CheckPass(pass))
					return true;
		}
		logs.Alerta();
		return false;
	}
	else {
		if (Owner.CheckPass(pass)) return true;
		return false;
	}
}
void LogScreen() {

	while (!logged) {

		cout << "In order to use the app, you need to be logged in:" << endl;
		cout << "Username: ";
		cin >> user;
		cout << "Password: ";
		cin >> pass;
		if (checkCredentials(user, pass)) {
			cout << "Success!";
			logged = true;
			system("CLS");

		}
		else {
			system("CLS");
			cout << "Wrong username or password!" << endl << "Please try again" << endl;
		}
	}
}

void GenerateStatistics() {
	int choice = 0;
	system("CLS");
	cout << "Poti genera urmatoarele statistici: "<<endl;
	cout << "1. Topul unitatilor de cazare solicitate" << endl;
	cout << "2. Gradul de ocupare al unei unitati de cazare" << endl;
	cout << "3. Pretul mediu al cazarilor." << endl;
	cout << endl << "Alege una dintre optiuni sau 0 pentru Main Menu." << endl;
	choice = getnumber();
	int ch;
	if (choice >= 1 && choice <= 4) {
		switch (choice) {
		case 1:
			system("CLS");
			ShowTop();
			MainMenu();
			break;
		case 2:
			system("CLS");

			for (int i = 0; i < Units.size(); i++) {
				cout << i + 1 << ". ";
				Units[i].brief();
			}
			cout << "Whitch unit do you want to check?" << endl;
			ch = getnumber();
			if (ch <= Units.size())
				GradOcupare(Units[ch - 1]);
			MainMenu();
			break;
		case 3:
			system("CLS");
			AveragePrice();
			MainMenu();
			break;
		}
	}

	else MainMenu();

}

void ShowTop() {
	vector<Unit> top;
	vector<int>HowMany;
	int aux;
	for (int i = 0; i < Units.size(); i++) {
		aux = 0;
		for (int j = 0; j < Reservations.size(); j++) {
			if (Reservations[j].getUnit().getName() == Units[i].getName()) aux++;
		}
		HowMany.push_back(aux);
	}
	std::sort(HowMany.begin(), HowMany.end(), greater<int>());
	bool no = false;
	for (int j = 0; j < HowMany.size(); j++) {
		for (int i = 0; i < Units.size(); i++) {
			no = false;
			for (int k = 0; k < top.size(); k++) { if (Units[i].getName() == top[k].getName())no = true; }
			if (no==false) {
				aux = 0;
				aux = Units[i].getRooms() - Units[i].checkAvailable();
				if (aux == HowMany[j] && aux != 0) top.push_back(Units[i]);
			}
		}
	}
		for (int i = 0; i < Units.size(); i++) {
			aux = Units[i].getRooms() - Units[i].checkAvailable();
			if (aux == 0) { top.push_back(Units[i]);
			}

	}
	
	for (int j = 0; j < top.size(); j++) {
		cout << j + 1 << ". " << top[j].getType() << " " << top[j].getName()<<" cu "<<HowMany[j]<<" rezervari!"<<endl;
	}
	cout << "Press enter to return to the main menu" << endl;
	cin.ignore();
	getchar();
}
void GradOcupare(Unit x) {
	system("CLS");
	float percentage;
	percentage = 1-( static_cast<float>(x.checkAvailable())/ static_cast<float>(x.getRooms()));
	cout << "Gradul de ocupare al unitatii \"" << x.getType() << " " << x.getName() << "\" este: ";
	float whole = floor(percentage);
	float decimal = percentage - whole;
	cout <<decimal*100 << "%." << endl;
	cout << "Press enter to return to the main menu" << endl;
	cin.ignore();
	getchar();

}
void AveragePrice() {
	system("CLS");
	float medium=0;
	int divis=0;

	for (int i = 0; i < Reservations.size(); i++)
	{
		if (Reservations[i].getStatus() != "Denied") {
			medium += Reservations[i].getPrice();
			divis++;
		}
	}

	medium = medium / divis;
	cout << "The average price of a reservation is: " << medium << " lei/Reservation" << endl;
	cout << "Press enter to return to the main menu" << endl;
	cin.ignore();
	getchar();

}

void MainMenu() {
	int choice=0;
	system("CLS");
	cout << "You are connected into your account, " << user << "!" << endl;
	cout << "You can: " << endl;
	cout << "1. Show available units. " << endl;
	cout << "2. Show all units." << endl;
	cout << "3. Show cities where you can book." << endl;
	cout << "4. Check reservations. " << endl;
	cout << "5. Disconnect" << endl;
	if (user == "Admin") {
		cout << "6. Add a new Unit." << endl;
		cout << "7. Check for unapproved reservations." << endl;
		cout << "8. Check all reservations." << endl;
		cout << "9. Check approved reservations that have not been finished." << endl;
		cout << "10. Generate statistics." << endl;
	}
	choice = getnumber();
	if ((user=="Admin"&&choice >= 1 && choice <= 10)||(choice >= 1 && choice <= 5)) {
		switch (choice) {
		case 1:
			system("CLS");
			ShowAvailableMenu();
			MainMenu();
			break;
		case 2:
			system("CLS");
			ShowAllMenu();
			MainMenu();
			break;
		case 3:
			system("CLS");
			ShowCities();
			MainMenu();
			break;
		case 4:
			system("CLS");
			CheckReservations();
			MainMenu();
			break;
		case 5:
			system("CLS");
			logged = false;
			LogScreen();
			MainMenu();
			break;
		case 6:
			if (user == "Admin") {
				string name = Owner.addUnit();
				Unit nice;
				nice.setup(name);
				Units.push_back(nice);
				cout << "NEW UNIT ADDED SUCESSFULLY!";
				getchar();
				getchar();
				MainMenu();
			}
			break;
		case 7:
			if (user == "Admin") {
				CheckUnnaprovedReservations();
				MainMenu();
			}
			break;
		case 8:
			if (user == "Admin") {
				CheckAllReservations();
				MainMenu();
			}
			break;
		case 9:
			if (user == "Admin") {
				CheckApprovedReservations();
				MainMenu();
			}
			break;
		case 10:
			if (user == "Admin") {
				GenerateStatistics();
				MainMenu();
			}
			break;
		}

	}
	else MainMenu();
}

int getnumber() {
	int choice;
	string helping;
	cin >> helping;
	for (int i = 0; i < helping.size(); i++) {
		if (isdigit(helping[i]) == 0) {
			helping = "0";		
		}
	}
	choice = stoi(helping);
	return choice;
}

void ShowCities() {
	int count = 1;
	vector<string> Cities;
	Cities.push_back(Units[0].getCity());
	for (int i = 1; i < Units.size(); i++) {
		bool ok = true;
		for (int j = 0; j < Cities.size(); j++) {
			if (Cities[j] == Units[i].getCity()) ok = false;
		}
		if (ok==true) Cities.push_back(Units[i].getCity());

	}
	for (int i = 0; i < Cities.size(); i++) {
		cout << count << ". ";
		cout<< Cities[i]<<endl<<endl;
		count++;
	}

	int choice;
	cout << "What city do you want to book a stay in?" << endl;
	cout << "Or press '0' if you want to go back to the last menu." << endl;
	choice = getnumber();
	if (choice == 0) MainMenu();
	else if(choice<=Cities.size()) ShowAvailableByCityMenu(Cities[choice-1]);
}
void ShowAvailableByCityMenu(string city) {
	system("CLS");
	int count = 1;
	for (int i = 0; i < Units.size(); i++) {
		if (Units[i].getCity() == city) {
			if (Units[i].checkAvailable() > 0) {
				cout << count << ". ";
				count++;
			}
			Units[i].displayAvailable();
		}
	}
	checkByCity(city);
}

void ShowAvailableMenu() {
	int count = 1;
	for (int i = 0; i < Units.size(); i++) {
		if (Units[i].checkAvailable() > 0) {
			cout << count << ". ";
			Units[i].displayAvailable();
			count++;
		}
	}
	check(count);
}

void ShowAllMenu() {
	int count = 1;
	for (int i = 0; i < Units.size(); i++) {
		cout << count << ". ";
		Units[i].brief();
		count++;
	}
	check(count);
}

void check(int count) {
	int choice;
	cout << "What UNIT do you want to book a stay in?" << endl;
	cout << "Or press '0' if you want to go back to the last menu." << endl;
	choice = getnumber();
	int checker = 0;
	if (choice == 0) MainMenu();
	else if (choice <= count) {
		if (Units[choice - 1].checkAvailable() > 0) {
			Reserve(choice - 1);
		}
		else logs.Rezervare();
	}

}

void checkByCity(string city) {
	int choice;
	cout << "What UNIT do you want to book a stay in?" << endl;
	cout << "Or press '0' if you want to go back to the last menu." << endl;
	choice = getnumber();
	int checker = 0;
	if (choice == 0) MainMenu();
		for (int i = 0; i < Units.size(); i++) {
			if (Units[i].getCity() == city) {
				checker++;
				if (choice == checker) {
					Reserve(i);
					break;
				}
			}
		}
	}
void CheckReservations() {
	system("CLS");
	int count = 1;
	vector<int> checker;
	for (int i = 0; i < Reservations.size(); i++) {
		if (Reservations[i].getUser(user)) {
			if (Reservations[i].getStatus() == "Done")checker.push_back(i); 
			cout << count << ". ";
			count++;
			cout << "Reservation at " << Reservations[i].getname() << ", camera " << Reservations[i].getRoom();
			cout << endl << "\tStatus: " << Reservations[i].getStatus()<<".";
			cout << endl << "The total price is: " << Reservations[i].getPrice()<<" lei."<<endl<<endl;
		}
	}
	count = 1;
	if (checker.size() > 0) {
		cout <<endl<<endl<< "You can add an review for: " << endl;
		for (int i = 0; i < checker.size(); i++) {
			cout << count << ". ";
			count++;
			cout << "Reservation at " << Reservations[i].getname() << ", camera " << Reservations[i].getRoom();
			cout << endl << "With the total paid price: " << Reservations[i].getPrice() << " lei." << endl << endl;
		}
		cout << "Do you want to do so? (yes/no)" << endl;
		string ch;
		cin >> ch;
		if (ch == "yes" || ch == "Yes" || ch == "YES" || ch == "y") {
			cout << "To which one do you want to add the review?" << endl;
			int choice;
			choice = getnumber();
			for (int i = 0; i < checker.size(); i++) {
				if ((choice - 1) == checker[i]) {
					for (int k = 0; k < Units.size(); k++) {
						if(Reservations[checker[i]].getUnit().getName()==Units[k].getName())
							Units[k].addreview(user);
					}
				}
			}
		}
	}
	
	cout << "Press enter to return to the main menu" << endl;
	cin.ignore();
	getchar();
}
void CheckUnnaprovedReservations() {
	system("CLS");
	int count = 1;
	for (int i = 0; i < Reservations.size(); i++) {
		if (Reservations[i].getStatus()=="Pending") {
			cout << count << ". ";
			count++;
			cout << "The user: " << Reservations[i].getUsername() << " has a reservation:" << endl;
			cout << "\tReservation at " << Reservations[i].getname() << ", camera " << Reservations[i].getRoom();
			cout << endl << "\tStatus: " << Reservations[i].getStatus() << ".";
			cout << endl << "\tThe total price is: " << Reservations[i].getPrice() << " lei." << endl << endl;
		}
	}
	if (count > 1) {

		cout << "Do you want to answer the requests?(yes/no)" << endl;
		string ch;
		cin >> ch;
		if (ch == "yes" || ch == "Yes" || ch == "YES" || ch == "y") {
			cout << "Which one do you want to change?" << endl;
			int choice, check = 1;
			choice = getnumber();
			for (int i = 0; i < Reservations.size(); i++) {
				if (Reservations[i].getStatus() == "Pending") {
					if (choice == check) {
						cout << endl << "Do you want to: " << endl << "1. Approve" << endl << "2. Deny" << endl;
						choice = getnumber();
						if (choice == 1)Reservations[i].setStatus("Approved");
						else if (choice == 2) {
							Reservations[i].setStatus("Denied");
							for (int j = 0; j < Units.size(); j++) {
								if (Reservations[i].getUnit().getName() == Units[j].getName())
								{
									Units[j].ReverseLockInRoom(Reservations[i].getRoom());
								}
							}
						}
						else {
							cout << "Nu este o varianta!!";
							getchar();
						}
						break;
					}
					check++;

				}
			}
		}
	}
	
}
void CheckApprovedReservations() {
	system("CLS");
	int count = 1;
	for (int i = 0; i < Reservations.size(); i++) {
		if (Reservations[i].getStatus() == "Approved") {
			cout << count << ". ";
			count++;
			cout << "The user: " << Reservations[i].getUsername() << " has a reservation:" << endl;
			cout << "\tReservation at " << Reservations[i].getname() << ", camera " << Reservations[i].getRoom();
			cout << endl << "\tStatus: " << Reservations[i].getStatus() << ".";
			cout << endl << "\tThe total price is: " << Reservations[i].getPrice() << " lei." << endl << endl;

		}
	}
	if (count > 1) {
		cout << "Do you want to finish any reservation??(yes/no)" << endl;
		string ch;
		cin >> ch;
		if (ch == "yes" || ch == "Yes" || ch == "YES" || ch == "y") {
			cout << "Which one do you want to finish?" << endl;
			int choice, check = 1;
			choice = getnumber();
			for (int i = 0; i < Reservations.size(); i++) {
				if (Reservations[i].getStatus() == "Approved") {
					if (choice == check) {
						Reservations[i].setStatus("Done");
						for (int j = 0; j < Accounts.size(); j++) {
							if (Accounts[j].CheckUser(Reservations[i].getUsername()))Accounts[j].NrReservations += 1;
						}
						for (int j = 0; j < Units.size(); j++) {
							if (Reservations[i].getUnit().getName() == Units[j].getName())
							{
								Units[j].ReverseLockInRoom(Reservations[i].getRoom());
							}
						}
						break;
					}
					check++;

				}
			}
		}
	}
}
void CheckAllReservations() {
	system("CLS");
	int count = 1;
	for (int i = 0; i < Reservations.size(); i++) {
			cout << count << ". ";
			count++;
			cout << "The user: " << Reservations[i].getUsername() << " has a reservation:" << endl;
			cout << "\tReservation at " << Reservations[i].getname() << ", camera " << Reservations[i].getRoom();
			cout << endl << "\tStatus: " << Reservations[i].getStatus() << ".";
			cout << endl << "\tThe total price is: " << Reservations[i].getPrice() << " lei." << endl << endl;
	}
	cout << "Press enter to return to the main menu" << endl;
	cin.ignore();
	getchar();
}

void Reserve(int x) {
	system("CLS");
	Units[x].display();
	cout << endl << "What room do you want to reserve?" << endl;
	int choice;
	cout << "Or press '0' if you want to go back to the main menu." << endl;
	choice = getnumber();

	if (choice == 0) MainMenu();
	else if (choice <= Units[x].getRooms()) {
		Account aux;

		for (int i = 0; i < Accounts.size(); i++) {
			if (Accounts[i].CheckUser(user)) aux = Accounts[i];
		}
		Reservation NewRe(aux);
		if (NewRe.StartARe(Units[x], choice)) {
			cout << "Do you wish to porceed with your book?(yes/no)";
			string ch;
			cin >> ch;
			if (ch == "yes" || ch == "Yes" || ch == "YES" || ch == "y") {
				NewRe.setStatus("Pending");
				Units[x].lockInRoom(choice);
				NewRe.createFile();
				NewRe.addToConf();
				Reservations.push_back(NewRe);
				cout << "SUCCESS!!";
				cin >> ch;
			}
		}
		else {
			logs.Rezervare();
			Reserve(x);

		}
	}
}




