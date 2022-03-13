#include "Employee.h"

int main(int argc, char* argv[]) {
    ofstream out(argv[0], ios::binary);
    int num = atoi(argv[1]);
    for (int i = 0; i < num; i++) {
        employee e;
        cin >> e.num;
        cin >> e.name;
        cin >> e.hours;
        out.write((char*)&e, sizeof(employee));
    }
    out.close();
    return 0;
}