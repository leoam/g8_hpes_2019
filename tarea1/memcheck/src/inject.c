//
// // Note that free(NULL) is valid C:
// // https://stackoverflow.com/questions/1938735/does-freeptr-where-ptr-is-null-corrupt-memory/1938758
//
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
//
// static void *(*real_malloc)(size_t) = NULL;
// static void (*real_free)(void *) = NULL;
//
// void *malloc(size_t size){
//     void *retval = real_malloc(size);
//     return retval;
//   }
//
// void free(void *ptr){
//   real_free(ptr);
// }




int rand(){
    return 42; //the most random number in the universe
}

// #define _GNU_SOURCE
// #include <dlfcn.h>
// #include <stdio.h>
//
// void* malloc(size_t size)
// {
//     static void* (*real_malloc)(size_t) = NULL;
//     if (!real_malloc)
//         real_malloc = dlsym(RTLD_NEXT, "malloc");
//
//     void *p = real_malloc(size);
//     // fprintf(stderr, "malloc(%d) = %p\n", size, p);
//     return p;
// }
//
// void free(void *p)
// {
//     void (*libc_free)(void*) = dlsym(RTLD_NEXT, "free");
//     // printf("free\n");
//     libc_free(p);
// }
