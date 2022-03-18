#include <iostream>

using namespace std;

int main() {
    int number;
    int requestNumber;

    cin >> number;
    long* values = new long[number];

    for (int i = 0; i < number; i++) {
        cin >> values[i];
    }

    cin >> requestNumber;

    for (int i = 0; i < requestNumber; i++) {
        if (i) cout << '\n';

        long request;
        cin >> request;
        long middle;
        long low = -1;
        long high = number;

        while (high - low > 1) {
            middle = (high + low) / 2;
            if (values[middle] < request)
                low = middle;
            else
                high = middle;
        }

        long low1 = -1;
        long high1 = number;

        while (high1 - low1 > 1) {
            middle = (high1 + low1) / 2;
            if (values[middle] <= request)
                low1 = middle;
            else
                high1 = middle;
        }

        if (low == low1 && high == high1) {
            cout << 0 << ' ' << high << ' ';
            if (high < number)
                cout << high;
            else
                cout << number;
        }
        else {
            cout << 1 << ' ' << high << ' ' << high1;
        }
    }

    return 0;
}