#pragma once

#include "Worker.hpp"

class Contractor : public Worker {
    double hourlyRate;
    int workingHours;

public:
    Contractor(const std::string& name, const std::string& birthDay,
                double hourlyRate, int workingHours);
    std::string toString() const override;
    double calcSalary() const override;
    double costOfEmployment() const override;
};
