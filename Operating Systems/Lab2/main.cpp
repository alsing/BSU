#include <iostream>
#include <Windows.h>
#include "array_struct.h"


DWORD WINAPI MinMax(LPVOID lpParam) {
    const int sleepTime = 7;
    arrayStruct* array_struct = (arrayStruct*)lpParam;

    array_struct->min = array_struct->max = array_struct->array[0];
    for (int i = 0; i < array_struct->size; i++) {
        if (array_struct->array[i] < array_struct->array[array_struct->min])
            array_struct->min = i;
        Sleep(sleepTime);
        if (array_struct->array[i] > array_struct->array[array_struct->max])
            array_struct->max = i;
        Sleep(sleepTime);
    }

    std::cout << "Min element: " << array_struct->array[array_struct->min] << '\n';
    std::cout << "Max element: " << array_struct->array[array_struct->max] << '\n';

    return 0;
}

DWORD WINAPI Average(LPVOID lpParam) {
    const int sleepTime = 12;
    arrayStruct* array_struct = (arrayStruct*)lpParam;

    array_struct->average = array_struct->array[0];
    for (int i = 1; i < array_struct->size; i++) {
        array_struct->average += array_struct->array[i];
        Sleep(sleepTime);
    }

    array_struct->average /= array_struct->size;

    std::cout << "Average: " << array_struct->average << '\n';

    return 0;
}

int main() {
    int size;
    std::cin >> size;

    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    arrayStruct* array_struct = new arrayStruct(size, arr);

    HANDLE min_max_thread = CreateThread(NULL, 0, MinMax, LPVOID(array_struct), 0, NULL);
    HANDLE average_thread = CreateThread(NULL, 0, Average, LPVOID(array_struct), 0, NULL);

    WaitForSingleObject(min_max_thread, INFINITE);
    WaitForSingleObject(average_thread, INFINITE);
    CloseHandle(min_max_thread);
    CloseHandle(average_thread);

    arr[array_struct->min] = array_struct->average;
    arr[array_struct->max] = array_struct->average;

    std::cout << "Result array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }

    return 0;
}
