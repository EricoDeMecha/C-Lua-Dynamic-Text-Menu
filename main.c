#include <stdio.h>
#include "stack.h"

int main() {
    Stack* stack = createStack();

    int a = 1;
    char b = 'A';
    float c = 3.14f;

    push(stack, &a);
    push(stack, &b);
    push(stack, &c);

    resize(stack);

    while (!isEmpty(stack)) {
        void* value = top(stack);

        if (value != NULL) {
            if (value == &a) {
                printf("%d ", *((int*)value));
            } else if (value == &b) {
                printf("%c ", *((char*)value));
            } else if (value == &c) {
                printf("%.2f ", *((float*)value));
            }
        }
        pop(stack);
    }
    printf("\n");
    destroy(stack);
    return 0;
}