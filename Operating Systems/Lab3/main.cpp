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
    std::cout << "Enter array length: ";
    std::cin >> array_length;

    int* array = new int[array_length];
    for (int i = 0; i < array_length; i++) {
        array[i] = 0;
    }

    int n_marker;
    std::cout << "Enter number of marker threads: ";
    std::cin >> n_marker;

    HANDLE* threads = new HANDLE[array_length];
    thread* information = new thread[array_length];
    bool* terminated_threads = new bool[array_length];
    HANDLE start = CreateEvent(NULL,TRUE,FALSE,NULL);
    HANDLE* stopped_threads = new HANDLE[array_length];

    for (int i = 0; i < n_marker; i++){
        information[i].array = array;
        information[i].array_size = array_length;
        information[i].index = i + 1;
        information[i].start = start;
        stopped_threads[i]= information[i].stop = CreateEvent(NULL, TRUE, FALSE, NULL);
        information[i].other_actions = new HANDLE[2];
        information[i].other_actions[0] = CreateEvent(NULL,FALSE,FALSE, NULL);
        information[i].other_actions[1] = CreateEvent(NULL,FALSE,FALSE, NULL);
        threads[i] = CreateThread(NULL, 0, ThreadActions,(LPVOID)(&information[i]),NULL,NULL);
        terminated_threads[i] = 0;
    }

    SetEvent(start);
    int n_ended=0;
    bool is_terminated = 0;

    while (n_ended != n_marker){
        WaitForMultipleObjects(n_marker, stopped_threads, TRUE, INFINITE);
        PrintArray(array, array_length);

        int thread_to_terminate;
        while (!is_terminated){
            std::cout << "Enter thread to terminate: ";
            std::cin >> thread_to_terminate;
            thread_to_terminate--;

            if (thread_to_terminate >= n_marker || thread_to_terminate < 0){
                std::cout << "There isn't such a thread!\n";
                continue;
            }
            if (terminated_threads[thread_to_terminate])
                std::cout << "This thread has been already terminated!\n";
            else {
                SetEvent(information[thread_to_terminate].other_actions[0]);
                WaitForSingleObject(threads[thread_to_terminate], INFINITE);
                PrintArray(array,array_length);
                terminated_threads[thread_to_terminate] = 1;
                is_terminated = 1;
                n_ended++;
            }
        }

        for(int i = 0; i < n_marker; i++){
            if(!terminated_threads[i]){
                ResetEvent(information[i].stop);
                SetEvent(information[i].other_actions[1]);
            }
        }
    }

    std::cout << "All threads are now terminated!\n";
    CloseHandle(start);

    for(int i = 0; i < n_marker; i++){
        CloseHandle(threads[i]);
        CloseHandle(stopped_threads[i]);
        CloseHandle(information[i].other_actions[0]);
        CloseHandle(information[i].other_actions[1]);
    }

    delete[] stopped_threads;
    delete[] terminated_threads;
    delete[] information;
    delete[] threads;
    delete[] array;
    DeleteCriticalSection(&cs);

    return 0;
}
