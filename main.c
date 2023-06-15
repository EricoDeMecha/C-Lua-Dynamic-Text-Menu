#include <stdio.h>
#include "stack.h"

void printInt(void* value){
    printf("%d", ((int*)value));
}
int main() {
    Stack* stack = createStack();

    push(stack, (int*)1);
    push(stack, (int*)2);
    push(stack, (int*)3);
    push(stack, (char*)'A');
    resize(stack);
    toString(stack,printInt);
    printf("\n");
    destroy(stack);
    return 0;
}