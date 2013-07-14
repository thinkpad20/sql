#ifndef __LIST_H_
#define __LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

typedef struct listnode {
    void *data;
    struct listnode *next, *prev;
} ListNode;

typedef struct List {
    size_t size;
    ListNode *front, *back;
    void (*del) (void *);
    pthread_mutex_t lock;
    char *(*toString) (void *);
    int (*compare)(void *, void *);
    const char *name;
} List;


void list_init(struct List *, void (*del) (void *));
void list_destroy(struct List *l);

void *list_findByInt(struct List *l, int (*toInt) (void *), int i);
void *list_findByString(struct List *l, void (*toString) (char *,void *), const char *str);
void *list_findByPointer(struct List *l, void *ptr);

bool list_removeByInt(struct List *l, int (*toInt) (void *), int i);
bool list_removeByString(struct List *l, void (*toString) (char *,void *), const char *str);
void *list_removeByPointer(struct List *list, void *ptr);
void *list_removeNode(struct List *list, struct listnode *node);
void list_removeNodeDelete(struct List *list, struct listnode *node);
void list_removeByPointerFree(List *list, void *ptr);

void list_print(struct List *l);
void list_printCustom(struct List *l, char * (*toString) (void *), bool freeAfter);

ListNode *listNode_init(void *data, ListNode *next, ListNode *prev);

/* Threadsafe */
bool list_addBack(struct List *l, void *data);
void *list_removeBack(struct List *l);
bool list_addFront(struct List *l, void *data);
bool list_addInOrder(struct List *l, void *data);
void *list_removeFront(struct List *l);
void list_addBetween(List *list, void *data, ListNode *prev, ListNode *next);

#endif
