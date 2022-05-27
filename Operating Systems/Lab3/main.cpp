#include <iostream>
#include "thread.h"

CRITICAL_SECTION cs;

DWORD WINAPI ThreadActions(LPVOID lpParam) {
    thread information= *static_cast<thread*>(lpParam);
    srand(information.index);
    bool end_thread = 0;
    int n_marked = 0;
    WaitForSingleObject(information.start, INFINITE);

    int current_index;
    while (!end_thread) {
        current_index = rand() % information.array_size;
        EnterCriticalSection(&cs);

        if (information.array[current_index] == 0) {
            Sleep(5);
            information.array[current_index]=information.index;
            LeaveCriticalSection(&cs);
            n_marked++;
            Sleep(5);
        }
        else {
            std::cout << "\nThread № " << information.index << "; n_marked = " << n_marked << "; element " <<
            current_index << " can not be marked!";
            LeaveCriticalSection(&cs);
            SetEvent(information.stop);
            int action_marker = WaitForMultipleObjects(2, information.other_actions, FALSE, INFINITE) - WAIT_OBJECT_0;
            if (!action_marker)
                end_thread = 1;
        }
    }
    for (int i = 0; i < information.array_size; i++) {
        if(information.array[i] == information.index)
            information.array[i] = 0;
    }

    return 0;
}

void PrintArray(int* arr, int size) {
    std::cout << "Array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    int array_length;
    std::cin >> array_length;
    int* array = new int[array_length];
    for (int i = 0; i < array_length; i++) {
        array[i] = 0;
    }

    int n_marker;
    std::cin >> n_marker;

    for (int i = 0; i < n_marker; i++) {

    }

    delete[] array;

    return 0;
}
