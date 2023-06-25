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
void destroyStack(Stack* stack);
bool isStackEmpty(Stack* stack);
void pushStack(Stack* stack, void* value);
void* popStack(Stack* stack);
void* topStack(Stack* stack);
void resizeStack(Stack* stack);
void clearStack(Stack* stack);
void toStringStack(Stack* stack, void(*printFunc)(void*));

#endif //TEST_STACK_H
