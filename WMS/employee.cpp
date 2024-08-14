#include "employee.hpp"
#include <sstream>

Employee::Employee(const std::string& name, const std::string& birthDay,
                         double monthlySalary, int totalWorkDaysInMonth, int numOfIllnessDays)
    : Worker(name, birthDay),
      monthlySalary(monthlySalary),
      totalWorkDaysInMonth(totalWorkDaysInMonth),
      numOfIllnessDays(numOfIllnessDays) {}

double Employee::calcSalary() const {
    double baseSalaryPerDay = monthlySalary / (totalWorkDaysInMonth + numOfIllnessDays);
    double salaryForHealthyDays = baseSalaryPerDay * totalWorkDaysInMonth;
    double salaryForSickDays = baseSalaryPerDay * numOfIllnessDays * 0.6;

    return salaryForHealthyDays + salaryForSickDays;
}

double Employee::costOfEmployment() const {
    double baseSalary = calcSalary();
    return baseSalary + baseSalary * 1.0;
}

std::string Employee::toString() const {
    std::ostringstream oss;
    oss << "Name: " << name
    << ", Birthday: " << birthDay
    << ", Monthly salary: " << monthlySalary
    << ", Total work days in month: " << totalWorkDaysInMonth
    << ", Number of illness days: " << numOfIllnessDays
    << ", Calculated salary: " << calcSalary()
    << ", Cost of employment: " << costOfEmployment();
    return oss.str();
}

