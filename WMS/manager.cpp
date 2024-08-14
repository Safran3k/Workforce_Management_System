#include "manager.hpp"
#include <sstream>

Manager::Manager(const std::string& name, const std::string& birthDay,
               double monthlyFixedSalary, double companyResult)
    : Worker(name, birthDay), monthlyFixedSalary(monthlyFixedSalary), companyResult(companyResult) {}

double Manager::calcSalary() const {
    double bonusOrDeduction = companyResult * 0.1;
    double finalSalary = monthlyFixedSalary + bonusOrDeduction;
    return finalSalary > 0 ? finalSalary : 0;
}

double Manager::costOfEmployment() const {
    double baseSalary = calcSalary();
    return baseSalary + baseSalary * 1.0;
}

std::string Manager::toString() const {
    std::ostringstream oss;
    oss << "Name: " << name
    << ", Birthday: " << birthDay
    << ", Monthly fixed salary: " << monthlyFixedSalary
    << ", Company result: " << companyResult
    << ", Calculated salary: " << calcSalary()
    << ", Cost of employment: " << costOfEmployment();
    return oss.str();
}


