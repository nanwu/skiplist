#include "skip_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  skipList *list = (skipList *)malloc(sizeof(skipList));
  skiplist_init(list);

  printf("Inserting: ----------------\n");
  for (int i = 0; i < sizeof(arr)/sizeof(int); ++i) {
    insert(list, arr[i]); 
  }
  
  print_skiplist(list);

  if (search(list, 8) == FOUND) {
    printf("found 3 in the skiplist\n");
  } else {
    printf("3 is missed\n");
  }
  
}
