//
// Created by koech on 6/15/2023.
//
#include "pair.h"

Pair* makePair(void* first, void* second){
    Pair* pair = (Pair*)malloc(sizeof(Pair));
    if(pair != NULL){
        pair->first = first;
        pair->second = second;
    }
    return pair;
}