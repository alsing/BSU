#include <iostream>

using namespace std;

const long long c = 1000000007;

long long binpow(long long base, long long p) {
    if (p == 1) {
        return base;
    }

    if (p % 2 == 0) {
        long long t = binpow(base, p / 2);
        return t * t % c;
    } else {
        return binpow(base, p - 1) * base % c;
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    long long  factNumerator = 1;
    for (int i = 1; i <= n; i++) {
        factNumerator = (factNumerator * i) % c;
    }

    long long factDenominator = 1;
    for (int i = 1; i <= k; i++) {
        factDenominator = (factDenominator * i) % c;
    }

    for (int i = 1; i <= n - k; i++) {
        factDenominator = (factDenominator * i) % c;
    }

    cout << (factNumerator * binpow(factDenominator, c - 2)) % c;
    return 0;
}