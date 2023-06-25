//
// Created by koech on 6/15/2023.
//

#ifndef TEST_PAIR_H
#define TEST_PAIR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    void* first;
    void* second;
}Pair;

Pair* makePair(void* first, void* second);
#endif //TEST_PAIR_H
