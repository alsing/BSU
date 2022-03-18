#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


int main() {
    ifstream in("in.txt");

    int deleteSym, insertSym, replaceSym;
    in >> deleteSym >> insertSym >> replaceSym;

    string s1, s2;
    in >> s1 >> s2;

    int n = s1.length();
    int m = s2.length();

    vector <vector <int>> B(n + 1, vector <int>(m + 1, 0));

    for (int i = 1; i < n + 1; i++)
        B[i][0] = i * deleteSym;

    for (int j = 1; j < m + 1; j++)
        B[0][j] = j * insertSym;

    for (int i = 1; i < n + 1; i++){
        for (int j = 1; j < m + 1; j++) {
            int delta = s1[i - 1] == s2[j - 1] ? 0 : 1;
            B[i][j] = min(min(B[i - 1][j] + deleteSym, B[i][j - 1] + insertSym), B[i - 1][j - 1] + delta * replaceSym);
        }
    }

    ofstream out("out.txt");
    out << B[n][m];

    in.close();
    out.close();

    return 0;
}