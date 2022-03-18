#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct matrix {
    int m;
    int n;
};

int main() {
    fstream in("input.txt");

    int number;
    in >> number;

    matrix arr[number];
    int** B = new int*[number];
    for(int i = 0; i < number; i++) {
        B[i] = new int[number];
        for(int j = 0; j < number; j++) {
            B[i][j] = 0;
        }
    }

    for (int i = 0; i < number; i++) {
        in >> arr[i].n;
        in >> arr[i].m;
    }

    for (int i = 0; i < number - 1; i++) {
        B[i][i + 1] = arr[i].n * arr[i].m * arr[i + 1].m;
    }

    for (int j = 2; j < number; j++) {
        for (int i = j - 2; i >= 0; i--) {
            int minOps = B[i][i] + B[i + 1][j] + arr[i].n * arr[i].m * arr[j].m;
            for (int k = i + 1; k < j; k++) {
                int temp = B[i][k] + B[k + 1][j] + arr[i].n * arr[k].m * arr[j].m;
                if (temp < minOps)
                    minOps = temp;
            }
            B[i][j] = minOps;
        }
    }

    fstream out("output.txt", ios::out);
    out << B[0][number - 1];

    in.close();
    out.close();

    return 0;
}
