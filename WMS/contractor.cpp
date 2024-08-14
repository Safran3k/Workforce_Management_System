#include "contractor.hpp"
#include <sstream>

Contractor::Contractor(const std::string& name, const std::string& birthDay,
                         double hourlyRate, int workingHours)
    : Worker(name, birthDay), hourlyRate(hourlyRate), workingHours(workingHours) {}

double Contractor::calcSalary() const {
    return hourlyRate * workingHours;
}

double Contractor::costOfEmployment() const {
    double baseSalary = calcSalary();
    return baseSalary + baseSalary * 0.3;
}

std::string Contractor::toString() const {
    std::ostringstream oss;
    oss << "Name: " << name
    << ", Birthday: " << birthDay
    << ", Hourly rate: " << hourlyRate
    << ", Working hours: " << workingHours
    << ", Calculated salary: " << calcSalary()
    << ", Cost of employment: " << costOfEmployment();
    return oss.str();
}


