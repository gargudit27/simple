#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <ctime>

using namespace std;

// Get the current year
int getCurrentYear() {
    time_t t = time(nullptr);
    tm now;
    localtime_r(&t, &now);  // Use thread-safe localtime_r instead of localtime
    return now.tm_year + 1900;
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        cout << "Enter Owner Name: ";
        getline(cin, ownerName);
        
        while (true) {
            cout << "Enter Model Year: ";
            cin >> modelYear;
            if (cin.fail() || modelYear < 1990 || modelYear > getCurrentYear()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    // Save vehicle to file
    void saveToFile(ofstream &outFile) const {
        size_t regLen = registrationNumber.size();
        size_t ownerLen = ownerName.size();
        
        outFile.write(reinterpret_cast<const char*>(&regLen), sizeof(regLen));
        outFile.write(registrationNumber.c_str(), regLen);
        outFile.write(reinterpret_cast<const char*>(&ownerLen), sizeof(ownerLen));
        outFile.write(ownerName.c_str(), ownerLen);
        outFile.write(reinterpret_cast<const char*>(&modelYear), sizeof(modelYear));
    }

    // Load vehicle from file
    void loadFromFile(ifstream &inFile) {
        size_t regLen, ownerLen;
        inFile.read(reinterpret_cast<char*>(&regLen), sizeof(regLen));

        registrationNumber.resize(regLen);
        inFile.read(&registrationNumber[0], regLen);

        inFile.read(reinterpret_cast<char*>(&ownerLen), sizeof(ownerLen));
        ownerName.resize(ownerLen);
        inFile.read(&ownerName[0], ownerLen);

        inFile.read(reinterpret_cast<char*>(&modelYear), sizeof(modelYear));
    }
};

void saveVehiclesToFile(const vector<Vehicle>& vehicles, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    size_t vehicleCount = vehicles.size();
    outFile.write(reinterpret_cast<const char*>(&vehicleCount), sizeof(vehicleCount));

    for (const auto& vehicle : vehicles) {
        vehicle.saveToFile(outFile);
    }

    outFile.close();
}

void readVehiclesFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    size_t vehicleCount;
    inFile.read(reinterpret_cast<char*>(&vehicleCount), sizeof(vehicleCount));

    for (size_t i = 0; i < vehicleCount; ++i) {
        Vehicle vehicle;
        vehicle.loadFromFile(inFile);
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
    saveVehiclesToFile(vehicles, filename);
    
    cout << "\nStored Vehicles:\n";
    readVehiclesFromFile(filename);
    
    return 0;
}
