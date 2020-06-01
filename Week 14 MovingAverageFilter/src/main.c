#include <stdio.h>
#include "Queue.h"
#define QueueSize 10

int main()
{
	char input = 'a';
	double runingAverage;
	double DeQueueOut;
	double InitValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	int iterations = 5;
	// (sizeof(InitValues) / sizeof(InitValues[0]));
	if (CreateQueue(QueueSize))
	{
		printf("Couldn't create a Queue!\n");
		exit(1);
	}
	printf("Queue created\n");

	while (input != 'q')
	{
		for (int i = 0; i < iterations; i++)
		{
			if (Count() >= QueueSize)
				DeQueue(&DeQueueOut);

			EnQueue(InitValues[i]);
			RuningAverage(&runingAverage);

			printf("The running average is: %lf\n", runingAverage);
		}
		printf("Do you want to close the app? [type: q] ");
		scanf("%c", &input);
	}

	return (0);
}