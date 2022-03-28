#include <iostream>
#include <fstream>
#include <vector>

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
    fstream in("input.txt");

    int n, m;
    in >> n >> m;

    long long factNumerator = 1;
    for (int i = 1; i <= n + m - 2; i++) {
        factNumerator = (factNumerator * i) % c;
    }

    long long factDenominator = 1;
    for (int i = 1; i <= n - 1; i++) {
        factDenominator = (factDenominator * i) % c;
    }

    for (int i = 1; i <= m - 1; i++) {
        factDenominator = (factDenominator * i) % c;
    }

    fstream out("output.txt", ios::out);
    out << (factNumerator * binpow(factDenominator, c - 2)) % c;

    in.close();
    out.close();

    return 0;
}