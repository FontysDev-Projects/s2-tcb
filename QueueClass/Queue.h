#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stdlib.h>
#include "Nodes.h"

struct Queue
{
    // private:
    struct Node *front;
    int QueueCapacity;
    int ElementCount;
    // methods
    // public:
    int (*EnQueue)(struct Queue *, void *);
    int (*DeQueue)(struct Queue *, void **);
    int (*Capacity)(struct Queue *);
    int (*Count)(struct Queue *);
};
extern const struct QueueClass
{
    // fields
    struct Queue *(*new)(int size);
    int (*DestroyQueue)(struct Queue *);
} Queue;

#endif