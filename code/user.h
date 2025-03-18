#ifndef USER_H
#define USER_H

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
    double calculateBill(int dataUsage, string discountCode = "") override;
    string getUserType() override;
};

class PremiumUser : public User {
public:
    double calculateBill(int dataUsage, string discountCode = "") override;
    string getUserType() override;
};

#endif