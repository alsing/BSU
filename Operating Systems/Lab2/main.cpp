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
        if (arrSt->array[i] < arrSt->array[arrSt->min])
            arrSt->min = i;
        Sleep(7);
        if (arrSt->array[i] > arrSt->array[arrSt->max])
            arrSt->max = i;
        Sleep(7);
    }

    cout << "Min element: " << arrSt->array[arrSt->min] << '\n';
    cout << "Max element: " << arrSt->array[arrSt->max] << '\n';

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
    int size;
    cin >> size;

    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    arrStruct* arrSt = new arrStruct(size, arr);

    HANDLE minMaxThread = CreateThread(NULL,0,min_max,LPVOID(arrSt), 0, NULL);
    HANDLE averageThread = CreateThread(NULL,0,average,LPVOID(arrSt), 0, NULL);

    WaitForSingleObject(minMaxThread, INFINITE);
    WaitForSingleObject(averageThread, INFINITE);
    CloseHandle(minMaxThread);
    CloseHandle(averageThread);

    arr[arrSt->min] = arrSt->average;
    arr[arrSt->max] = arrSt->average;

    cout << "Result array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }

    return 0;
}
