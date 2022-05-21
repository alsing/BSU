#include "Employee.h"

int main(int argc, char* argv[]) {
    std::ofstream out(argv[0], std::ios::binary);
    int num = atoi(argv[1]);
    for (int i = 0; i < num; i++) {
        employee e;
        std::cin >> e.num;
        std::cin >> e.name;
        std::cin >> e.hours;
        out.write((char*)&e, sizeof(employee));
    }
    out.close();
    return 0;
}