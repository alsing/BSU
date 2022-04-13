#include <iostream>
#include <vector>

using namespace std;


bool compare(int a, int b) {
    if (b != 0)
        return abs(a) % abs(b) == 0;
    else return 0;
}

int main() {

    int num ;
    cin >> num;

    vector <long> A(num);

    for (int i = 0; i < num; i++)
        cin >> A[i];

    vector <long> D(num);

    D[0] = 1;
    int maxPos = 0;

    for (int i = 1; i < num; i++) {
        maxPos = 0;
        for (int j = 0; j < i; j++) {
            if (compare(A[i], A[j]) && D[j] > D[maxPos])
                maxPos = j;
            D[i] = D[maxPos] + 1;
        }
    }

    int maxElpos = 0;
    for (int i = 1; i < num; i++) {
        if (D[i] > D[maxElpos])
            maxElpos = i;
    }

    vector <long> vec(1);
    vec[0] = maxElpos + 1;
    for (int i = maxElpos - 1; i >= 0; i--) {
        if (D[i] == D[maxElpos] - 1 && compare(A[maxElpos], A[i])) {
            vec.push_back(i + 1);
            maxElpos = i;
        }
    }

    cout << vec.size() << '\n';

    cout << vec[vec.size() - 1];
    for (int i = vec.size() - 2; i >= 0; i--) {
        cout << ' ' << vec[i];
    }

    return 0;
}