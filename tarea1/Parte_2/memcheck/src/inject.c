#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

int malloc_counter = 0;
int free_counter = 0;

static void* (*real_malloc)(size_t)=NULL;
static void (*real_free)(void *) = NULL;

static void init(int argc, char **argv, char **envp) {
    malloc_counter = 0;
    free_counter = 0;

    real_malloc = dlsym(RTLD_NEXT, "malloc");
    real_free = dlsym(RTLD_NEXT, "free");
}

static void fini(void) {
    fprintf(stderr,"\nAnalysis finished!\n");
    fprintf(stderr,"Memory allocations: %d\n", malloc_counter);
    fprintf(stderr,"Memory free: %d\n", free_counter);
    fprintf(stderr,"Total memory leaks found: %d \n", malloc_counter - free_counter);
}

__attribute__((section(".init_array"), used)) static typeof(init) *init_p = init;
__attribute__((section(".fini_array"), used)) static typeof(fini) *fini_p = fini;

void *malloc(size_t size){
    malloc_counter ++;

    void *p = NULL;
    p = real_malloc(size);
    return p;
  }

void free(void *ptr){
  free_counter ++;
  real_free(ptr);
}
