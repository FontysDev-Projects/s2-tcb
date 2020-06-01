#include "InputStrem.h"

typedef struct KeyValuePair
{
    const char operator;
    const int priority;
} KeyValuePair;

KeyValuePair LookUpTable[] = {
    {.operator= '(', .priority = 0 },
     {.operator= ')', .priority = 0 },
      {.operator= '*', .priority = 1 },
       {.operator= '/', .priority = 1 },
        {.operator= '+', .priority = 2 },
         {.operator= '-', .priority = 2 } };

void FilterInput(struct Stack *ConversionStack, struct Stack *OperatorStack, struct Stack *OperantStack, char *inputChar)
{
    char *inputValue = (char *)malloc(sizeof(inputChar));
    *inputValue = *inputChar;

    if (*inputValue != '\n' && *inputValue != '\r')
        if (inputValue == NULL)
            return;

    //Cheking if the input is a Number
    if ((int)(*inputValue) >= (int)'0')
        if ((int)(*inputValue) <= (int)'9')
        {
            //Pushing the number to the ConversionStack
            printf("Its a NUM!!!\n");

            ConversionStack->Push(ConversionStack, inputValue);
            return;
        }

    //Checking if the input is an Operator
    void *PoppedOperator = NULL;
    if (!CheckOperator(*inputValue))
        return;

    printf("Its a Operator!!!\n");
    if (ConversionStack->Count(ConversionStack) > 0)
    {
        printf("Converting the operant to int!\n");
        OperantStack->Push(OperantStack, ConvertToInt(ConversionStack));
    }

    if (AddOperator(OperatorStack, inputValue, &PoppedOperator))
        return;

    if (PoppedOperator == NULL)
        return;

    if (OperantStack->Count(OperantStack) < 2)
        return;

    int Output = 1;
    void *popped;

    switch (*(char *)PoppedOperator)
    {
    case ')':

        break;
    case '*':
        for (int i = 0; i < 2; i++)
        {
            OperantStack->Pop(OperantStack, &popped);
            Output *= (*(int *)popped);
        }
        break;
    case '/':
        OperantStack->Pop(OperantStack, &popped);
        Output = (*(int *)popped);
        OperantStack->Pop(OperantStack, &popped);
        Output /= (*(int *)popped);
        break;
    case '+':
        for (int i = 0; i < 2; i++)
        {
            OperantStack->Pop(OperantStack, &popped);
            Output += (*(int *)popped);
        }
        Output -= 1;
        break;
    case '-':
        OperantStack->Pop(OperantStack, &popped);
        Output = (*(int *)popped);
        OperantStack->Pop(OperantStack, &popped);
        Output -= (*(int *)popped);
        break;

    default:
        break;
    }

    printf("Output: %d\n", Output);
}

int AddOperator(struct Stack *OperatorStack, char *inputChar, void **PoppedOperator)
{
    printf("Looking at the TopOperator!!!\n");
    void *topOperator = NULL;
    if (OperatorStack->Top(OperatorStack, &topOperator) < 0)
    {
        OperatorStack->Push(OperatorStack, inputChar);
        return -1;
    }

    if (CompareOperators((char *)topOperator, inputChar) > 0)
    {
        printf("Just Pushing operator!!!\n");
        OperatorStack->Push(OperatorStack, inputChar);
        *PoppedOperator = NULL;
    }
    else
    {
        printf("Poping and Pushing operator!!!\n");
        OperatorStack->Pop(OperatorStack, PoppedOperator);
        OperatorStack->Push(OperatorStack, inputChar);
    }
    return 0;
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

int CompareOperators(char *topOperator, char *inputChar)
{
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

    if (topOperatorPriority == 0 || inputOperatorPriority == 0)
        return 1;
    printf("1.5\n");

    if (topOperatorPriority < inputOperatorPriority)
        return -1;
    printf("1.6\n");

    if (topOperatorPriority == inputOperatorPriority)
        return 0;
    printf("1.7\n");

    if (topOperatorPriority > inputOperatorPriority)
        return 1;
    printf("1.8\n");

    return -3;
}

int *ConvertToInt(struct Stack *ConversionStack)
{
    int *A = (int *)malloc(sizeof(int));
    printf("step 1\n");

    int lenght = ConversionStack->Count(ConversionStack);
    for (int i = 0; i < lenght; i++)
    {
        void *temp = NULL;
        ConversionStack->Pop(ConversionStack, &temp);
        *A += (((*(int *)temp) - (int)'0') * Power(10, i));
    }
    // void *PoppedNum;
    // while (ConversionStack->Count(ConversionStack) > 0)
    // {
    //     ConversionStack->Pop(ConversionStack, PoppedNum);
    //     *A = (*(A)*10) + ((*(int *)PoppedNum) - (int)'0');
    // }

    return A;
}

int Power(int base, int exponent)
{
    if (exponent == 0)
        return 1;

    for (int i = 1; i < exponent; i++)
    {
        base *= base;
    }
    return base;
}