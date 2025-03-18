#include <iostream>
#include <string>
using namespace std;

class User {
public:
    virtual double calculateBill(int dataUsage, string discountCode = "") = 0;
    virtual string getUserType() = 0;
    virtual ~User() {}
};

class BasicUser : public User {
public:
    double calculateBill(int dataUsage, string discountCode = "") override {
        double baseCharge = 500;
        double extraCharge = (dataUsage > 50) ? (dataUsage - 50) * 5 : 0;
        return baseCharge + extraCharge;
    }
    string getUserType() override {
        return "Basic";
    }
};

class PremiumUser : public User {
public:
    double calculateBill(int dataUsage, string discountCode = "") override {
        double baseCharge = 100;
        double extraCharge = (dataUsage > 100) ? (dataUsage - 100) * 5 : 0;
        double total = baseCharge + extraCharge;
        if (discountCode == "NET50") {
            total -= 50;
        }
        return total;
    }
    string getUserType() override {
        return "Premium";
    }
};

int main() {
    string userType;
    int dataUsage;
    string discountCode;

    while (true) {
        cout << "Enter Type of User (B for Basic, P for Premium): ";
        cin >> userType;
        if (userType == "B" || userType == "P") break;
        cout << "Invalid user type. Please try again." << endl;
    }

    while (true) {
        cout << "Enter data usage in GB: ";
        cin >> dataUsage;
        if (dataUsage > 0) break;
        cout << "Data usage must be a positive number. Please try again." << endl;
    }

    User* user;
    if (userType == "B") {
        user = new BasicUser();
    } else {
        user = new PremiumUser();
        cout << "Enter discount code if available (or press Enter to skip): ";
        cin.ignore();
        getline(cin, discountCode);
    }

    double totalBill = user->calculateBill(dataUsage, discountCode);
    cout << "User type = " << user->getUserType() << ". ";
    if (userType == "B") {
        double extraCharge = (dataUsage > 50) ? (dataUsage - 50) * 5 : 0;
        cout << "Extra data charge = Rs " << extraCharge << ". ";
    } else {
        double extraCharge = (dataUsage > 100) ? (dataUsage - 100) * 5 : 0;
        cout << "Extra data charge = Rs " << extraCharge << ". ";
    }
    cout << "Total bill = Rs " << totalBill << endl;

    delete user;
    return 0;
}
