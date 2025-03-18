#include <iostream>
#include <string>
#include "User.h"
using namespace std;

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