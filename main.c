#include <stdio.h>
#include "stack.h"
#include "pair.h"

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
int main() {
    Stack* stack = createStack();

    push(stack, (int*)1);
    push(stack, (int*)2);
    push(stack, (int*)3);
    toString(stack, printInt);// print the stack containing only integers
    clear(stack);

    push(stack, (char*)'A');
    push(stack, (char*)'B');
    push(stack, (char*)'C');
    push(stack, (char*)'D');
    toString(stack, printChar);
    clear(stack);

    push(stack, makePair((int*)1, (int*)2));
    push(stack, makePair((int*)3, (int*)4));
    push(stack, makePair((int*)5, (int*)6));
    toString(stack, printPairInts);
    clear(stack);

    destroy(stack);
    return 0;
}