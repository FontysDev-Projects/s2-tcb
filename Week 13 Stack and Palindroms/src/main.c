#include <stdio.h>
#include <string.h>
#include "Stack.h"

int main()
{
	char String_Buffer[20];

	while (1)
	{
		printf("Please insert a String!\n");
		scanf("%s", String_Buffer);

		if (!strcmp(String_Buffer, "quit") || !strcmp(String_Buffer, "Quit"))
			exit(0);

		int strLenght = strlen(String_Buffer);
		char compareChar;
		unsigned char isPalendrome = 1;

		for (int i = 0; String_Buffer[i] != '\0'; i++)
		{
			if (i < strLenght / 2)
				stack_push(&String_Buffer[i]);
			else
			{
				if (strLenght % 2 != 0 && i == strLenght / 2)
					continue;

				stack_pop(&compareChar);
				if (compareChar != String_Buffer[i])
				{
					isPalendrome = 0;
					break;
				}
			}
		}

		if (isPalendrome)
			printf("String is a Palendrom!\n");
		else
			printf("String is not a Palindrom!\n");

		for (int i = 0; i < 20; i++)
		{
			printf("-");
		}
		printf("\n");
	}

	return (0);
}