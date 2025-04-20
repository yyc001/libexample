#ifndef _linked_list_h_
#define _linked_list_h_

typedef struct node {
    void *value;
    struct node *prev, *next;
} LinkedListNode;

typedef struct list {
    LinkedListNode *head, *tail;
} LinkedList;

extern LinkedListNode *__linked_list_ref__;

LinkedList *list_new(void);
void list_delete(LinkedList *list);
void list_delete_keepvalue(LinkedList *list);
// void list_remove_node(LinkedList *list, LinkedListNode *node);

void *list_front(LinkedList *list);
void *list_back(LinkedList *list);

void list_push_front(LinkedList *list, void *value);
void *list_pop_front(LinkedList *list);

void list_push_back(LinkedList *list, void *value);
void *list_pop_back(LinkedList *list);

void *list_next_value(LinkedList* list);
void *list_prev_value(LinkedList* list);

#define LIST_FOREACH(list, v) \
    for(v = list_next_value(list); v; v = list_next_value(NULL))

#define LIST_REVEACH(list, v) \
    for(v = list_prev_value(list); v; v = list_prev_value(NULL))

#endif