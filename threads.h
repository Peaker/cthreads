#ifndef __THREADS_H_
#define __THREADS_H_

#include <stdint.h>             /* uint32_t */

/* EAX,ECX,EDX caller-saved */
/* EBX,ESI,EDI,EBP callee-saved */
typedef struct thread_context thread_context;

void thread_switch(struct thread_context *to, struct thread_context *from);

void thread_new(
    struct thread_context *new,
    struct thread_context *from,
    void *stack_top,
    void (*func)(void *), void *arg);

#include "threads_private.h"

#endif
