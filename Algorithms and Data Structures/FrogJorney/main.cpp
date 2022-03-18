#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct frog{
    int number;
    int index;
};

int main() {
    int n;
    cin >> n;

    if (n == 1) {
        int mosquito;
        cin >> mosquito;
        cout << mosquito << "\n1";
    }
    else if (n == 2)
        cout << -1;
    else {
        vector <int> mosquitos(n);

        for (int i = 0; i < n; i++) {
            cin >> mosquitos[i];
        }

        frog jumps[n];
        jumps[0].number = mosquitos[0];
        jumps[0].index = -1;
        jumps[1].number = -2147483648;
        jumps[1].index = -1;
        jumps[2].number = mosquitos[0] + mosquitos[2];
        jumps[2].index = 0;

        frog temp;
        int index;

        for (int i = 3; i < n; i++) {
            if (jumps[i - 3].number > jumps[i - 2].number){
                temp = jumps[i - 3];
                index = i - 3;
            }
            else {
                temp = jumps[i - 2];
                index = i - 2;
            }

            jumps[i].number = temp.number + mosquitos[i];
            jumps[i].index = index;
        }

        cout << jumps[n - 1].number << '\n';
        string s = to_string(n);
        reverse(s.begin(), s.end());
        index = jumps[n - 1].index;
        while (index != -1) {
            string temp = to_string(index + 1);
            reverse(temp.begin(), temp.end());
            s += ' ' + temp;
            index = jumps[index].index;
        }

        reverse(s.begin(), s.end());
        cout << s;
    }

    return 0;
}