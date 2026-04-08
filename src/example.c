/**
 * example.c - Example implementation
 */

#include "example.h"

int add_numbers(int a, int b) {
    return a + b;
}

void print_example(const ExampleStruct *example) {
    if (example == NULL) {
        printf("Example is NULL\n");
        return;
    }
    
    printf("Example ID: %d\n", example->id);
    printf("Example Value: %.2f\n", example->value);
}