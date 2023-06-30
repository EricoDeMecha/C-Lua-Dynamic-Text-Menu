//
// Created by koech on 6/15/2023.
//

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <string.h>
#include "pair/pair.h"
#include "minimumStack/minstack.h"
#include "stack/stack.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define create(type) _Generic((type){}, \
    Stack: createStack(), \
    MinStack: createMinStack() \
)
#define destroy(stack) _Generic((stack), \
    Stack*: destroyStack, \
    MinStack*: destroyMinStack \
)(stack)

#define isEmpty(stack) _Generic((stack), \
    Stack*: isStackEmpty, \
    MinStack*: isMinStackEmpty \
)(stack)

#define push(stack, value) _Generic((stack), \
    Stack*: pushStack, \
    MinStack*: pushMinStack \
)(stack, value)

#define pop(stack) _Generic((stack), \
    Stack*: popStack, \
    MinStack*: popMinStack \
)(stack)

#define top(stack) _Generic((stack), \
    Stack*: topStack, \
    MinStack*: topMinStack \
)(stack)

#define clear(stack) _Generic((stack), \
    Stack*: clearStack, \
    MinStack*: clearMinStack \
)(stack)

#define toString(stack, printFunc) _Generic((stack), \
    Stack*: toStringStack, \
    MinStack*: toStringMinStack \
)(stack, printFunc)


void printInt(void* value);
void printChar(void* value);
void printPairInts(void* value);
void printPairFloats(void* value);
void printPairChars(void* value);
char* concatenateStrings(const char* str1, const char* str2);
char* normalize_path(const char* path);
#endif //TEST_UTILS_H
