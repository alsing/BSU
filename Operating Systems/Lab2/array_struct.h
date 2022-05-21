#ifndef LAB2_ARRAY_STRUCT_H
#define LAB2_ARRAY_STRUCT_H

struct arrayStruct {
    arrayStruct(int size, int *array) : size(size), array(array) {}

    int size;
    int* array;
    int min;
    int max;
    int average;
};

#endif //LAB2_ARRAY_STRUCT_H
