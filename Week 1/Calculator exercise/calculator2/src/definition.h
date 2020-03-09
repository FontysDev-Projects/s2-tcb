#ifndef DEFINITION
#define DEFINITION

#include <Arduino.h>

#define RED_LED 5
#define GREEN_LED 6

typedef enum Stages
{
  S_INPUT,
  S_PROCESSING,
  S_OUTPUT
} stage;

stage CalculatorStage = S_INPUT;

typedef enum Modes
{
  M_INPUT_FIRST_INTEGER,
  M_INPUT_OPERATOR,
  M_INPUT_SECOND_INTEGER
} mode;

mode CalculatorModes = M_INPUT_FIRST_INTEGER;

typedef enum Operators
{
  OPERATOR_NULL,
  PLUS,
  MINUS,
  DEVISION,
  MULTYPLICATION
} operators;

operators Operate = OPERATOR_NULL;

void getInput();
void filterInput();
void processing();
int powerOf(int, int);

char input;
char buffer[10] = {};
int counter = 0;

int Numbers[2];
double output = 0;

int message = 1;

#endif