#include "Stack.h"

typedef struct StackNode
{
    double data;
    struct StackNode *nextNode;
} StackNode;

StackNode *head = NULL;

int stack_create(void)
{
    return 0;
}

void stack_destroy(void)
{
    if (!head)
    {
        printf("The Stack is empty!\n");
        return;
    }

    StackNode *temp;
    while (head != NULL)
    {
        temp = head->nextNode;
        free(head);
        head = temp;
    }
    printf("Stack was destroyed!\n");
}

int stack_push(const double *elem)
{
    if (!elem)
        return -1;

    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->data = *elem;
    newNode->nextNode = NULL;

    if (!head)
    {
        head = newNode;
        return 0;
    }
    newNode->nextNode = head;
    head = newNode;
    return 0;
}

int stack_pop(double *elem)
{
    if (!elem)
        return -1;

    if (!head)
        return -1;

    *elem = head->data;
    StackNode *temp = head->nextNode;
    free(head);
    head = temp;

    return 0;
}

int stack_top(double *elem)
{
    if (!head)
        return -1;

    printf("%f\n", head->data);
    *elem = head->data;
    return 0;
}