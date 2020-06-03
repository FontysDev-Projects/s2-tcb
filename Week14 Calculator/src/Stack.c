#include "Stack.h"
// #include <stdio.h>

/*
* Creates the new stack. Returns 0 on success
*/
static struct Stack *new (int size);

/*
* Destroys the stack.
*/
static int DestroyStack(struct Stack *this);

/*
* Pushes a new elemenrt on the stack
* returns 0 on success
* returns -1 on error
*/
static int Push(struct Stack *this, void *newElement);

/*
* Pops an element from the stack
* returns 0 on success
* returns -1 on error
*/
static int Pop(struct Stack *this, void **elem);

/*
 * Show the top element of the stack
 * return 0 on success
 * return -1 on error or empty
 */
static int Top(struct Stack *this, void **elem);

/*
 * Returns the number of elements in the stack
 */
static int Count(struct Stack *this);

/*
 * Returns the Capacity of the Stack
 */
static int GetCapacity(struct Stack *this);

const struct StackClass Stack = {.new = &new, .DestroyStack = &DestroyStack};

static struct Stack *new (int size)
{
    struct Stack *newStack = (struct Stack *)malloc(sizeof(struct Stack));
    newStack->Push = &Push;
    newStack->Pop = &Pop;
    newStack->Top = &Top;
    newStack->Count = &Count;
    newStack->Capacity = &GetCapacity;
    newStack->head = NULL;
    newStack->StackCapacity = size;
    newStack->ElementCount = 0;

    return newStack;
}

static int DestroyStack(struct Stack *this)
{
    struct Node *temp;
    while (this->head != NULL)
    {
        temp = this->head->next;
        free(this->head->data);
        free(this->head);
        this->head = temp;
    }

    free(this);

    if (!this)
        return 0;

    return -1;
}

static int Count(struct Stack *this) { return this->ElementCount; }

static int GetCapacity(struct Stack *this) { return this->StackCapacity; }

static int Push(struct Stack *this, void *newElement)
{
    if (!this)
        return -1;
    // printf("0.4\n");

    if (!newElement)
        return -2;
    // printf("0.5\n");

    if (this->ElementCount >= this->StackCapacity)
        return -3;
    // printf("0.6\n");

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = newElement;
    newNode->next = NULL;

    // printf("0.7\n");
    if (!this->head)
    {
        this->head = newNode;
        this->ElementCount++;
        return 0;
    }
    // printf("0.8\n");
    newNode->next = this->head;
    this->head = newNode;
    this->ElementCount++;
    return 0;
}

static int Pop(struct Stack *this, void **elem)
{
    if (!this)
        return -1;

    if (!this->head)
        return -2;

    if (this->ElementCount <= 0)
        return -3;

    *elem = this->head->data;
    struct Node *temp = this->head->next;
    free(this->head);
    this->head = temp;
    this->ElementCount--;

    return 0;
}

static int Top(struct Stack *this, void **elem)
{
    if (!this)
        return -1;
    // printf("0.1\n");

    if (!this->head)
        return -2;
    // printf("0.2\n");

    if (!this->head->data)
        return -3;
    // printf("0.3\n");

    *elem = this->head->data;
    // printf("0.3.1\n");
    return 0;
}