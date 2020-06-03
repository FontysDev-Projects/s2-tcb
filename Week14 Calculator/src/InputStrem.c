#include "InputStrem.h"

typedef struct KeyValuePair
{
    const char operator;
    const int priority;
} KeyValuePair;

KeyValuePair LookUpTable[] = {
    {.operator= '(', .priority = 0 },
     {.operator= ')', .priority = 0 },
      {.operator= '$', .priority = 1 },
       {.operator= '*', .priority = 2 },
        {.operator= '/', .priority = 2 },
         {.operator= '+', .priority = 3 },
          {.operator= '-', .priority = 3 } };

int AddOperant(struct Stack *OperantStack, double operantValue)
{
    double *Operant = (double *)malloc(sizeof(double));
    *Operant = operantValue;
    return OperantStack->Push(OperantStack, Operant);
}

int AddOperator(struct Stack *OperatorStack, char *inputChar, void **PoppedOperator)
{
    // static int isSubSequence = 0;
    // if (*inputChar == '(')
    //     isSubSequence = 1;

    // if (isSubSequence)
    //     if (*inputChar == ')')
    //     {
    //         isSubSequence = 0;
    //         return -2;
    //     }

    // printf("Looking at the TopOperator!!!\n");
    void *topOperator = NULL;
    if (OperatorStack->Top(OperatorStack, &topOperator) < 0)
    {
        OperatorStack->Push(OperatorStack, inputChar);
        return -1;
    }

    if (CompareOperators((char *)topOperator, inputChar) > 0)
    {
        // printf("Just Pushing operator!!!\n");
        OperatorStack->Push(OperatorStack, inputChar);
        return -1;
    }
    else
    {
        // printf("Poping and Pushing operator!!!\n");
        OperatorStack->Pop(OperatorStack, PoppedOperator);
        OperatorStack->Push(OperatorStack, inputChar);
    }

    return 0;
}

int CompareOperators(char *topOperator, char *inputChar)
{
    if (*topOperator == '(')
        return 1;

    if (*inputChar == ')')
        return 0;

    int LookUpTableLenght = (sizeof(LookUpTable) / sizeof(LookUpTable[0]));

    int topOperatorPriority = -1;
    int inputOperatorPriority = -1;

    for (int i = 0; i < LookUpTableLenght; i++)
    {
        if ((int)(LookUpTable[i].operator) == (int)(*topOperator))
            topOperatorPriority = LookUpTable[i].priority;

        if ((int)(LookUpTable[i].operator) == (int)(*inputChar))
            inputOperatorPriority = LookUpTable[i].priority;
    }

    if (topOperatorPriority < inputOperatorPriority)
        return -1;
    // printf("1.6\n");

    if (topOperatorPriority == inputOperatorPriority)
        return 0;
    // printf("1.7\n");

    if (topOperatorPriority > inputOperatorPriority)
        return 1;
    // printf("1.8\n");

    return -3;
}

int CheckOperator(const char Operator)
{
    int LookUpTableLenght = (sizeof(LookUpTable) / sizeof(LookUpTable[0]));

    for (int i = 0; i < LookUpTableLenght; i++)
    {
        if ((int)(LookUpTable[i].operator) == (int)(Operator))
            return 1;
    }
    return 0;
}

int CheckOperant(const char operant)
{
    if ((int)(operant) >= (int)'0')
        if ((int)(operant) <= (int)'9')
            return 1;

    return 0;
}