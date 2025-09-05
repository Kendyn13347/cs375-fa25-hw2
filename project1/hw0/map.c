#include <stdio.h>
#include <stdlib.h>

/* A statically allocated variable (in .bss / .data) */
int foo;
volatile int stuff = 7;      /* pre-initialized => in .data */

/* --- forward decl --- */
int recur(int i);

int main(int argc, char *argv[]) {
    /* A stack-allocated variable (lives in the stack frame of main) */
    volatile int i = 0;

    /* Dynamically allocate some stuff (lives on the heap) */
    volatile char *buf1 = malloc(100);
    volatile char *buf2 = malloc(100);

    /* Print addresses formatted like the example */
    printf("_main @ %p\n",  (void *)&main);   /* code address of main  */
    printf("recur @ %p\n",  (void *)&recur);  /* code address of recur */
    printf("_main stack: %p\n", (void *)&i);  /* address of main's stack var */
    printf("static data: %p\n", (void *)&stuff);  /* address in .data/.bss   */
    printf("Heap: malloc 1: %p\n", (void *)buf1); /* heap blocks              */
    printf("Heap: malloc 2: %p\n", (void *)buf2);

    recur(3);

    /* keep or free — not required for the demo
       free((void*)buf2); free((void*)buf1); */
    return 0;
}

/* Recursively print the address of a stack variable at each depth */
int recur(int n) {
    volatile int x = 0;  /* each call gets its own copy on the stack */
    printf("recur call %d: stack@ %p\n", n, (void *)&x);
    if (n > 0) {
        recur(n - 1);
    }
    return 0;
}
