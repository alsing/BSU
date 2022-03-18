#include <iostream>
#include <Windows.h>

using namespace std;

struct arrStruct {
    arrStruct(int size, int *array) : size(size), array(array) {}

    int size;
    int* array;
    int min;
    int max;
    int average;
};

DWORD WINAPI min_max(LPVOID lpParam) {
    arrStruct* arrSt = (arrStruct*)lpParam;

    arrSt->min = arrSt->max = arrSt->array[0];
    for (int i = 0; i < arrSt->size; i++) {
        if (arrSt->array[i] > arrSt->max)
            arrSt->max = arrSt->array[i];
        Sleep(7);
        if (arrSt->array[i] < arrSt->min)
            arrSt->min = arrSt->array[i];
        Sleep(7);
    }

    cout << "Max element: " << arrSt->max << '\n';
    cout << "Min element: " << arrSt->min << '\n';

    return 0;
}

DWORD WINAPI average(LPVOID lpParam) {
    arrStruct* arrSt = (arrStruct*)lpParam;

    arrSt->average = arrSt->array[0];
    for (int i = 1; i < arrSt->size; i++) {
        arrSt->average += arrSt->array[i];
        Sleep(12);
    }

    arrSt->average /= arrSt->size;

    cout << "Average: " << arrSt->average << '\n';

    return 0;
}

int main() {

    return 0;
}
