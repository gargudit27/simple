 #include <iostream>
#include <string>
#include <limits>
using namespace std;

class User {
protected:
    int dataUsage;
    string discountCode;

public:
    virtual void input() = 0;
    virtual double calculateBill() = 0;
    virtual void display() = 0;
    virtual ~User() {}
};

class BasicUser : public User {
public:
    void input() override {
        while (true) {
            cout << "Enter data usage in GB: ";
            cin >> dataUsage;
            if (cin.fail() || dataUsage <= 0) {
                cout << "Data usage must be a positive number. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
    }

    double calculateBill() override {
        double baseCharge = 500;
        double extraCharge = (dataUsage > 50) ? (dataUsage - 50) * 5 : 0;
        return baseCharge + extraCharge;
    }

    void display() override {
        double extraCharge = (dataUsage > 50) ? (dataUsage - 50) * 5 : 0;
        double totalBill = calculateBill();
        cout << "User type = Basic. Extra data charge = Rs " << extraCharge
             << ". Total bill = Rs " << totalBill << endl;
    }
};

class PremiumUser : public User {
public:
    void input() override {
        while (true) {
            cout << "Enter data usage in GB: ";
            cin >> dataUsage;
            if (cin.fail() || dataUsage <= 0) {
                cout << "Data usage must be a positive number. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
        cout << "Enter discount code if available (or press Enter to skip): ";
        cin.ignore();
        getline(cin, discountCode);
    }

    double calculateBill() override {
        double baseCharge = 1000;
        double extraCharge = (dataUsage > 100) ? (dataUsage - 100) * 5 : 0;
        double total = baseCharge + extraCharge;
        if (discountCode == "NET50") {
            total -= 50;
        }
        return total;
    }

    void display() override {
        double extraCharge = (dataUsage > 100) ? (dataUsage - 100) * 5 : 0;
        double totalBill = calculateBill();
        cout << "User type = Premium. Extra data charge = Rs " << extraCharge
             << ". Total bill after discount = Rs " << totalBill << endl;
    }
};

int main() {
    string userType;
    User* user = nullptr;

    while (true) {
        cout << "Enter Type of User (B for Basic, P for Premium): ";
        cin >> userType;
        if (userType == "B" || userType == "P") break;
        cout << "Invalid user type. Please try again." << endl;
    }

    if (userType == "B") {
        user = new BasicUser();
    } else if (userType == "P") {
        user = new PremiumUser();
    }

    user->input();
    user->display();

    delete user;
    return 0;
}
