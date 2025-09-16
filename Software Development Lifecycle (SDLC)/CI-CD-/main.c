#include <stdio.h>
#include <assert.h>

// Simple function to add two numbers
int add(int a, int b) {
    return a + b;
}

int main() {
    printf("=== Starting Program ===\n");
    printf("\n== Running Test Cases ===\n");
    
    // Test Case 1
    printf("Test 1: add(2, 3) -> expected 5\n");
    assert(add(2, 3) == 5);
    printf("√ Passed\n");
    
    // Test Case 2
    printf("Test 2: add(-1, 1) -> expected 0\n");
    assert(add(-1, 1) == 0);
    printf("√ Passed\n");
    
    // Test Case 3
    printf("Test 3: add(0, 0) -> expected 0\n");
    assert(add(0, 0) == 0);
    printf("√ Passed\n");

    printf("\n== All Tests Passed Successfully ===\n");
    return 0;
}