#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct road {
    int c1;
    int c2;
    bool demolished = false;
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
    int n, m, q;
    in >> n >> m >> q;

    vector <road> roads(m);
    for (int i = 0; i < m; ++i)
        in >> roads[i].c1 >> roads[i].c2;

    vector <int> demolishedRoads(q);
    for (int i = 0; i < q; ++i) {
        in >> demolishedRoads[i];
        roads[demolishedRoads[i] - 1].demolished = true;
    }

    int n_components = n;
    vector <int> parents(n);

    for (int i = 0; i < n; ++i)
        parents[i] = i;

    for (int i = 0; i < m; ++i) {
        if (!roads[i].demolished)
            unionSet(parents, roads[i].c1 - 1, roads[i].c2 - 1, n_components);
    }

    vector <int> connected(q);
    for (int i = q - 1; i >= 0; --i) {
        connected[i] = n_components > 1 ? 0 : 1;
        unionSet(parents, roads[demolishedRoads[i] - 1].c1 - 1, roads[demolishedRoads[i] - 1].c2 - 1, n_components);
    }

    ofstream out("output.txt");
    for (int i = 0; i < q; ++i)
        out << connected[i];

    in.close();
    out.close();

    return 0;
}