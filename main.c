#include <stdio.h>
#include "stack.h"
#include "pair.h"
#include "utils.h"
#include "MinimumStack/minstack.h"

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

    MinStack* minStack = F(createStack)();
    F(push)(minStack, (int*)2);
    F(push)(minStack, (int*)4);
    F(push)(minStack, (int*)3);
    F(push)(minStack, (int*)5);
    F(push)(minStack, (int*)6);
    F(push)(minStack, (int*)7);
    F(push)(minStack, (int*)8);
    F(push)(minStack, (int*)31);
    F(push)(minStack, (int*)34);
    F(push)(minStack, (int*)54);
    F(push)(minStack, (int*)74);
    F(push)(minStack, (int*)44);
    F(push)(minStack, (int*)35);
    // print minimum
    void* min = F(top)(minStack)->second;

    printInt(min);
    return 0;
}