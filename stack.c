//
// Created by koech on 6/15/2023.
//

#include "stack.h"

Stack* createStack(){
    Stack* stack  = (Stack*) malloc(sizeof(Stack));
    stack->data = NULL;
    stack->top = -1;
    stack->capacity = 0;
    return stack;
}
void destroy(Stack* stack){
    free(stack->data);
    free(stack);
}
bool isEmpty(Stack* stack){
    if(stack == NULL) return true;
    return stack->top == -1;
}
void push(Stack* stack, void* value){
    if(stack == NULL) return;
    if (stack->top == stack->capacity - 1) {
        stack->capacity = stack->capacity == 0 ? 1 : stack->capacity * 2;// double the storage
        void** temp = (void**)realloc(stack->data, stack->capacity * sizeof(void*));
        if(temp == NULL){
            printf("Failed to re-allocate storage\n");
            return;
        }
        stack->data = temp;
    }
    stack->data[++stack->top] = value;
}
void* pop(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack underflow\n");
        return NULL;
    }
    return stack->data[--stack->top];
}
void* top(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is empty\n");
        return NULL;
    }
    return stack->data[stack->top];
}
void resize(Stack* stack) {
    if(stack==NULL) return;
    int newCapacity = stack->top + 1;
    void** resizedData = (void**)realloc(stack->data, newCapacity * sizeof(void*));
    if (resizedData == NULL) {
        printf("Failed to resize stack\n");
        return;
    }
    stack->data = resizedData;
    stack->capacity = newCapacity;
}

void clear(Stack* stack){
    stack->top = -1;
}
void toString(Stack* stack, void(*printFunc)(void*)){
    if(stack==NULL){
        printf("NULL");
        return;
    }
    printf("Stack: [");
    for(int i = stack->top; i >= 0; --i){
        void* value = stack->data[i];
        if(value != NULL){
            printFunc(value);
        }
        if (i > 0) {
            printf(", ");
        }
    }
    printf("]\n");
}