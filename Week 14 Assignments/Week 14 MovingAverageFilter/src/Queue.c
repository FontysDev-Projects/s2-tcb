#include "Queue.h"

// Queue properties
int Capacity;
int ElementCount = 0;
double ValueSum = 0;
// array pointer
double *Queue;
// the index of the first element of the queue
int front = 0;

int CreateQueue(const int Size)
{
    if (Size <= 0)
        return -1;

    Queue = (double *)calloc(Size, sizeof(double));
    Capacity = Size;

    if (!Queue)
        return -2;

    return 0;
}

int DestroyQueue()
{
    free(Queue);

    if (!Queue)
        return 0;

    return -1;
}

int Count() { return ElementCount; }

int EnQueue(const double newElement)
{
    if (!Queue)
        return -1;

    if (ElementCount >= Capacity)
        return -2;

    Queue[(front + ElementCount++) % Capacity] = newElement;
    ValueSum += newElement;

    return 0;
}

int DeQueue(double *elem)
{
    if (!Queue)
        return -1;

    if (ElementCount <= 0)
        return -2;

    *elem = Queue[front];
    ElementCount--;
    (++front == Capacity) ? front = 0 : 0;
    ValueSum -= *elem;

    return 0;
}

int ReverseQueue()
{
    if (!Queue)
        return -1;

    if (ElementCount <= 1)
        return -2;

    double Temp;
    for (int i = 0; i < ElementCount / 2; i++)
    {
        Temp = Queue[(front + ElementCount + i) % ElementCount];
        Queue[(front + ElementCount + i) % ElementCount] = Queue[(front + (ElementCount - i - 1)) % ElementCount];
        Queue[(front + (ElementCount - i - 1)) % ElementCount] = Temp;
    }
    return 0;
}

int RuningAverage(double *OutputAverage)
{
    if (!Queue)
        return -1;

    if (ValueSum <= 0 || ElementCount <= 0)
        return -2;

    *OutputAverage = ValueSum / ElementCount;
    return 0;
}

void PrintQueue()
{
    for (int i = 0; i < ElementCount; i++)
    {
        printf("%lf ", Queue[i]);
    }
    printf("\n");
}