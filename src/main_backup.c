/**
 * main.c - Main entry point for the test project
 */

#include <stdio.h>
#include "example.h"

int main(int argc, char *argv[]) {
    printf("Hello from C Test Project!\n");
    
    // Example function call
    int result = add_numbers(5, 3);
    printf("5 + 3 = %d\n", result);
    
    // Example with the example module
    ExampleStruct example;
    example.id = 1;
    example.value = 42.5;
    
    print_example(&example);
    
    return 0;
}