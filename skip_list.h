#include <stdio.h>
#include <stdlib.h>

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#define SKIPLIST_MAX_LEVEL 10
#define MISSED -1
#define FOUND 0

typedef struct skipListNode {
  size_t level;
  int value;
  struct skipListNode **forward;
} skipListNode;

typedef struct skipList {
  skipListNode *header;
} skipList;


int search(skipList *list, int taget);
void print_skiplist(skipList *list); 
void insert(skipList *list, int new_val);
void skiplist_init(skipList *list);

#endif
