//
// Created by koech on 6/15/2023.
//

#ifndef TEST_MINSTACK_H
#define TEST_MINSTACK_H

#include "../pair/pair.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include <stdbool.h>

//TODO - Reuse Stack DS

typedef struct {
    Pair* data;
    int capacity;
    int top;
} MinStack;

MinStack* createMinStack();
void destroyMinStack(MinStack* stack);
bool isMinStackEmpty(MinStack* stack);
void pushMinStack(MinStack* stack, void* value);
Pair* popMinStack(MinStack* stack);
Pair* topMinStack(MinStack* stack);
void clearMinStack(MinStack* stack);
void toStringMinStack(MinStack* stack, void(*printFunc)(void*));

#endif //TEST_MINSTACK_H
