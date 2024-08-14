#pragma once

#include <vector>
#include "worker.hpp"

class Menu {
    public:
        ~Menu();
        Menu();
        void execute();

    private:
        void newEmployee();
        void newContractor();
        void newManager();
        void listEmployees();
        void searchEmployee();
        void amountsToTotalWageCost();
        void modifyEmployeeData();
        void saveToFile();
        void loadFromFile();
        void deleteEmployee();
        void filterByType();
        void filterBySickDays();
        void filterBySalaryRange();
        std::vector<Worker*> workers;
};

