#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int m, c;

int h(int x, int i) {
    return (x % m + c * i) % m;
}

int main() {
    ifstream in("input.txt");
    int n;
    in >> m >> c >> n;

    vector <int> table(m, -1);

    int el;
    bool isInTable;
    int pos;

    for (int i = 0; i < n; ++i) {
        isInTable = false;
        in >> el;
        for (int j = 0; j < m; ++j) {
            pos = h(el, j);
            if (table[pos] == el) {
                isInTable = true;
                break;
            }
            else if (table[pos] == -1)
                break;
        }

        if (isInTable == false) {
            for (int j = 0; j < m; ++j) {
                pos = h(el, j);
                if (table[pos] == -1) {
                    table[pos] = el;
                    break;
                }
            }
        }
    }

    ofstream out("output.txt");
    out << table[0];
    for (int i = 1; i < m; ++i) {
        out << ' ' << table[i];
    }

    in.close();
    out.close();

    return 0;
}
