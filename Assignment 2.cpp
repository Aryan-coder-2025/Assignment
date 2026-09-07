#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int id;
    string name;
    string department;
    double baseSalary;

public:

    // 1. Default Constructor
    // Creates an employee with no initial information.
    Employee() {
        id = 0;
        name = "Unknown";
        department = "Not Assigned";
        baseSalary = 0;
    }

    // 2. Constructor with ID and Name
    // Useful when only basic identity information is available.
    Employee(int id, string name) {
        this->id = id;
        this->name = name;
        department = "Not Assigned";
        baseSalary = 0;
    }

    // 3. Full Constructor
    // Used when complete employee information is available.
    Employee(int id, string name, string department, double baseSalary) {
        this->id = id;
        this->name = name;
        this->department = department;
        this->baseSalary = baseSalary;
    }

    // 4. Copy Constructor
    // Creates a new employee by copying another employee.
    Employee(const Employee &e) {
        id = e.id;
        name = e.name;
        department = e.department;
        baseSalary = e.baseSalary;
    }


    // 1. Base salary only
    double calculatePay() {
        return baseSalary;
    }

    // 2. Base salary + flat annual bonus
    double calculatePay(double bonus) {
        return baseSalary + bonus;
    }

    // 3. Base salary + overtime pay
    // Overtime pay = hours worked × hourly rate
    double calculatePay(double hours, double hourlyRate) {
        return baseSalary + (hours * hourlyRate);
    }

    // 4. Base salary + bonus - tax deduction
    // Tax is calculated on the total earnings.
    double calculatePay(double bonus, double taxPercentage, bool taxApplied) {
        double total = baseSalary + bonus;

        if (taxApplied) {
            double tax = total * taxPercentage / 100;
            total = total - tax;
        }

        return total;
    }


    // 1. Update only department
    void updateProfile(string newDepartment) {
        department = newDepartment;
    }

    // 2. Update only salary
    void updateProfile(double newSalary) {
        baseSalary = newSalary;
    }

    // 3. Update department and salary
    void updateProfile(string newDepartment, double newSalary) {
        department = newDepartment;
        baseSalary = newSalary;
    }


    // Display employee information
    void display() {
        cout << "\nEmployee ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "Base Salary: " << baseSalary << endl;
    }
};


int main() {


    // 1. Default constructor
    Employee e1;

    // 2. ID and Name constructor
    Employee e2(101, "Aryan");

    // 3. Full constructor
    Employee e3(102, "Rahul", "Engineering", 600000);

    // 4. Copy constructor
    Employee e4(e3);


    cout << "===== EMPLOYEE DETAILS =====" << endl;

    e1.display();
    e2.display();
    e3.display();
    e4.display();


    cout << "\n===== PAY CALCULATIONS ======" << endl;

    // Base salary only
    cout << "Base Pay: "
         << e3.calculatePay() << endl;

    // Base salary + bonus
    cout << "Pay with Bonus: "
         << e3.calculatePay(50000) << endl;

    // Base salary + overtime
    cout << "Pay with Overtime: "
         << e3.calculatePay(20, 500) << endl;

    // Base salary + bonus - tax
    cout << "Pay after Bonus and Tax: "
         << e3.calculatePay(50000, 10, true) << endl;



    cout << "\n====== PROFILE UPDATES =====" << endl;

    // Update department only
    e3.updateProfile("Artificial Intelligence");

    // Update salary only
    e3.updateProfile(700000);

    // Update department and salary together
    e3.updateProfile("AI Research", 800000);

    e3.display();


    return 0;
}