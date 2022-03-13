#include "Employee.h"

using namespace std;


int main(int argc, char* argv[]) {
    ifstream in(argv[0], ios::binary);
    ofstream out(argv[1]);
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


