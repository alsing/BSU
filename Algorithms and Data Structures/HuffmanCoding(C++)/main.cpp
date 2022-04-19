#include <iostream>
#include <queue>
#include <fstream>

using namespace std;


int main() {
    ifstream in("huffman.in");
    int n;
    in >> n;

    priority_queue <long long, vector<long long>, greater<long long>> q;
    long long el;
    for (int i = 0; i < n; i++) {
        in >> el;
        q.push(el);
    }

    long long s = 0;
    while (q.size() > 1) {
        el = q.top();
        q.pop();
        el += q.top();
        q.pop();
        q.push(el);
        s += el;
    }

    ofstream out("huffman.out");
    out << s;

    in.close();
    out.close();

    return 0;
}
