#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main() {
    int N;
    long long K;
    cin >> N >> K;

    string arr[3] = {"chu", "ka", "pi"};
    string res = "";

    int all;
    int d;
    int i = 0;

    /*while (K > 3) {
        all = (11 - N) * pow(3, N - 2);
        d = all / 3;
        i = 0;

        while (K > d) {
            K -= d;
            i++;
        }
        res += arr[i];

        N--;
    }

    res +=arr[K - 1];
    cout << res;*/
    int a = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int h = 0; h < 3; h++) {
                for (int k = 0; k < 3; k++) {
                    for (int f = 0; f < 3; f++) {
                        //for (int z = 0; z < 3; z++) {
                            res = arr[i] + arr[j] + arr[h] + arr[k] + arr[f];// + arr[z];
                            cout << a << ' ' << res;
                            if (!(res.find("pipipi") == string::npos && res.find("kakaka") == string::npos &&
                                res.find("chukapi") == string::npos)) {
                                cout << "   !!!!!!!!!!!!";
                            }
                            else a++;
                            cout << '\n';
                        //}
                    }
                }
            }
        }
    }

    return 0;
}
