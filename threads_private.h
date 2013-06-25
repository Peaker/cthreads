struct thread_context {
    /* These must be preserved by callee: */
    uint32_t ebp, ebx, esi, edi, esp;
};
