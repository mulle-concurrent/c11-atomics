#include <stdatomic.h>
#include <stdio.h>

int main(void)
{
    printf("Testing direct <stdatomic.h> include...\n");
    
    // Test basic atomic operations
    atomic_int counter = 0;  // Direct initialization (ATOMIC_VAR_INIT is deprecated)
    
    // Test compare-and-swap
    int expected = 0;
    int desired = 100;
    
    if (atomic_compare_exchange_strong(&counter, &expected, desired)) {
        printf("SUCCESS: CAS succeeded (0 -> 100)\n");
    } else {
        printf("FAIL: CAS failed\n");
        return 1;
    }
    
    int value = atomic_load(&counter);
    printf("Final value: %d\n", value);
    
    if (value == 100) {
        printf("SUCCESS: Atomics work correctly\n");
        return 0;
    } else {
        printf("FAIL: Unexpected value %d\n", value);
        return 1;
    }
}
