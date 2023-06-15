//
// Created by koech on 6/15/2023.
//

#ifndef TEST_MINSTACK_H
#define TEST_MINSTACK_H

#include "../pair.h"
#include "../utils.h"

#include <stdbool.h>

//TODO - Reuse Stack DS

typedef struct {
    Pair* data;
    int capacity;
    int top;
} MinStack;

MinStack* F(createStack)();
void F(destroy)(MinStack* stack);
bool F(isEmpty)(MinStack* stack);
void F(push)(MinStack* stack, void* value);
Pair* F(pop)(MinStack* stack);
Pair* F(top)(MinStack* stack);
void F(clear)(MinStack* stack);
void F(toString)(MinStack* stack, void(*printFunc)(void*));

#endif //TEST_MINSTACK_H
