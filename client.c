#include "skip_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FUNC_TYPE1 1
#define FUNC_TYPE2 2
#define FUNC_TYPE3 3

typedef struct {
  char *command;
  int func_type;
  union {
    int (*func1) (skipList*, int);
    void (*func2) (skipList*, int);
    void (*func3) (skipList*);
  } skipList_func;
} entry_t;

entry_t table[] = {{"put", 2, .skipList_func.func2 = insert}, 
                   {"get", 1, .skipList_func.func1 = search},
                   {"delete", 2, .skipList_func.func2 = remove_node},
                   {"print", 3, .skipList_func.func3 = print_skiplist}};

void parse(skipList *list, char *cmd_line) {
  char *cmd = strtok(cmd_line, " \n");
  if (cmd == NULL) return;
  char *key = strtok(NULL, " ");

  int i = sizeof(table)/sizeof(entry_t) - 1;
  while (i >= 0) {
    if (!strcasecmp(table[i].command, cmd)) {
      int arg;
      if (key)
        sscanf(key, "%d", &arg);

      if (table[i].func_type == FUNC_TYPE1) {
        table[i].skipList_func.func1(list, arg);
      } else if (table[i].func_type == FUNC_TYPE2) {
        table[i].skipList_func.func2(list, arg);
      } else if (table[i].func_type == FUNC_TYPE3) {
        table[i].skipList_func.func3(list);
      }

      return;
    }
    --i;
  }
}


int main() {
  int arr[] = {1, 2, 3, 4, 5};
  skipList *list = (skipList *)malloc(sizeof(skipList));
  skiplist_init(list);

  printf("Inserting: ----------------\n");
  for (int i = 0; i < sizeof(arr)/sizeof(int); ++i) {
    insert(list, arr[i]); 
  }
  
  while (1) {
    printf("> ");
    char cmd[200];
    parse(list, fgets(cmd, 200, stdin));
  }
}
