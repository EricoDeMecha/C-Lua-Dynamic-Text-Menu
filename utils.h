//
// Created by koech on 6/15/2023.
//

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include "pair.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define F(fcn) f1_##fcn

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void printInt(void* value);
void printChar(void* value);
void printPairInts(void* value);
void printPairFloats(void* value);
void printPairChars(void* value);

#endif //TEST_UTILS_H
