# Workforce Management System

This project was developed as an assignment for the **C++ Programming Language** course. The goal was to create a program that manages the workforce for a company, calculating salaries and handling various categories of workers.

## Project Description

The program manages employees of a company, who can be classified into different categories:

1. **Employee (Salaried)**: Receives a fixed monthly salary, with adjustments for days worked and sick leave.
2. **Contractor (Hourly Paid)**: Paid based on the number of reported work hours and a pre-agreed hourly rate.
3. **Manager (Salaried)**: Receives a fixed monthly salary and a percentage of the company's profit or a deduction in case of a loss.

### Salary Calculation

- **Employee**: Paid a fixed monthly salary, adjusted according to the number of days worked and sick leave (60% of salary during sick leave). The company pays 100% additional cost on the salary for various contributions.
- **Contractor**: Paid based on reported work hours and an agreed hourly rate. The company pays an additional 30% on the total payment as contributions.
- **Manager**: Receives a fixed monthly salary with a bonus or deduction based on the company's performance. The company pays 100% additional cost on the salary.

### Features

- **Basic Requirements:**
  - Add new employees to the system.
  - List all employees and calculate end-of-month salaries based on individually entered performance data (workdays, sick leave for employees; work hours for contractors; company results for managers).
- **Intermediate Features:**
  - Search for employees by name or birthdate and calculate the salary for the selected employee based on performance data.
  - Calculate the total wage cost for the company (including contributions).
- **Advanced Features:**
  - Modify employee data such as salary, name, and birthdate. Delete employees from the database.
  - Perform operations like filtering employees based on sick leave, type, or salary range.
- **Complete Solution:**
  - Save and load employee data to/from a file. Perform additional filtering based on criteria such as sick leave status, category, or salary range.

## File Structure

- `main.cpp`: Entry point of the program.
- `menu.hpp` / `menu.cpp`: Handles the user interface and main operations.
- `worker.hpp` / `worker.cpp`: Base class for all worker types.
- `employee.hpp` / `employee.cpp`: Employee-specific logic.
- `contractor.hpp` / `contractor.cpp`: Contractor-specific logic.
- `manager.hpp` / `manager.cpp`: Manager-specific logic.
- `stoi.hpp` / `stoi.cpp`: Custom string to integer conversion with input validation.
- `stod.hpp` / `stod.cpp`: Custom string to double conversion with input validation.
- `stodate.hpp` / `stodate.cpp`: Custom date validation and conversion.

## Additional Information

This project was developed as part of the C++ Programming Language course. It showcases the use of object-oriented programming principles, file handling, and basic user interface design in C++.
