#include <iostream>
#include <cstdlib>

using namespace std;

struct employee
{
    int num;
    char name[10];
    double hours;
};


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


