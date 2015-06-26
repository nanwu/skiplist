#include "skip_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *command;
  void (*func) (skipList*, int);
} entry_t;

entry_t table[] = {{"put", insert}, 
                   {"get", search}};

void parse(skipList *list, char *cmd_line) {
  char *cmd = strtok_r(cmd_line, " ");
  if (cmd == NULL) return;
  char *key = strtok_r(NULL, " ");
  if (key == NULL) return;
  
  int i = sizeof(table)/sizeof(entry_t);
  while (--i) {
    if (!strcasecmp(table[i].command, cmd)) {
      int arg;
      sscanf(key, "%d", &arg);
      table[i].func(list, arg);
      return;
    }
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
    char cmd[200];
    parse(list, fgets(cmd, 200, stdin));
  }
}
