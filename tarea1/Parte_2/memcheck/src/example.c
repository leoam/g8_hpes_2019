#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(int argc, char **argv){
  void *pointer1, *pointer2, *pointer3;

  pointer1 = malloc(sizeof(int));
  pointer2 = malloc(sizeof(int));
  pointer3 = malloc(sizeof(int));
  free(pointer2);
  free(pointer1);
  return 0;
}
