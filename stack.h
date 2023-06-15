//
// Created by koech on 6/15/2023.
//

#ifndef TEST_STACK_H
#define TEST_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void** data;
    int top;
    int capacity;
} Stack;

Stack* createStack();
void destroy(Stack* stack);
bool isEmpty(Stack* stack);
void push(Stack* stack, void* value);
void* pop(Stack* stack);
void* top(Stack* stack);
void resize(Stack* stack);
void toString(Stack* stack, void(*printFunc)(void*));

#endif //TEST_STACK_H
