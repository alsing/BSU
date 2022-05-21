#include "Employee.h"

int main(int argc, char* argv[]) {
    std::ifstream in(argv[0], std::ios::binary);
    std::ofstream out(argv[1]);
    double wage = atof(argv[2]);
    employee e;

    out << "Report on a file " << argv[0] << '\n';
    out << "Employee number, employee name, working hours, salary:\n";
    while (in.read((char*)&e, sizeof(employee))) {
        out << e.num << " " << e.name << " " << e.hours << " " << e.hours * wage << '\n';
    }

    in.close();
    out.close();
    return 0;
}


