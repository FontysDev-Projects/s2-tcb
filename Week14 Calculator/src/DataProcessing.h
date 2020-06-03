#ifndef __DATA_PROCESSING_H__
#define __DATA_PROCESSING_H__
#include <math.h>
#include "Stack.h"

/**
 * Executes an algorithm based on the inputed Operator
 * and pushes the result on the stack!
 */
void ExecuteOperator(struct Stack *, void *);

/**
 * Processing the preconfigured Math Expresion!
 * pushes the result on the Operant stack!
 */
void ProcessData(struct Stack *, struct Stack *);

#endif