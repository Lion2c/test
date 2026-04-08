/**
 * example.h - Example header file
 */

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <stdio.h>

// Simple function prototype
int add_numbers(int a, int b);

// Example structure
typedef struct {
    int id;
    double value;
} ExampleStruct;

// Function to print example structure
void print_example(const ExampleStruct *example);

#endif // EXAMPLE_H