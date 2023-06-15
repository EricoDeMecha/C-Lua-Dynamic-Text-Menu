//
// Created by koech on 6/15/2023.
//
#include "utils.h"

void printInt(void* value){
    printf("%d", ((int*)value));
}
void printChar(void* value){
    printf("%c", (char*)value);
}
void printPairInts(void* value){
    Pair* temp = (Pair*)value;
    printf("{%d, %d}", (int*)temp->first, (int*)temp->second);
}

void printPairFloats(void* value){
    Pair* temp = (Pair*)value;
    printf("{%f, %f}", (float*)temp->first, (float*)temp->second);
}
void printPairChars(void* value){
    Pair* temp = (Pair*)value;
    printf("{%f, %f}", (char*)temp->first, (char*)temp->second);
}