#include "threads.h"
#include <stdlib.h>             /* abort */
#include <string.h>             /* memset */

void thread_switch(struct thread_context *to, struct thread_context *from);

__asm__(
  "\n .globl thread_switch"
  "\nthread_switch:"
  "\n movl 0x04(%esp), %ecx"    /* to */
  "\n movl 0x08(%esp), %eax"    /* from */
  "\n movl %ebp, 0x00(%eax)"    /* regs into 'from' */
  "\n movl %ebx, 0x04(%eax)"
  "\n movl %esi, 0x08(%eax)"
  "\n movl %edi, 0x0C(%eax)"
  "\n movl %esp, 0x10(%eax)"
  "\n"
  "\n movl 0x00(%ecx), %ebp"    /* regs from 'to' */
  "\n movl 0x04(%ecx), %ebx"
  "\n movl 0x08(%ecx), %esi"
  "\n movl 0x0C(%ecx), %edi"
  "\n movl 0x10(%ecx), %esp"
  "\n retl"
);

static void push(uint32_t *esp, uint32_t val)
{
  *esp -= 4;
  *(uint32_t*)*esp = (uint32_t)val;
}

static void start_thread(void (*func)(void *arg), void *arg)
{
  func(arg);
  abort();
}

void thread_new(
    struct thread_context *new,
    struct thread_context *from,
    void *stack_top,
    void (*func)(void *), void *arg)
{
  memset(new, 0, sizeof *new);
  new->esp = (uint32_t)stack_top;
  push(&new->esp, (uint32_t)arg);
  push(&new->esp, (uint32_t)func);
  push(&new->esp, (uint32_t)NULL); /* ret-addr: We should never jump here */
  push(&new->esp, (uint32_t)&start_thread); /* Jump-to */
  thread_switch(new, from);
}
