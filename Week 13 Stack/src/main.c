#include <stdio.h>
#include "Stack.h"

void AskForInput(double *InputVal);

int main()
{
	int State = -1;
	double InputValue;
	double ExtractedValue;
	char YesNo = '\0';

	while (1)
	{
		printf("Hello user this is the demo of the Stack App!\n");
		printf("Press 1: Create A Stack!\n");
		printf("Press 2: Push An Element On The Stack!\n");
		printf("Press 3: Pop An Element Of The Stack!\n");
		printf("Press 4: Show The Top Of The Stack!\n");
		printf("Press 5: Destroy The Stack!\n");
		printf("Press 0: Create A Stack!\n");
		scanf("%d", &State);

		switch (State)
		{
		case 1:
			stack_create();
			break;
		case 2:
			AskForInput(&InputValue);
			stack_push(&InputValue);
			break;
		case 3:
			stack_pop(&ExtractedValue);
			break;
		case 4:
			stack_top(&ExtractedValue);
			break;
		case 5:
			stack_destroy();
			break;
		case 0:
			while (YesNo != 'Y' && YesNo != 'y' && YesNo != 'N' && YesNo != 'n')
			{
				printf("Did you mean to close the App! [Y/N]: ");
				scanf("%c", &YesNo);
			}

			if (YesNo == 'Y' || YesNo == 'y')
				exit(0);

			YesNo = '\0';
			break;
		default:
			printf("Oops, Something went wrong!\n");
			break;
		}
	}

	return (0);
}

void AskForInput(double *InputVal)
{
	printf("Please insert a value!(double): ");
	scanf("%lf", InputVal);
}