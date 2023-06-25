//
// Created by koech on 6/15/2023.
//
#include "minstack.h"

MinStack* F(createStack)(){
    MinStack* stack = (MinStack*) malloc(sizeof(MinStack));
    if(stack != NULL){
        stack->data = NULL;
        stack->top = -1 ;
        stack->capacity = 0;
    }
    return stack;
}
void F(destroy)(MinStack* stack){
    free(stack->data);
    free(stack);
}
bool F(isEmpty)(MinStack* stack){
    if(stack == NULL) return true;
    return stack->top == -1;
}
void F(push)(MinStack* stack, void* value){
    if(stack == NULL) return;
    void* newMin = F(isEmpty)(stack)? value : MIN(value, F(top)(stack)->second);
    if(stack->top == stack->capacity - 1){
        stack->capacity = stack->capacity == 0 ? 1 : stack->capacity * 2;// double the storage
        Pair* temp = (Pair*)realloc(stack->data, stack->capacity * sizeof(Pair));
        if(temp == NULL){
            printf("Failed to reallocate storage\n");
            return;
        }
        stack->data = temp;
    }
    stack->data[++stack->top] = *makePair(value, newMin);
}
Pair* F(pop)(MinStack* stack){
    if(F(isEmpty)(stack)){
        printf("Stack underflow\n");
        return NULL;
    }
    return &stack->data[--stack->top];
}
Pair* F(top)(MinStack* stack){
    if(F(isEmpty)(stack)){
        printf("Stack is empty\n");
        return NULL;
    }
    return &stack->data[stack->top];
}
void F(clear)(MinStack* stack){
    stack->top = -1;
}
void F(toString)(MinStack* stack, void(*printFunc)(void*)){
    if(stack==NULL){
        printf("NULL");
        return;
    }
    printf("MinStack: [");
    for(int i = stack->top; i >= 0; --i){
        Pair* value = &stack->data[i];
        if(value != NULL){
            printFunc(value);
        }
        if (i > 0) {
            printf(", ");
        }
    }
    printf("]\n");
}