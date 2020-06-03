#include "DataProcessing.h"

void ExecuteOperator(struct Stack *OperantStack, void *PoppedOperator)
{
    double *Output = (double *)malloc(sizeof(double));
    *Output = 1;
    void *popped;

    switch (*(char *)PoppedOperator)
    {
    case '$':
        OperantStack->Pop(OperantStack, &popped);
        *Output = sqrt((*(double *)popped));
        OperantStack->Push(OperantStack, (void *)Output);
        break;
    case '*':
        for (double i = 0; i < 2; i++)
        {
            OperantStack->Pop(OperantStack, &popped);
            *Output *= (*(double *)popped);
        }
        OperantStack->Push(OperantStack, (void *)Output);
        break;
    case '/':
        OperantStack->Pop(OperantStack, &popped);
        *Output = (*(double *)popped);
        OperantStack->Pop(OperantStack, &popped);
        *Output = (*(double *)popped) / *Output;
        OperantStack->Push(OperantStack, (void *)Output);

        break;
    case '+':
        for (double i = 0; i < 2; i++)
        {
            OperantStack->Pop(OperantStack, &popped);
            *Output += (*(double *)popped);
        }
        *Output -= 1;
        OperantStack->Push(OperantStack, (void *)Output);

        break;
    case '-':
        OperantStack->Pop(OperantStack, &popped);
        *Output = (*(double *)popped);
        OperantStack->Pop(OperantStack, &popped);
        *Output = (*(double *)popped) - *Output;
        OperantStack->Push(OperantStack, (void *)Output);
        break;

    default:
        break;
    }
}

void ProcessData(struct Stack *OperantStack, struct Stack *OperatorStack)
{
    while (OperatorStack->Count(OperatorStack) != 0)
    {
        void *PoppedOperator = NULL;
        OperatorStack->Pop(OperatorStack, &PoppedOperator);
        ExecuteOperator(OperantStack, PoppedOperator);
    }
}