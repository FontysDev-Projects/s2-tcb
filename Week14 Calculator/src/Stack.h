#ifndef __STACK_H__
#define __STACK_H__
#include <stdlib.h>

struct Stack
{
    // private:
    struct Node *head;
    int StackCapacity;
    int ElementCount;
    // methods
    // public:
    int (*Push)(struct Stack *, void *);
    int (*Pop)(struct Stack *, void **);
    int (*Top)(struct Stack *, void **);
    int (*Capacity)(struct Stack *);
    int (*Count)(struct Stack *);
};
extern const struct StackClass
{
    // fields
    struct Stack *(*new)(int size);
    int (*DestroyStack)(struct Stack *);
} Stack;

struct Node
{
    void *data;
    struct Node *next;
};

#endif