#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

#define STACK_SIZE 0x10000

static struct thread_context main_thread, other_thread;

void other_thread_func(void *dummy)
{
    printf("In other thread1!\n");
    thread_switch(&main_thread, &other_thread);
    printf("In other thread2!\n");
    thread_switch(&main_thread, &other_thread);
    printf("In other thread3!\n");
    thread_switch(&main_thread, &other_thread);
    printf("OOPS!\n");
}

int main() {
    void *other_thread_stack = malloc(STACK_SIZE);
    thread_new(&other_thread, &main_thread, (char *)other_thread_stack+STACK_SIZE,
               &other_thread_func, NULL);
    printf("In main thread1!\n");
    thread_switch(&other_thread, &main_thread);
    printf("In main thread2!\n");
    thread_switch(&other_thread, &main_thread);
    printf("DONE!\n");
    free(other_thread_stack);
    return 0;
}
