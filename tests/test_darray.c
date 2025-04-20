#include <stdio.h>
#include <stdlib.h>
#include <darray.h>
#include "testlib.h"


void test_array_from_carray() {
    int carray[] = {1, 2, 3};
    Darray *arr = array_from_carray(carray, 3, sizeof(int));

    TEST_ASSERT(arr != NULL);
    TEST_ASSERT(arr->len == 3);
    TEST_ASSERT(arr->unit_size == sizeof(int));
    TEST_ASSERT(*(int *)array_at(arr, 0) == 1);
    TEST_ASSERT(*(int *)array_at(arr, 1) == 2);
    TEST_ASSERT(*(int *)array_at(arr, 2) == 3);

    array_delete(arr);
}

void test_array_remove() {
    Darray *arr = array_new(sizeof(int));
    int val1 = 10, val2 = 20, val3 = 30;
    array_push_back(arr, &val1);
    array_push_back(arr, &val2);
    array_push_back(arr, &val3);

    TEST_ASSERT(arr->len == 3);

    array_remove(arr, 1);  // Remove element at index 1 (value 20)

    TEST_ASSERT(arr->len == 2);
    TEST_ASSERT(*(int *)array_at(arr, 0) == 10);  // First element should be 10
    TEST_ASSERT(*(int *)array_at(arr, 1) == 30);  // Second element should be 30

    array_delete(arr);
}

void test_array_push_back() {
    Darray *arr = array_new(sizeof(int));
    int val1 = 10, val2 = 20;

    array_push_back(arr, &val1);
    TEST_ASSERT(arr->len == 1);
    TEST_ASSERT(*(int *)array_at(arr, 0) == 10);

    array_push_back(arr, &val2);
    TEST_ASSERT(arr->len == 2);
    TEST_ASSERT(*(int *)array_at(arr, 1) == 20);

    array_delete(arr);
}

void test_array_at() {
    Darray *arr = array_new(sizeof(int));
    int val1 = 10, val2 = 20;

    array_push_back(arr, &val1);
    array_push_back(arr, &val2);

    TEST_ASSERT(*(int *)array_at(arr, 0) == 10);  // First element should be 10
    TEST_ASSERT(*(int *)array_at(arr, 1) == 20);  // Second element should be 20

    array_delete(arr);
}



void all() {
    RUN_TEST(test_array_from_carray);
    RUN_TEST(test_array_push_back);
    RUN_TEST(test_array_remove);
    RUN_TEST(test_array_at);
}

RUN_TEST_BUNDLE(all)
