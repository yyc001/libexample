#include <darray.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Darray *array_new(size_t unit_size) {
    Darray *array = (Darray*) calloc(1, sizeof(Darray));
    array->array = calloc(1, unit_size);
    array->len = 0;
    array->unit_size = unit_size;
    array->malloced = 1;
    return array;
}


Darray *array_from_carray(void *carray, size_t len, size_t unit_size) {
    Darray *array = (Darray*) calloc(1, sizeof(Darray));
    array->array = calloc(unit_size, len);
    array->len = len;
    array->unit_size = unit_size;
    array->malloced = len;
    memcpy(array->array, carray, unit_size * len);
    return array;
}


void array_delete(Darray *array) {
    free(array->array);
    free(array);
}


void array_remove(Darray *array, size_t index) {
    assert(index < array->len);
    for(size_t i = index + 1; i < array->len; i++) {
        memcpy(array_at(array, i-1), array_at(array, i), array->unit_size);
    }
    array->len--;
}

void array_push_back(Darray *array, void *value_ref) {
    if(array->len == array->malloced) {
        void *narray = calloc(array->malloced * 2, array->unit_size);
        memcpy(narray, array->array, array->malloced * array->unit_size);
        free(array->array);
        array->array = narray;
        array->malloced *= 2;
    }
    array->len++;
    memcpy(array_at(array, array->len - 1), value_ref, array->unit_size);
}

void *array_at(Darray* array, size_t index) {
    assert(index < array->len);
    return array->array + index * array->unit_size;
}

