#include "ArrayStack.h"
#define StackSize 20

double *Stack = NULL;
int elementCount = 0;

int stack_create(void)
{
    Stack = (double *)calloc(StackSize, sizeof(double));
    if (!Stack)
        return -1;

    return 0;
}

void stack_destroy(void)
{
    if (!Stack)
    {
        printf("Stack not found! Please, first create the stack!\n");
        return;
    }
    free(Stack);
    Stack = NULL;
    printf("Stack was destroyed!\n");
}

int stack_push(const double *elem)
{
    if (!Stack)
        return -1;

    if (elementCount == StackSize)
        return -1;

    Stack[elementCount++] = *elem;
    return 0;
}

int stack_pop(double *elem)
{
    if (!Stack)
        return -1;

    if (elementCount == 0)
        return -1;

    *elem = Stack[--elementCount];
    return 0;
}

int stack_top(double *elem)
{
    if (!Stack)
        return -1;

    if (elementCount == 0)
        return -1;

    *elem = Stack[elementCount - 1];
    printf("%lf\n", *elem);

    return 0;
}