#pragma once

#include "worker.hpp"

class Employee : public Worker {
    double monthlySalary;
    int totalWorkDaysInMonth;
    int numOfIllnessDays;

public:
    Employee(const std::string& name, const std::string& birthDay,
                double monthlySalary, int totalWorkDaysInMonth, int numOfIllnessDays);
    std::string toString() const override;
    double calcSalary() const override;
    double costOfEmployment() const override;
    int getNumOfIllnessDays() const { return numOfIllnessDays; }
};
