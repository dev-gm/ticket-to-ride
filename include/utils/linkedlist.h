#ifndef UTILS_LINKEDLIST_H

#define UTILS_LINKEDLIST_H

#include "types.h"
#include <stdbool.h>

typedef struct Node {
	struct Node *prev, *next;
	void *value;
} Node;

typedef struct {
	Node *head, *curr, *tail;
	usize index, len;
} LinkedList;

LinkedList linkedlist_init();

void * linkedlist_get(LinkedList *self, usize index);

void linkedlist_insert(LinkedList *self, usize index, void *value);

void * linkedlist_replace(LinkedList *self, usize index, void *value);

usize linkedlist_length(LinkedList *self);

void linkedlist_push(LinkedList *self, void *value);

void * linkedlist_remove(LinkedList *self, usize index);

void * linkedlist_pop(LinkedList *self);

// returns value
void * linkedlist_begin(LinkedList *self);

// returns value
void * linkedlist_end(LinkedList *self);

// returns value
void * linkedlist_prev(LinkedList *self);

// returns value
void * linkedlist_next(LinkedList *self);

bool linkedlist_is_empty(LinkedList *self);

usize linkedlist_deinit(LinkedList *self, void ***values);

#endif
