#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iomanip>
#include <sstream>

class Employee {
    std::string name;
    int birth_year;
    double salary;
public:
    Employee(std::string n, int y, double s) : name(n), birth_year(y), salary(s) {}

    std::string getName() const { return name; }
    int getBirthYear() const { return birth_year; }
    double getSalary() const { return salary; }

    void setName(std::string n) { name = n; }
    void setBirthYear(int y) { birth_year = y; }
    void setSalary(double s) { salary = s; }
};

void addEmployee(std::list<Employee> &employees) {
    std::string name;
    int birth_year;
    double salary;

    std::cout << "Enter the name: ";
    std::cin.ignore();
    getline(std::cin, name);
    std::cout << "Enter the birth year: ";
    std::cin >> birth_year;
    std::cout << "Enter the salary: ";
    std::cin >> salary;

    Employee employee(name, birth_year, salary);
    employees.push_back(employee);
}

void loadEmployees(std::list<Employee> &employees, std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: could not open file " << filename << std::endl;
    } else {
        std::string line;
        while (getline(file, line)) {
            std::string name = line.substr(0, 30);
            name.erase(0, name.find_first_not_of(' '));
            int birth_year = stoi(line.substr(30, 5));
            double salary = stod(line.substr(35, 10));

            Employee employee(name, birth_year, salary);
            employees.push_back(employee);
        }
        std::cout << "Loaded " << employees.size() << " employees from " << filename << std::endl;
    }

    file.close();
}

void saveEmployees(std::list<Employee> &employees, std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << std::endl;
        return;
    }

    for (auto &employee: employees) {
        std::string name = employee.getName();
        int name_spaces = 30 - name.length();

        int birth_year = employee.getBirthYear();
        int birth_year_spaces = 5 - std::to_string(birth_year).length();

        double salary = employee.getSalary();
        int salary_spaces = 10;

        std::stringstream salary_stream;
        salary_stream << std::fixed << std::setprecision(2) << salary;
        std::string salary_string = salary_stream.str();
        salary_spaces -= salary_string.length();

        file << std::string(name_spaces, ' ') << name << std::string(birth_year_spaces, ' ')
             << birth_year << std::string(salary_spaces, ' ') << salary_string << std::endl;
    }

    file.close();
}

void printEmployee(Employee &employee) {
    std::cout << employee.getName() << ", born in " << employee.getBirthYear() << ", earns $" << employee.getSalary()
         << std::endl;
}

void searchEmployee(std::list<Employee> &employees) {
    std::string query;

    std::cout << "Enter the name to search for: ";
    std::cin.ignore();
    getline(std::cin, query);

    bool found = false;
    for (auto &employee: employees) {
        if (employee.getName().find(query) != std::string::npos) {
            found = true;
            printEmployee(employee);
        }
    }

    if (!found) {
        std::cout << "No employee found with that name." << std::endl;
    }
}

void EditEmployee(std::list<Employee> &employees) {
    std::string searchName;
    std::cout << "Enter the last name of the employee to search: ";
    std::cin >> searchName;

    bool found = false;
    for (auto &employee: employees) {
        if (employee.getName() == searchName) {
            found = true;

            std::cout << "Selected employee:" << std::endl;
            std::cout << "Name: " << employee.getName() << std::endl;
            std::cout << "Birth year: " << employee.getBirthYear() << std::endl;
            std::cout << "Salary: " << employee.getSalary() << std::endl;

            int choice;
            std::cout << "Enter the number of the field to change (1 - Name, 2 - Birth year, 3 - Salary): ";
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::string newName;
                    std::cout << "Enter the new name: ";
                    std::cin >> newName;
                    employee.setName(newName);
                    break;
                }
                case 2: {
                    int newBirthYear;
                    std::cout << "Enter the new birth year: ";
                    std::cin >> newBirthYear;
                    employee.setBirthYear(newBirthYear);
                    break;
                }
                case 3: {
                    double newSalary;
                    std::cout << "Enter the new salary: ";
                    std::cin >> newSalary;
                    employee.setSalary(newSalary);
                    break;
                }
                default: {
                    std::cout << "Error: invalid input" << std::endl;
                    break;
                }
            }

            std::cout << "Employee information updated!" << std::endl;

            break;
        }
    }

    if (!found) {
        std::cout << "Employee not found..." << std::endl;
    }
}

void youngestEmployee(std::list<Employee> &employees) {
    Employee youngest("", 9999, 0.0);
    for (auto &employee: employees) {
        if (employee.getBirthYear() > 0 && employee.getBirthYear() < youngest.getBirthYear()) {
            youngest = employee;
        }
    }

    if (youngest.getName().empty()) {
        std::cout << "No employees found." << std::endl;
    } else {
        std::cout << "The youngest employee is ";
        printEmployee(youngest);
    }
}

int main() {
    std::string filename = "../files/employees.txt";
    std::list<Employee> employees, back;
    loadEmployees(employees, filename);

    std::cout << "Welcome to the employee database." << std::endl;
    while (true) {
        try {
            back = employees;

            std::cout << std::endl << "Select an option:" << std::endl;
            std::cout << "1. Save changes to the database" << std::endl;
            std::cout << "2. Print database" << std::endl;
            std::cout << "3. Add an employee" << std::endl;
            std::cout << "4. Edit an employee" << std::endl;
            std::cout << "5. Search for an employee" << std::endl;
            std::cout << "6. Find the youngest employee" << std::endl;
            std::cout << "7. Exit" << std::endl;

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    saveEmployees(employees, filename);
                    break;
                case 2:
                    for (auto employee: employees)
                        printEmployee(employee);
                    break;
                case 3:
                    addEmployee(employees);
                    break;
                case 4:
                    EditEmployee(employees);
                    break;
                case 5:
                    searchEmployee(employees);
                    break;
                case 6:
                    youngestEmployee(employees);
                    break;
                case 7:
                    std::cout << "Thanks for using the program. Goodbye!!!" << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice." << std::endl;
            }
        } catch(const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            employees = back;
        }
    }
}
