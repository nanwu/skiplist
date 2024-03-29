#include "skip_list.h"
#include <limits.h>
#include <signal.h>

void print_skiplist(skipList *list) {
  for (int i = SKIPLIST_MAX_LEVEL; i >= 0;  --i) {
    skipListNode *node = list->header->forward[i];
    while (node != list->header) {
      printf("%d\t", node->value);
      node = node->forward[i];
    }
    printf("\n");
  } 
}

void remove_node(skipList *list, int key) {
  skipListNode* cur_node = list->header;
  skipListNode* to_be_removed = NULL;

  int i = SKIPLIST_MAX_LEVEL;
  while (i >= 0) {
    int next_value = cur_node->forward[i]->value;
    if (next_value == key) {
      if (!to_be_removed) to_be_removed = cur_node->forward[i];
      cur_node->forward[i] = cur_node->forward[i]->forward[i];
      i -= 1;
    } else if (next_value > key) {
      i -= 1;
    } else {
      cur_node = cur_node->forward[i]; 
    }
  }
  
  if (to_be_removed) {
    free(to_be_removed);
  } else {
    printf("%d not found.", key);
  }

}

void free_skiplist(skipList *list) {
  skipListNode *cur_node = list->header->forward[0];
  list->header->forward[0] = NULL;

  while (cur_node) {
    skipListNode *tmp = cur_node->forward[0];
    free(cur_node);
    cur_node = tmp;
  }

  free(list);
  printf("Removed the skiplist\n");
}

int search(skipList *list, int arg) {
  skipListNode *cur_node = list->header;
  int level = SKIPLIST_MAX_LEVEL;

  while (level >= 0) {
    int next_value = cur_node->forward[level]->value;
    if (next_value == arg) {
      printf("%d in the skiplist\n", arg);
      return FOUND;
    } else if (next_value > arg) {
      --level;
    } else {
        cur_node = cur_node->forward[level];
    }
  }
  
  printf("%d not in skiplist\n", arg);
  return MISSED;
}

void skiplist_init(skipList *list) {
  skipListNode *header = (skipListNode *)malloc(sizeof(skipListNode));
  header->value = INT_MAX;
  header->level = SKIPLIST_MAX_LEVEL;
  header->forward = (skipListNode **)malloc(sizeof(skipListNode *) * (header->level+1));
  for (int i = 0; i <= SKIPLIST_MAX_LEVEL; ++i) {
    header->forward[i] = header;
  }
  
  list->header = header;
  for (int i = list->header->level; i >= 0; --i) {
    if (list->header->forward[i] == list->header) {
      printf("put forward on level %d\n", i);
    }
  }
  
}


void insert(skipList *list, int new_value) {
  skipListNode *to_be_updated[SKIPLIST_MAX_LEVEL+1];
  skipListNode *cur_node = list->header;
  for (int i = SKIPLIST_MAX_LEVEL; i >= 0; --i) {
    while (cur_node->forward[i]->value <= new_value)
      cur_node = cur_node->forward[i];
    to_be_updated[i] = cur_node;
  } 

  int max_level = insertion_level();
  skipListNode *new_node = (skipListNode *)malloc(sizeof(skipListNode));
  new_node->level = max_level;
  new_node->value = new_value;
  new_node->forward = (skipListNode **)malloc(sizeof(skipListNode *) * (max_level+1));
  for (int level = 0; level <= max_level; level++) {
     skipListNode *forward = to_be_updated[level]->forward[level];
     to_be_updated[level]->forward[level] = new_node;
     new_node->forward[level] = forward;
  } 
}

int insertion_level() {
  int level = 1;
  while (rand()%2 && level < SKIPLIST_MAX_LEVEL)
    level++;
  return level;
}
