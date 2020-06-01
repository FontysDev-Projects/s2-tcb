#include <stdio.h>
#include <string.h>
#include "InputStrem.h"
#include "Stack.h"

typedef enum ProgramStates
{
	S_INPUTING,
	S_PREPROCESSING,
	S_PROCESSING,
	S_OUTPUTING
} ProgramStates;

char inputChar;
int A = 0;
int B = 0;

int main()
{
	struct Stack *ConversionStack = Stack.new(10);
	struct Stack *OperatorStack = Stack.new(50);
	struct Stack *OperantStack = Stack.new(50);

	if (!ConversionStack)
		exit(-1);
	if (!OperatorStack)
		exit(-2);
	if (!OperantStack)
		exit(-3);

	ProgramStates ProgramState = S_INPUTING;

	while (1)
	{
		switch (ProgramState)
		{
		case S_INPUTING:
			inputChar = getchar();
			if (inputChar != EOF)
				FilterInput(ConversionStack, OperatorStack, OperantStack, &inputChar);
			// ProgramState = S_PROCESSING;

			// ProgramState = S_PREPROCESSING;
			break;
		case S_PREPROCESSING:
			ProgramState = S_INPUTING;
			break;
		case S_PROCESSING:
			ProgramState = S_OUTPUTING;
			break;
		case S_OUTPUTING:
			ProgramState = S_INPUTING;
			break;
		}
	}

	return (0);

	//Filterinput
}