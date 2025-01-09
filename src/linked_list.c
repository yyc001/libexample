#include "linked_list.h"
#include <stdlib.h>
#include <assert.h>

LinkedListNode *__linked_list_ref__;

LinkedList *list_new() {
    LinkedList *list = (LinkedList*) calloc(1, sizeof(LinkedList));
    list->head = list->tail = NULL;
    return list;
}


void list_delete_keepvalue(LinkedList *list) {
    for(LinkedListNode *cur = list->head; cur != NULL; cur = cur->next) {
        if(cur == __linked_list_ref__) {
            __linked_list_ref__ = NULL;
        }
        if(cur->prev) {
            free(cur->prev);
        }
    }
    if(list->tail) {
        free(list->tail);
    }
    free(list);
}


void list_delete(LinkedList* list) {
    for(LinkedListNode *cur = list->head; cur != NULL; cur = cur->next) {
        if(cur->value) {
            free(cur->value);
        }
    }
    list_delete_keepvalue(list);
}


void list_remove_node(LinkedList* list, LinkedListNode *node) {
    if(node == list->head) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;    
    }
    if(node == list->tail) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }
    free(node);
}


void *list_front(LinkedList* list) {
    return list->head != NULL ? list->head->value : NULL;
}

void *list_back(LinkedList* list) {
    return list->tail != NULL ? list->tail->value : NULL;
}

// static inline bool list_empty(LinkedList * list) {
//     assert((list->head != NULL) == (list->tail != NULL));
//     return list->head != NULL;
// } 

void list_push_front(LinkedList* list, void *value) {
    assert(value != NULL);
    assert((list->head == NULL) == (list->tail == NULL));
    LinkedListNode *node = (LinkedListNode*) calloc(1, sizeof(LinkedListNode));
    
    if(list->head) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }
    node->prev = NULL;
    node->next = list->head;
    node->value = value;
    list->head = node;
}


void *list_pop_front(LinkedList* list) {
    assert(list->head != NULL);
    
    LinkedListNode *node = list->head;
    void *value = node->value;
    list_remove_node(list, node);
    return value;
}


void list_push_back(LinkedList* list, void *value) {
    assert(value != NULL);
    assert((list->head == NULL) == (list->tail == NULL));
    LinkedListNode *node = (LinkedListNode*) calloc(1, sizeof(LinkedListNode));
    
    if(list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    node->prev = list->tail;
    node->next = NULL;
    node->value = value;
    list->tail = node;
}
void *list_pop_back(LinkedList* list) {
    assert(list->tail != NULL);
    
    LinkedListNode *node = list->tail;
    void *value = node->value;
    list_remove_node(list, node);
    return value;
}

void *list_next_value(LinkedList* list) {
    if(list != NULL) {
        __linked_list_ref__ = list->head;
    } else {
        __linked_list_ref__ = __linked_list_ref__->next;
    }
    return __linked_list_ref__ != NULL ? __linked_list_ref__->value : NULL;
}


void *list_prev_value(LinkedList* list) {
    if(list != NULL) {
        __linked_list_ref__ = list->tail;
    } else {
        __linked_list_ref__ = __linked_list_ref__->prev;
    }
    return __linked_list_ref__ != NULL ? __linked_list_ref__->value : NULL;
}