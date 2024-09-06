/*
 * This file contains a simple implementation of a singly-linked list.  See
 * the documentation below for more information on the individual functions in
 * this implementation.  You should not modify anything in this file.
 */

#include <stdlib.h>
#include <assert.h>

#include "list.h"

/*
 * This structure is used to represent a single link in a singly-linked list.
 * It is not defined in list.h, so it is not visible to the user.
 */
struct link {
  void* val;
  struct link* next;
};

/*
 * This structure is used to represent an entire singly-linked list.  Note that
 * we're keeping track of just the head of the list here, for simplicity.
 */
struct list {
  struct link* head;
};

/*
 * This function allocates and initializes a new, empty linked list and
 * returns a pointer to it.
 */
struct list* list_create() {
  struct list* list = malloc(sizeof(struct list));
  list->head = NULL;
  return list;
}

/*
 * This function frees the memory associated with a linked list.  Freeing any
 * memory associated with values still stored in the list is the responsibility
 * of the caller.
 *
 * Params:
 *   list - the linked list to be destroyed.  May not be NULL.
 */
void list_free(struct list* list) {
  assert(list);

  /*
   * Free all individual links.
   */
  struct link* next, * curr = list->head;
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }

  free(list);
}

/*
 * This function inserts a new value into a given linked list.  The new element
 * is always inserted as the head of the list.
 *
 * Params:
 *   list - the linked list into which to insert an element.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void list_insert(struct list* list, void* val) {
  assert(list);

  /*
   * Create new link and insert at head.
   */
  struct link* link = malloc(sizeof(struct link));
  link->val = val;
  link->next = list->head;
  list->head = link;
}

/*
 * This function returns 1 if the list is empty and 0 otherwise.
 */
int list_isempty(struct list* list) {
  assert(list);
  if (list->head) {
    return 0;
  } else {
    return 1;
  }
}

/*
 * This function returns the value stored at the head of a given linked list
 * or NULL if the list is empty.
 */
void* list_head(struct list* list) {
  assert(list);

  if (list->head) {
    return list->head->val;
  } else {
    return NULL;
  }
}

/*
 * This function removes the value stored at the head of a given linked list.
 * If the list is empty, this function is a noop.
 */
void list_remove_head(struct list* list) {
  assert(list);

  if (list->head) {
    struct link* old_head = list->head;
    list->head = old_head->next;
    free(old_head);
  }
}
