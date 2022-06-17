#ifndef LAB5_EMPLOYEE_H
#define LAB5_EMPLOYEE_H

#include <iostream>
#include <process.h>
#include <windows.h>
#include <iostream>
#include <fstream>+
#include <conio.h>
#include <algorithm>
#include <string>

struct employee {
    int num;
    char name[10];
    double hours;

    void print() {
        std::cout << "ID: " << num << "\nName: " << name << "\nHours: " << hours << '\n';
    }
};

int EmployeeComparator(const void* p1, const void* p2) {
    return ((employee*)p1)->num - ((employee*)p2)->num;
}

#endif //LAB5_EMPLOYEE_H
