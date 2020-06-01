#ifndef QUEUE
#define QUEUE
#include <stdlib.h>
#include <stdio.h>

//Function to create a Queue
int CreateQueue(const int);
//Destroys the current instance of the
int DestroyQueue();
//
int EnQueue(const double);

int DeQueue(double *);

int ReverseQueue();

int RuningAverage(double *);

void PrintQueue();

int Count();
#endif