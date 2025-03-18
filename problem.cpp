#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

// Get the current year
int getCurrentYear() {
	time_t t = time(nullptr);
	tm* now = localtime(&t);
	return now->tm_year + 1900;
}

class Vehicle {
public:
	string registrationNumber;
	string ownerName;
	int modelYear;

	Vehicle() {}
	Vehicle(string regNum, string owner, int year) {
		if (year < 1990 || year > getCurrentYear()) {
			throw invalid_argument("Model Year must be between 1990 and the current year.");
		}
		registrationNumber = regNum;
		ownerName = owner;
		modelYear = year;
	}

	void input() {
		cout << "Enter Registration Number: ";
		cin >> registrationNumber;
		cout << "Enter Owner Name: ";
		cin.ignore(); // Clear input buffer
		getline(cin, ownerName);

		while (true) {
			cout << "Enter Model Year: ";
			cin >> modelYear;
			if (cin.fail() || modelYear < 1990 || modelYear > getCurrentYear()) {
				cin.clear();
				cin.ignore();
				cerr << "Invalid model year! Must be between 1990 and the current year. Try again.\n";
			} else {
				break;
			}
		}
	}

	void display() const {
		cout << "Registration Number: " << registrationNumber << endl;
		cout << "Owner Name: " << ownerName << endl;
		cout << "Model Year: " << modelYear << endl;
	}
};

void saveToFile(const vector<Vehicle>& vehicles, const string& filename) {
	ofstream outFile(filename, ios::binary);
	if (!outFile) {
		cerr << "Error opening file for writing!" << endl;
		return;
	}
	for (const auto& vehicle : vehicles) {
		outFile.write(reinterpret_cast<const char*>(&vehicle), sizeof(Vehicle));
	}
	outFile.close();
}

void readFromFile(const string& filename) {
	ifstream inFile(filename, ios::binary);
	if (!inFile) {
		cerr << "Error opening file for reading!" << endl;
		return;
	}
	Vehicle vehicle;
	while (inFile.read(reinterpret_cast<char*>(&vehicle), sizeof(Vehicle))) {
		vehicle.display();
		cout << "-------------------------" << endl;
	}
	inFile.close();
}

int main() {
	vector<Vehicle> vehicles;
	char choice;

	do {
		try {
			Vehicle v;
			v.input();
			vehicles.push_back(v);
		} catch (const invalid_argument& e) {
			cerr << "Error: " << e.what() << endl;
		}

		cout << "Do you want to add another vehicle? (y/n): ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');

	string filename = "vehicles.dat";
	saveToFile(vehicles, filename);

	cout << "\nStored Vehicles:\n";
	readFromFile(filename);

	return 0;
}
