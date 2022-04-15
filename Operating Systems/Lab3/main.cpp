#include <iostream>
#include <Windows.h>

using namespace std;


DWORD WINAPI thread_actions(LPVOID lpParam) {
    srand(*(DWORD*)lpParam);

    return 0;
}

int main() {
    int n;
    cin >> n;
    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        array[i] = 0;
    }

    int n_marker;
    cin >> n_marker;

    for (int i = 0; i < n_marker; i++) {

    }

    return 0;
}
