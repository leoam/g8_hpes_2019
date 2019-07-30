// #include <stdio.h>
// #include <stdlib.h>
// #include <malloc.h>
//
// void main()
//     {
//     void *pointer1, *pointer2;
//
//     pointer1 = malloc(100);
//     pointer2 = malloc(101);
//     free(pointer2);
//     free(pointer1);
//     exit(0);
//     }
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  srand(time(NULL));
  int i = 10;
  while(i--) printf("%d\n",rand()%100);
  return 0;
}
