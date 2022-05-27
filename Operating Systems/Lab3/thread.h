#ifndef LAB3_THREAD_H
#define LAB3_THREAD_H

#include <Windows.h>

struct thread {
    int array_size;
    int* array;
    int index;
    HANDLE start, stop, *other_actions;
};

#endif //LAB3_THREAD_H
