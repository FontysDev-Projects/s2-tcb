#ifndef INPUT_STREAM
#define INPUT_STREAM
#include <stdio.h>
#include "Stack.h"

void FilterInput(struct Stack *, struct Stack *, struct Stack *, char *);
int AddOperator(struct Stack *, char *, void **);
int CompareOperators(char *, char *);
int CheckOperator(const char);
int *ConvertToInt(struct Stack *);
int Power(int, int);

#endif