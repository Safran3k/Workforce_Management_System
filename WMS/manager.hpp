#pragma once

#include "worker.hpp"

class Manager : public Worker {
    double monthlyFixedSalary;
    double companyResult;

public:
    Manager(const std::string& name, const std::string& birthDay,
           double monthlyFixedSalary, double companyResult);
    std::string toString() const override;
    double calcSalary() const override;
    double costOfEmployment() const override;
};
