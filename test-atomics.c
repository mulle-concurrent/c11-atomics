#include <stdio.h>

// Test C11 atomic detection
#ifndef HAVE_C11_STDATOMIC
# ifdef __clang__
#  if __has_include(<stdatomic.h>)
#    define HAVE_C11_STDATOMIC 1
#  endif
# else
#  if __STDC_VERSION__ >= 201112L && ! defined( __STDC_NO_ATOMICS__)
#   define HAVE_C11_STDATOMIC  1
#  endif
# endif
#endif

#if HAVE_C11_STDATOMIC
# include <stdatomic.h>

int main(void)
{
    printf("SUCCESS: C11 atomics are supported\n");
    printf("  __has_include: yes\n");
    printf("  <stdatomic.h>: found\n");
    
    // Test basic atomic operations
    atomic_int counter = ATOMIC_VAR_INIT(0);
    atomic_fetch_add(&counter, 1);
    int value = atomic_load(&counter);
    
    printf("  atomic operations: working (value=%d)\n", value);
    
    return 0;
}

#else

int main(void)
{
    fprintf(stderr, "FAIL: C11 atomics NOT supported\n");
    
#ifdef __clang__
    fprintf(stderr, "  Compiler: clang\n");
#elif defined(__GNUC__)
    fprintf(stderr, "  Compiler: gcc\n");
#elif defined(_MSC_VER)
    fprintf(stderr, "  Compiler: msvc\n");
#else
    fprintf(stderr, "  Compiler: unknown\n");
#endif

#ifdef __STDC_VERSION__
    fprintf(stderr, "  __STDC_VERSION__: %ld\n", __STDC_VERSION__);
#else
    fprintf(stderr, "  __STDC_VERSION__: not defined\n");
#endif

#ifdef __STDC_NO_ATOMICS__
    fprintf(stderr, "  __STDC_NO_ATOMICS__: defined\n");
#else
    fprintf(stderr, "  __STDC_NO_ATOMICS__: not defined\n");
#endif

    return 1;
}

#endif
