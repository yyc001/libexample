#ifndef _darray_h_
#define _darray_h_

#include <stddef.h>

typedef struct {
    size_t len, unit_size, malloced;
    void *array;
} Darray;

Darray *array_new(size_t unit_size);
Darray *array_from_carray(void *carray, size_t len, size_t unit_size);

void array_delete(Darray *array);
void array_remove(Darray *array, size_t index);

void array_push_back(Darray *array, void *value_ref);
void *array_at(Darray* array, size_t index);


#define ARRAY_FOREACH(type, array, v) \
    for (arr_size_t i = 0; i < array->len; i++) \
        if ((v = *((type*)array_at(array, i))), 1)

#endif