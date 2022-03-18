#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main() {
    fstream in("input.txt");

    int num ;
    in >> num;

    vector <int> A(num);

    for (int i = 0; i < num; i++)
        in >> A[i];

    vector <int> D(num, 2147483647);

    int maxPos = 0;
    for (int i = 0; i < num; i++) {
        int j = lower_bound(D.begin(), D.end(), A[i]) - D.begin();
        if (j > maxPos)
            maxPos = j;
        D[j] = A[i];
    }

    fstream out("output.txt", ios::out);
    out << maxPos + 1;

    in.close();
    out.close();

    return 0;
}