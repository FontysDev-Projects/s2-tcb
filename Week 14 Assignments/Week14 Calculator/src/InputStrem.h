#ifndef __INPUT_STREAM_H__
#define __INPUT_STREAM_H__
#include "Stack.h"
// #include <stdio.h>

/**
 * Adds an Operator to the Operator Stack!
 * Outputs an Operator from the Stack!
 * returns: 
 *         -1 - when no Operator is returned!
 *          0 - when an Operator is returned!
 */
int AddOperator(struct Stack *, char *, void **);
/**
 * Adds an Operant to the Operant Stack!
 * returns the Stack's status return:
 *          0 - on success!
 *          less than 0 - on failure! 
 */
int AddOperant(struct Stack *, double);
/**
 * Compares 2 Operators
 * returns:
 *         -1 - when the Top operator of the stack is with higher priority!
 *          0 - when the input operator and the Top operator of the stack,
 *              is with the same priority!
 *          1 - when the input operator is with higher priority!
 */
int CompareOperators(char *, char *);
/**
 * Checks if the it char is an Operator!
 * returns: 
 *          0 - on fail to recognize 
 *          1 - on success
 */
int CheckOperator(const char);

/**
 * Checks if the it char is an Operant!
 * returns: 
 *          0 - on fail to recognize 
 *          1 - on success
 */
int CheckOperant(const char);

#endif