#include "array_struct.h"

const int minMaxSleepTime = 7;
const int averageSleepTime = 12;


void MinMax(arrayStruct& array_struct) {
    std::this_thread::yield();
    array_struct.min = array_struct.max = array_struct.array[0];
    for (int i = 0; i < array_struct.size; ++i) {
        if (array_struct.array[i] > array_struct.max) {
            array_struct.max = array_struct.array[i];
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(minMaxSleepTime));
        if (array_struct.array[i] < array_struct.min) {
            array_struct.min= array_struct.array[i];
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(minMaxSleepTime));
    }
    std::cout << "Min element: " << array_struct.min<< '\n';
    std::cout << "Max element: " << array_struct.max << '\n';

    return;
}

void Average(arrayStruct& array_struct) {
    for (int i = 0; i < array_struct.size; ++i) {
        array_struct.average += array_struct.array[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(averageSleepTime));
    }
    array_struct.average /= array_struct.size;
    std::cout << "Average: " << array_struct.average << '\n';
    return;
}


int main() {
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;
    std::cout << "Enter elements of array: ";

    int* array = new int[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> array[i];
    }

    arrayStruct array_struct(size, array);

    std::thread min_max_thread(MinMax, std::ref(array_struct));
    std::thread average_thread(Average, std::ref(array_struct));
    min_max_thread.join();
    average_thread.join();

    for (int i = 0; i < size; ++i) {
        if (array_struct.array[i] == array_struct.min || array_struct.array[i] == array_struct.max)
            array_struct.array[i] = array_struct.average;
    }

    for (int i = 0; i < size; ++i) {
        std::cout << array_struct.array[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}