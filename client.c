#include "skip_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define FUNC_TYPE1 1
#define FUNC_TYPE2 2
#define FUNC_TYPE3 3

#define OUT_OF_LOOP -1
#define CONTINUE_LOOP 0

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
                   {"print", 3, .skipList_func.func3 = print_skiplist},
                   {"quit", 3, .skipList_func.func3 = free_skiplist}};

int parse(skipList *list, char *cmd_line) {
  char *cmd = strtok(cmd_line, " \n");
  if (cmd == NULL) return 0;
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
      
      if (!strcasecmp("quit", cmd)) {
        return OUT_OF_LOOP;
      } else {
        return CONTINUE_LOOP;
      }
    }
    --i;
  }
}

skipList *list;

void sigint_handler(int signo) {
  if (signo == SIGINT) {
    printf("\nreceive SIGINT signal\n");
    if (list) {      // check if the skiplist is freed or not
      free_skiplist(list);
    }
    exit(0);
  }  

}

int main() {
  
  int arr[] = {1, 2, 3, 4, 5};
  list = (skipList *)malloc(sizeof(skipList));
  skiplist_init(list);

  printf("Inserting: ----------------\n");
  for (int i = 0; i < sizeof(arr)/sizeof(int); ++i) {
    insert(list, arr[i]); 
  }

  if (signal(SIGINT, sigint_handler) == SIG_ERR)
    printf("can't handle the signal\n");

  while (1) {
    printf("> ");
    char cmd[200];
    if (OUT_OF_LOOP == parse(list, fgets(cmd, 200, stdin))) break;
  }

  return 0;
}
