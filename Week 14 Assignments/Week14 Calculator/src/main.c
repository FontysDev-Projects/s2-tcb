#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputStrem.h"
#include "DataProcessing.h"

#define MathExpression Argv[1]
#define input Argv[1][i]

int NumChar = 0;

int main(int Argc, char *Argv[])
{
	/**
	 * 1. Checking for valid input
	 * 2. Checking for sufficient memory
	 */
	if (Argc > 2)
	{
		printf("Too many Arguments supplied!");
		exit(1);
	}
	if (Argc < 2)
	{
		printf("2 Arguments expected!");
		exit(1);
	}

	struct Stack *OperatorStack = Stack.new(50);
	struct Stack *OperantStack = Stack.new(50);
	if (!OperatorStack)
		exit(-2);
	if (!OperantStack)
		exit(-3);

	/**
	 * Preconfiguring and preprocessing the math expression 
	 */
	int MathExpressionLenght = strlen(MathExpression);

	for (int i = 0; i < MathExpressionLenght; i++)
	{
		printf("%c", input);

		if (CheckOperant(input))
		{
			// printf("It is a Num!\n");
			NumChar = NumChar * 10 + ((int)(input) - (int)'0');
			continue;
		}

		if (CheckOperator(input))
		{
			// printf("It is an Operator!\n");
			if (NumChar > 0)
			{
				if (AddOperant(OperantStack, (double)NumChar))
				{
					printf("Unable to add operant %d!", NumChar);
					exit(-4);
				}
			}
			NumChar = 0;
			void *PoppedOperator = NULL;
			if (AddOperator(OperatorStack, &input, &PoppedOperator))
				continue;

			ExecuteOperator(OperantStack, PoppedOperator);
		}
	}
	if (NumChar > 0)
		if (AddOperant(OperantStack, (double)NumChar))
		{
			printf("Unable to add operant %d!", NumChar);
			exit(-4.1);
		}

	/**
	 * Processing the preconfigured Math Expresion!
	 * pushes the result on the Operant stack 
	 */
	ProcessData(OperantStack, OperatorStack);

	/**
	 * Outputs the result of the Math Expresion
	 */
	double *ExpresionOutput;
	OperantStack->Pop(OperantStack, (void *)&ExpresionOutput);
	printf("=%f\n", *ExpresionOutput);

	/**
	 * Prints the main.c source code
	 */
	// printf("\nThe main source code!\n\n");
	// system("cat src\\main.c");

	return (*ExpresionOutput);
}