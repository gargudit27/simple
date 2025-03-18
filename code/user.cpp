#include "User.h"

double BasicUser::calculateBill(int dataUsage, string discountCode) {
    double baseCharge = 500;
    double extraCharge = (dataUsage > 50) ? (dataUsage - 50) * 5 : 0;
    return baseCharge + extraCharge;
}

string BasicUser::getUserType() {
    return "Basic";
}

double PremiumUser::calculateBill(int dataUsage, string discountCode) {
    double baseCharge = 100;
    double extraCharge = (dataUsage > 100) ? (dataUsage - 100) * 5 : 0;
    double total = baseCharge + extraCharge;
    if (discountCode == "NET50") {
        total -= 50;
    }
    return total;
}

string PremiumUser::getUserType() {
    return "Premium";
}