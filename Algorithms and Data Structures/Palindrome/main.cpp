#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


int main() {
    fstream in("input.txt");

    string s;
    in >> s;

    int length = s.length();

    vector <vector <int> > B(length, vector(length, 0));

    for (int i = 0; i < length - 1; i++) {
        B[i][i] = 1;
        B[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
    }
    B[length - 1][length - 1] = 1;

    for (int j = 2; j < length; j++) {
        for (int i = j - 2; i >= 0; i--) {
            if (s[i] == s[j])
                B[i][j] = B[i +  1][j - 1] + 2;
            else B[i][j] = max(B[i][j - 1], B[i + 1][j]);
        }
    }

    /*for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j ++) {
            cout << B[i][j] << " ";
        }
        cout << "\n";
    }*/

    string res = "";

    int i = 0, j = length - 1;
    while (j >= i) {
        if (s[i] == s[j]) {
            res += s[i];
            i++;
            j--;
        }
        else
            B[i][j - 1] > B[i + 1][j] ? j-- : i++;
    }

    if (B[i - 1][j + 1] == 2){
        string temp = res;
        reverse(res.begin(), res.end());
        res = temp + res;
    }
    else {
        string temp = res.substr(0, res.length() - 1);
        reverse(res.begin(), res.end());
        res = temp + res;
    }

    fstream out("output.txt", ios::out);
    out << B[0][length - 1] << '\n' << res;

    in.close();
    out.close();

    return 0;
}
