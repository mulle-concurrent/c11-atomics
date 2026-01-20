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
    atomic_int counter = 0;  // Direct initialization (ATOMIC_VAR_INIT is deprecated)
    atomic_fetch_add(&counter, 1);
    int value = atomic_load(&counter);
    
    printf("  atomic operations: working (value=%d)\n", value);
    
    return 0;
}

#else

int main(void)
{
    printf("WARNING: C11 atomics NOT detected\n");
    
#ifdef __clang__
    printf("  Compiler: clang\n");
#elif defined(__GNUC__)
    printf("  Compiler: gcc\n");
#elif defined(_MSC_VER)
    printf("  Compiler: msvc\n");
#else
    printf("  Compiler: unknown\n");
#endif

#ifdef __STDC_VERSION__
    printf("  __STDC_VERSION__: %ld\n", __STDC_VERSION__);
#else
    printf("  __STDC_VERSION__: not defined\n");
#endif

#ifdef __STDC_NO_ATOMICS__
    printf("  __STDC_NO_ATOMICS__: defined\n");
#else
    printf("  __STDC_NO_ATOMICS__: not defined\n");
#endif

    return 0;
}

#endif
