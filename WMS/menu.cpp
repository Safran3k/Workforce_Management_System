#include "menu.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "worker.hpp"
#include "employee.hpp"
#include "contractor.hpp"
#include "manager.hpp"
#include "stoi.hpp"
#include "stodate.hpp"
#include "stod.hpp"

using namespace std;

template<typename T>
T readCheck()
{
    T retval;
    std::cin >> retval;
    return retval;
}

template<>
int readCheck()
{
    int retval;
    string inputBuffer;
    bool doReading = true;

    while(doReading)
    {
        cin >> inputBuffer;
        doReading = false;
        try
        {
            retval = inputCheck::stoi(inputBuffer);
        }
        catch(...)
        {
            cout << "Enter numeric value: ";
            doReading = true;
        }
    }
    return retval;
}

template<>
double readCheck() {
    double retval;
    string inputBuffer;
    bool doReading = true;

    while(doReading) {
        cin >> inputBuffer;
        doReading = false;
        try {
            retval = inputCheck::stod(inputBuffer);
        } catch(...) {
            cout << "Enter numeric value for double: ";
            doReading = true;
        }
    }
    return retval;
}

string readDate() {
    string retval;
    bool doReading = true;

    while (doReading) {
        cin >> retval;
        doReading = false;
        try {
            retval = dateCheck::stodate(retval);
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cout << "Birthday (YYYY-MM-DD): ";
            doReading = true;
        }
    }
    return retval;
}

Menu::Menu() {
    loadFromFile();
}

Menu::~Menu() {
    for (Worker* ptr : workers) {
        delete ptr;
    }
}

