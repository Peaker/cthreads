#if defined(__LP64__) || defined(__x86_64__) || defined(__amd64__)
#include "threads64_private.h"
#elif defined(__ILP32__) || defined(i386) || defined(__i386__)
#include "threads32_private.h"
#else
#error "Unsupported architecture!"
#endif
