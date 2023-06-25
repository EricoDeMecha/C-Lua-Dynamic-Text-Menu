//
// Created by koech on 6/15/2023.
//
#include "minstack.h"

MinStack* createMinStack(){
    MinStack* stack = (MinStack*) malloc(sizeof(MinStack));
    if(stack != NULL){
        stack->data = NULL;
        stack->top = -1 ;
        stack->capacity = 0;
    }
    return stack;
}
void destroyMinStack(MinStack* stack){
    free(stack->data);
    free(stack);
}
bool isMinStackEmpty(MinStack* stack){
    if(stack == NULL) return true;
    return stack->top == -1;
}
void pushMinStack(MinStack* stack, void* value){
    if(stack == NULL) return;
    void* newMin = isMinStackEmpty(stack)? value : MIN(value, topMinStack(stack)->second);
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
Pair* popMinStack(MinStack* stack){
    if(isMinStackEmpty(stack)){
        printf("Stack underflow\n");
        return NULL;
    }
    return &stack->data[--stack->top];
}
Pair* topMinStack(MinStack* stack){
    if(isMinStackEmpty(stack)){
        printf("Stack is empty\n");
        return NULL;
    }
    return &stack->data[stack->top];
}
void clearMinStack(MinStack* stack){
    stack->top = -1;
}
void toStringMinStack(MinStack* stack, void(*printFunc)(void*)){
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