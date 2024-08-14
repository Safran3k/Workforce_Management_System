#pragma once

#include <string>

class Worker {
protected:
    std::string name;
    std::string birthDay;

public:
    Worker(const std::string& name, const std::string& birthDay);
    virtual ~Worker() = default;
    virtual std::string toString() const = 0;
    virtual double calcSalary() const = 0;
    virtual double costOfEmployment() const = 0;
    std::string getName() const { return name; }
    std::string getBirthDay() const { return birthDay; }
    void setName(const std::string& newName) { name = newName; }
    void setBirthDay(const std::string& newBirthDay) { birthDay = newBirthDay; }
};

