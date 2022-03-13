#include <iostream>
#include <cstdlib>
#include "Employee.h"

using namespace std;


int main(int argc, char* argv[]) {
    FILE* out = fopen(argv[0], "wb");
    int num = atoi(argv[1]);
    for (int i = 0; i < num; i++) {
        employee e;
        cin >> e.num;

        cin >> e.name;
        cout << e.name;
        cin >> e.hours;
        fwrite(&e, sizeof(e), 1, out);
    }
    fclose(out);
    return 0;
}


