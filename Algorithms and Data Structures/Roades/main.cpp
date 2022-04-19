#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct road {
    int c1;
    int c2;
};

int findSet(vector <int>& vec, int x) {
    if (vec[x] == x)
        return x;
    else return vec[x] = findSet(vec, vec[x]);
}

void unionSet(vector <int>& vec, int x, int y, int& n) {
    x = findSet(vec, x);
    y = findSet(vec, y);
    if (x != y) {
        vec[x] = y;
        n--;
    }
}

int main() {
    ifstream in("input.txt");
    int n, q;
    in >> n >> q;

    int n_components = n;
    vector <int> parents(n);

    for (int i = 0; i < n; ++i)
        parents[i] = i;

    vector <road> roads(q);

    for (int i = 0; i < q; ++i)
        in >> roads[i].c1 >> roads[i].c2;

    ofstream out("output.txt");
    for (int i = 0; i < q; ++i) {
        unionSet(parents, roads[i].c1 - 1, roads[i].c2 - 1, n_components);
        out << n_components << '\n';
    }

    in.close();
    out.close();

    return 0;
}
