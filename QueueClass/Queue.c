#include "Queue.h"

static struct Queue *new (int size);
static int DestroyQueue(struct Queue *this);
static int Count(struct Queue *this);
static int GetCapacity(struct Queue *this);
static int EnQueue(struct Queue *this, void *newElement);
static int DeQueue(struct Queue *this, void **elem);

const struct QueueClass Queue = {.new = &new, .DestroyQueue = &DestroyQueue};

static struct Queue *new (int size)
{
    struct Queue *newQueue = (struct Queue *)malloc(sizeof(struct Queue));
    newQueue->EnQueue = &EnQueue;
    newQueue->DeQueue = &DeQueue;
    newQueue->Count = &Count;
    newQueue->Capacity = &GetCapacity;
    newQueue->front = NULL;
    newQueue->QueueCapacity = size;
    newQueue->ElementCount = 0;

    return newQueue;
}

static int DestroyQueue(struct Queue *this)
{
    struct Node *current = this->front;
    struct Node *next;
    while (current != NULL)
    {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(this);

    if (!this)
        return 0;

    return -1;
}

static int Count(struct Queue *this) { return this->ElementCount; }

static int GetCapacity(struct Queue *this) { return this->QueueCapacity; }

static int EnQueue(struct Queue *this, void *newElement)
{
    if (!this)
        return -1;

    if (this->ElementCount >= this->QueueCapacity)
        return -2;

    if (!newElement)
        return -3;

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = newElement;
    newNode->next = NULL;

    if (!this->front)
    {
        this->front = newNode;
        this->ElementCount++;
        return 0;
    }

    struct Node *current = this->front;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    this->ElementCount++;

    return 0;
}

static int DeQueue(struct Queue *this, void **elem)
{
    if (!this)
        return -1;

    if (this->ElementCount <= 0)
        return -2;

    *elem = this->front->data;
    struct Node *next = this->front->next;
    free(this->front);
    this->front = next;

    this->ElementCount--;

    return 0;
}
