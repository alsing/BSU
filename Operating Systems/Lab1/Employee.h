#ifndef LAB1_EMPLOYEE_H
#define LAB1_EMPLOYEE_H

#include <iostream>
#include <cstdlib>
#include <fstream>

const int nameLength = 10;

struct employee {
    int num;
    char name[nameLength];
    double hours;
};

#endif //LAB1_EMPLOYEE_H