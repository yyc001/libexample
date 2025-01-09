#include <stdio.h>
#include <stdlib.h>
#include "../src/linked_list.h"
#include "testlib.h"
// Helper function to check list size
int list_size(LinkedList *list) {
    int size = 0;
    int *value;
    LIST_FOREACH(list, value) {
        size++;
    }
    return size;
}

void test_create_and_push_back() {
    LinkedList *list = list_new();
    int a = 10, b = 20, c = 30;
    
    list_push_back(list, &a);
    list_push_back(list, &b);
    list_push_back(list, &c);

    TEST_ASSERT(list_size(list) == 3);  // Ensure 3 elements are in the list

    int *value;
    LIST_FOREACH(list, value) {
        if (*value == 10 || *value == 20 || *value == 30) continue;
        TEST_ASSERT(0);  // Ensure only expected values are in the list
    }

    list_delete_keepvalue(list);  // Clean up
}

void test_pop_front() {
    LinkedList *list = list_new();
    int a = 10, b = 20, c = 30;
    
    list_push_back(list, &a);
    list_push_back(list, &b);
    list_push_back(list, &c);

    int *front_value = list_pop_front(list);
    TEST_ASSERT(*front_value == 10);  // Ensure front value is 10

    TEST_ASSERT(list_size(list) == 2);  // Ensure list size is 2 after pop

    list_delete_keepvalue(list);  // Clean up
}

void test_pop_back() {
    LinkedList *list = list_new();
    int a = 10, b = 20, c = 30;
    
    list_push_back(list, &a);
    list_push_back(list, &b);
    list_push_back(list, &c);

    int *back_value = list_pop_back(list);
    TEST_ASSERT(*back_value == 30);  // Ensure back value is 30

    TEST_ASSERT(list_size(list) == 2);  // Ensure list size is 2 after pop

    list_delete_keepvalue(list);  // Clean up
}

void test_push_front() {
    LinkedList *list = list_new();
    int a = 10, b = 20, c = 30;
    
    list_push_front(list, &a);
    list_push_front(list, &b);
    list_push_front(list, &c);

    TEST_ASSERT(list_size(list) == 3);  // Ensure 3 elements are in the list

    int *value;
    LIST_FOREACH(list, value) {
        if (*value == 30 || *value == 20 || *value == 10) continue;
        TEST_ASSERT(0);  // Ensure only expected values are in the list
    }

    list_delete_keepvalue(list);  // Clean up
}

void test_reverse_iteration() {
    LinkedList *list = list_new();
    int a = 10, b = 20, c = 30;

    list_push_back(list, &a);
    list_push_back(list, &b);
    list_push_back(list, &c);

    int expected[] = {30, 20, 10};
    int i = 0;
    int *value;
    LIST_REVEACH(list, value) {
        TEST_ASSERT(*value == expected[i++]);  // Ensure values are in reverse order
    }

    list_delete_keepvalue(list);  // Clean up
}

void all() {
    // Run tests
    RUN_TEST(test_create_and_push_back);
    RUN_TEST(test_pop_front);
    RUN_TEST(test_pop_back);
    RUN_TEST(test_push_front);
    RUN_TEST(test_reverse_iteration);
}


RUN_TEST_BUNDLE(all)
