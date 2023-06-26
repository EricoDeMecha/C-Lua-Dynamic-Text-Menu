#include <stdio.h>
#include "utils.h"



int main() {
    Stack* stack = create(Stack);

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

    MinStack* minStack = create(MinStack);
    push(minStack, (int*)2);
    push(minStack, (int*)4);
    push(minStack, (int*)3);
    push(minStack, (int*)5);
    push(minStack, (int*)6);
    push(minStack, (int*)7);
    push(minStack, (int*)8);
    push(minStack, (int*)31);
    push(minStack, (int*)34);
    push(minStack, (int*)54);
    push(minStack, (int*)74);
    push(minStack, (int*)44);
    push(minStack, (int*)35);
    toString(minStack, printPairInts);
    // print minimum
    void* min = top(minStack)->second;
    printf("MinStack minimum: %d\n", (int*)min);
    return 0;
}