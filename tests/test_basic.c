/**
 * test_basic.c - Basic unit tests
 */

#include <stdio.h>
#include <assert.h>
#include "example.h"

void test_add_numbers() {
    printf("Testing add_numbers... ");
    assert(add_numbers(2, 3) == 5);
    assert(add_numbers(-1, 1) == 0);
    assert(add_numbers(0, 0) == 0);
    printf("PASS\n");
}

void test_print_example() {
    printf("Testing print_example... ");
    ExampleStruct example = {1, 42.5};
    print_example(&example);
    printf("PASS (manual verification required)\n");
}

int main() {
    printf("Running tests...\n");
    
    test_add_numbers();
    test_print_example();
    
    printf("All tests completed!\n");
    return 0;
}