struct thread_context {
    /* These must be preserved by callee: */
    uint64_t rbp, rbx, r12, r13, r14, r15, rsp;
};
