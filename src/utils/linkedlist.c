#include <stdlib.h>
#include <string.h>
#include <utils/linkedlist.h>
#include <utils/types.h>
#include <utils/hmalloc.h>

LinkedList linkedlist_init() {
	LinkedList out = {
		.head = NULL,
		.curr = NULL,
		.tail = NULL,
		.index = 0,
		.len = 0,
	};
	return out;
}

void * linkedlist_get(LinkedList *self, usize index) {
	if (index >= self->len)
		return NULL;
	const bool curr_is_left = self->index <= index;
	const usize
		len_to_head = index,
		len_to_curr = curr_is_left
			? index - self->index
			: self->index - index,
		len_to_tail = self->index - index;
	Node *node;
	if (len_to_head > len_to_curr && len_to_head > len_to_tail) {
		for (
			node = linkedlist_begin(self);
			node != NULL && self->index < index;
			node = linkedlist_next(self)
		);
	} else if (len_to_tail > len_to_curr && len_to_tail > len_to_head) {
		for (
			node = linkedlist_end(self);
			node != NULL && self->index > index;
			node = linkedlist_prev(self)
		);
	} else {
		for (
			node = self->curr;
			node != NULL && curr_is_left
				? self->index < index
				: self->index > index;
			node = curr_is_left 
				? linkedlist_next(self)
				: linkedlist_prev(self)
		);
	}
	return node != NULL ? node->value : NULL;
}

void linkedlist_insert(LinkedList *self, usize index, void *value) {
	Node *next_node = linkedlist_get(self, index);
	if (next_node == NULL)
		return;
	Node *node = hmalloc(sizeof(Node));
	node->prev = next_node->prev;
	node->next = next_node;
	node->value = value;
	node->prev->next = node;
	node->next->prev = node;
	++self->len;
	++self->index;
}

void * linkedlist_replace(LinkedList *self, usize index, void *value) {
	Node *node = linkedlist_get(self, index);
	if (node == NULL)
		return NULL;
	void *old_value = node->value;
	node->value = value;
	return old_value;
}

inline usize linkedlist_length(LinkedList *self) {
	return self->len;
}

inline void linkedlist_push(LinkedList *self, void *value) {
	if (linkedlist_is_empty(self))
		return;
	linkedlist_insert(self, self->len, value);
}

void * linkedlist_remove(LinkedList *self, usize index) {
	Node *node = linkedlist_get(self, index);
	if (node == NULL)
		return NULL;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	void *value = node->value;
	free(node);
	return value;
}

inline void * linkedlist_pop(LinkedList *self) {
	if (linkedlist_is_empty(self))
		return NULL;
	return linkedlist_remove(self, self->len - 1);
}

inline void * linkedlist_begin(LinkedList *self) {
	return (self->curr = self->head);
}

inline void * linkedlist_end(LinkedList *self) {
	self->index = self->len - 1;
	return (self->curr = self->tail);
}

void * linkedlist_prev(LinkedList *self) {
	if (self->curr != NULL) {
		self->curr = self->curr->prev;
		self->index += 1;
	}
	return self->curr != NULL ? self->curr->value : NULL;
}

void * linkedlist_next(LinkedList *self) {
	if (self->curr != NULL) {
		self->curr = self->curr->next;
		self->index += 1;
	}
	return self->curr != NULL ? self->curr->value : NULL;
}

inline bool linkedlist_is_empty(LinkedList *self) {
	return self->len == 0;
}

usize linkedlist_deinit(LinkedList *self, void ***values) {
	const usize len = self->len;
	*values = hcalloc(self->len, sizeof(void *));
	while (self->head != NULL) 
		*values[len - self->len] = linkedlist_remove(self, 0);
	return len;
}
