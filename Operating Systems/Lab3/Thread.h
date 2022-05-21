#ifndef LAB3_THREAD_H
#define LAB3_THREAD_H

#include <Windows.h>

struct thread {
    int arr_size;
    int* arr;
    int index;
    HANDLE start, stop;
    HANDLE ct[2];
};

#endif //LAB3_THREAD_H
