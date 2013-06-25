XXX: This wasn't tested, my system is x86, not x86_64

#include <stdint.h>             /* uint64_t */

/* rdi, rsi, rdx, rcx, r8, r9 -- 6 arg regs */
struct thread_context {
  /* These must be preserved by callee: */
  uint64_t rbp, rbx, r12to15[4], rsp;
};

void thread_switch(struct thread_context *to, struct thread_context *from);

__asm__(
  "\n .globl thread_switch"
  "\nthread_switch:"
  "\n movl %rbp, 0x00(%rsi)"
  "\n movl %rbx, 0x08(%rsi)"
  "\n movl %r12, 0x10(%rsi)"
  "\n movl %r13, 0x18(%rsi)"
  "\n movl %r14, 0x20(%rsi)"
  "\n movl %r15, 0x28(%rsi)"
  "\n movl %rsp, 0x30(%rsi)"
  "\n"
  "\n movl 0x00(%rdi), %rbp"
  "\n movl 0x08(%rdi), %rbx"
  "\n movl 0x10(%rdi), %r12"
  "\n movl 0x18(%rdi), %r13"
  "\n movl 0x20(%rdi), %r14"
  "\n movl 0x28(%rdi), %r15"
  "\n movl 0x30(%rdi), %rsp"
  "\n retl"
);

struct thread_context *thread_new()