void Menu::execute() {
    int select;
    bool isRunning = true;

    while (isRunning) {
        cout << "-------------------------------------" <<endl;
        cout << "1. New Employee" << endl
        << "2. New Contract Employee" << endl
        << "3. New Manager" << endl
        << "4. List Employees" << endl
        << "5. Search Employee" << endl
        << "6. Get Total Wage Cost" << endl
        << "7. Modify Employee Data" << endl
        << "8. Save Employees Data to File" << endl
        << "9. Delete Employee Data" << endl
        << "10. Filter Employees by Type" << endl
        << "11. Filter Employees by Sick Days" << endl
        << "12. Filter Employees by Salary Range" << endl
        << "0. Exit" << endl;
        cout << "Choose from this menu options: ";
        select = readCheck<int>();
        cout << "-------------------------------------" <<endl;
        switch (select) {
            case 1:
                newEmployee();
                break;
            case 2:
                newContractor();
                break;
            case 3:
                newManager();
                break;
            case 4:
                listEmployees();
                break;
            case 5:
                searchEmployee();
                break;
            case 6:
                amountsToTotalWageCost();
                break;
            case 7:
                modifyEmployeeData();
                break;
            case 8:
                saveToFile();
                break;
            case 9:
                deleteEmployee();
                break;
            case 10:
                filterByType();
                break;
            case 11:
                filterBySickDays();
                break;
            case 12:
                filterBySalaryRange();
                break;
            case 0:
                isRunning = false;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    }
}

// Új dolgozó hozzáadása esetén is meg lehetne hívni a saveToFile metódust, így automatikusan mentésre kerülni a fájlba, nem kellene plusz menüpont
void Menu::newEmployee() {
    string name, birthDay;
    double salary;
    int daysWorked, illnessDays;

    cout << "Name: ";
    name = readCheck<string>();
    cout << "Birthday (YYYY-MM-DD): ";
    birthDay = readDate();
    cout << "Salary: ";
    salary = readCheck<double>();
    cout << "Number of worked days: ";
    daysWorked = readCheck<int>();
    cout << "Number of illness days: ";
    illnessDays = readCheck<int>();

    Employee* newEmployee = new Employee(name, birthDay, salary, daysWorked, illnessDays);
    workers.push_back(newEmployee);
}

void Menu::newContractor() {
    string name, birthDay;
    double hourlyRate;
    int workingHours;

    cout << "Name: ";
    name = readCheck<string>();
    cout << "Birthday (YYYY-MM-DD): ";
    birthDay = readDate();
    cout << "Hourly rate: ";
    hourlyRate = readCheck<double>();
    cout << "Working hours: ";
    workingHours = readCheck<int>();

    Contractor* newContractor = new Contractor(name, birthDay, hourlyRate, workingHours);
    workers.push_back(newContractor);
}

void Menu::newManager() {
    string name, birthDay;
    double monthlyFixedSalary, companyResult;

    cout << "Name: ";
    name = readCheck<string>();
    cout << "Birthday (YYYY-MM-DD): ";
    birthDay = readDate();
    cout << "Monthly fixed salary : ";
    monthlyFixedSalary = readCheck<double>();
    cout << "Company result: ";
    companyResult = readCheck<double>();

    Manager* newManager = new Manager(name, birthDay, monthlyFixedSalary, companyResult);
    workers.push_back(newManager);
}

void Menu::listEmployees() {
    if (workers.empty()) {
        std::cout << "The list is empty." << std::endl;
    } else {
        int index = 0;
        for (Worker* worker : workers) {
                index += 1;
            std::cout << index << ". worker: " << worker->toString() << std::endl;
        }
    }
}

void Menu::searchEmployee() {
    string searchCriteria;
    cout << "Enter the search criteria (name or date of birth): ";
    cin >> searchCriteria;

    for (Worker* worker : workers) {
        if (worker->getName() == searchCriteria || worker->getBirthDay() == searchCriteria) {
            cout << worker->toString() << endl;
        }
    }
}

void Menu::amountsToTotalWageCost() {
    double totalCost = 0.0;
    for (Worker* worker : workers) {
        totalCost += worker->costOfEmployment();
    }
    cout << "Total cost: " << totalCost << endl;
}

// Csak a nevet és a születési dátumot lehet módosítani, egyéb értékek esetén ugyan így kell eljárni, csak pl. a fizetésnél újra kell számolni
void Menu::modifyEmployeeData() {
    if (workers.empty()) {
        cout << "The list is empty." << endl;
        return;
    }

    listEmployees();

    cout << "Enter the index of the employee to modify: ";
    int index = readCheck<int>() - 1;
    if (index < 0 || index >= static_cast<int>(workers.size())) {
        cout << "Invalid index!" << endl;
        return;
    }

    Worker* selectedWorker = workers[index];

    string newName, newBirthDay;
    cout << "Enter new name (leave empty for no change): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newName);
    if (!newName.empty()) {
        selectedWorker->setName(newName);
    }

    cout << "Enter new birth date (YYYY-MM-DD, leave empty for no change): ";
    getline(cin, newBirthDay);
    if (!newBirthDay.empty()) {
        try {
            newBirthDay = dateCheck::stodate(newBirthDay);
            selectedWorker->setBirthDay(newBirthDay);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
}

void Menu::saveToFile() {
    std::ofstream file("workers.txt", std::ios::trunc); // Hozzáfûzési mód
    for (auto& worker : workers) {
        if (dynamic_cast<Employee*>(worker) != nullptr) {
            file << "(Employee) | ";
        } else if (dynamic_cast<Manager*>(worker) != nullptr) {
            file << "(Manager) | ";
        } else if (dynamic_cast<Contractor*>(worker) != nullptr) {
            file << "(Contractor) | ";
        }

        file << worker->toString() << "\n";
    }
    file.close();
    cout << "List saved to worked.txt file." << endl;
}

void Menu::loadFromFile() {
    std::ifstream file("workers.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("(Manager)") == 0) {
            std::string name, birthDay;
            double monthlyFixedSalary, companyResult;

            std::istringstream iss(line.substr(string("(Manager) | ").length()));
            std::string token;

            while (std::getline(iss, token, ',')) {
                std::istringstream tokenStream(token);
                std::string key;
                std::string value;

                std::getline(tokenStream, key, ':');
                std::getline(tokenStream, value);
                value = value.substr(value.find_first_not_of(" "));

                if (key.find("Name") != std::string::npos) {
                    name = value;
                } else if (key.find("Birthday") != std::string::npos) {
                    birthDay = value;
                } else if (key.find("Monthly fixed salary") != std::string::npos) {
                    monthlyFixedSalary = std::stod(value);
                } else if (key.find("Company result") != std::string::npos) {
                    companyResult = std::stoi(value);
                }
            }

            Manager* manager = new Manager(name, birthDay, monthlyFixedSalary, companyResult);
            workers.push_back(manager);


        } else if (line.find("(Employee)") == 0) {
            std::string name, birthDay;
            double monthlySalary;
            int totalWorkDaysInMonth, numOfIllnessDays;

            std::istringstream iss(line.substr(string("(Employee) | ").length()));
            std::string token;

            while (std::getline(iss, token, ',')) {
                std::istringstream tokenStream(token);
                std::string key;
                std::string value;

                std::getline(tokenStream, key, ':');
                std::getline(tokenStream, value);
                value = value.substr(value.find_first_not_of(" "));

                if (key.find("Name") != std::string::npos) {
                    name = value;
                } else if (key.find("Birthday") != std::string::npos) {
                    birthDay = value;
                } else if (key.find("Monthly salary") != std::string::npos) {
                    monthlySalary = std::stod(value);
                } else if (key.find("Total work days in month") != std::string::npos) {
                    totalWorkDaysInMonth = std::stoi(value);
                } else if (key.find("Number of illness days") != std::string::npos) {
                    numOfIllnessDays = std::stoi(value);
                }
            }

            Employee* employee = new Employee(name, birthDay, monthlySalary, totalWorkDaysInMonth, numOfIllnessDays);
            workers.push_back(employee);

        } else if (line.find("(Contractor)") == 0) {
            std::string name, birthDay;
            double hourlyRate;
            int workingHours;

            std::istringstream iss(line.substr(string("(Contractor) | ").length()));
            std::string token;
            while (std::getline(iss, token, ',')) {
                std::istringstream tokenStream(token);
                std::string key;
                std::string value;

                std::getline(tokenStream, key, ':');
                std::getline(tokenStream, value);
                value = value.substr(value.find_first_not_of(" "));

                if (key.find("Name") != std::string::npos) {
                    name = value;
                } else if (key.find("Birthday") != std::string::npos) {
                    birthDay = value;
                } else if (key.find("Hourly rate") != std::string::npos) {
                    hourlyRate = std::stod(value);
                } else if (key.find("Working hours") != std::string::npos) {
                    workingHours = std::stoi(value);
                }
            }

            Contractor* contractor = new Contractor(name, birthDay, hourlyRate, workingHours);
            workers.push_back(contractor);
        }

    }
    file.close();
}

void Menu::deleteEmployee() {
    if (workers.empty()) {
        cout << "The list is empty." << endl;
        return;
    }

    listEmployees();

    cout << "Enter the index of the employee to delete: ";
    int index = readCheck<int>() - 1;
    if (index < 0 || index >= static_cast<int>(workers.size())) {
        cout << "Invalid index!" << endl;
        return;
    }

    delete workers[index];
    workers.erase(workers.begin() + index);

    saveToFile();
}

void Menu::filterByType() {
    cout << "Select type to filter (1- Employee, 2- Contractor, 3- Manager): ";
    int typeChoice = readCheck<int>();

    for (auto& worker : workers) {
        switch (typeChoice) {
            case 1:
                if (dynamic_cast<Employee*>(worker) != nullptr) {
                    cout << worker->toString() << endl;
                }
                break;
            case 2:
                if (dynamic_cast<Contractor*>(worker) != nullptr) {
                    cout << worker->toString() << endl;
                }
                break;
            case 3:
                if (dynamic_cast<Manager*>(worker) != nullptr) {
                    cout << worker->toString() << endl;
                }
                break;
            default:
                cout << "Invalid type selection." << endl;
                return;
        }
    }
}

void Menu::filterBySickDays() {
    for (auto& worker : workers) {
        Employee* emp = dynamic_cast<Employee*>(worker);
        if (emp != nullptr && emp->getNumOfIllnessDays() > 0) {
            cout << worker->toString() << endl;
        }
    }
}

void Menu::filterBySalaryRange() {
    double lowerBound, upperBound;
    cout << "Enter lower bound of salary: ";
    lowerBound = readCheck<double>();
    cout << "Enter upper bound of salary: ";
    upperBound = readCheck<double>();

    for (auto& worker : workers) {
        if (worker->calcSalary() >= lowerBound && worker->calcSalary() <= upperBound) {
            cout << worker->toString() << endl;
        }
    }
}


