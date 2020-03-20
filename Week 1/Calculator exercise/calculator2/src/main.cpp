#include "definition.h"

void setup()
{
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  PORTD = PORTD & B11111111;
  Serial.begin(9600);

  Serial.println("\nHi, I am Calculus!");
  Serial.println("How may I help you?\n");
}

void loop()
{
  // put your main code here, to run repeatedly
  switch (CalculatorStage)
  {
  case S_INPUT:
    if (message)
    {
      if (CalculatorModes == M_INPUT_FIRST_INTEGER || CalculatorModes == M_INPUT_SECOND_INTEGER)
      {
        Serial.println("Please insert a positive Number!");
      }
      else
      {
        Serial.println("Please insert an operator ('+', '-', '*', '/')");
      }
      message = 0;
    }

    getInput();
    break;
  case S_PROCESSING:
    processing();
    break;
  case S_OUTPUT:
    switch (Operate)
    {
    case PLUS:
      output = Numbers[0] + Numbers[1];
      break;
    case MINUS:
      output = Numbers[0] - Numbers[1];
      break;
    case DEVISION:
      output = Numbers[0] / Numbers[1];
      break;
    case MULTYPLICATION:
      output = Numbers[0] * Numbers[1];
      break;
    }
    Serial.print("The output is: ");
    Serial.println(output);
    Numbers[0] = 0;
    Numbers[1] = 0;
    CalculatorStage = S_INPUT;

    if (output > 0)
    {
      PORTD = B01000000;
    }
    else if (output < 0)
    {
      PORTD = B00100000;
    }
    else
    {
      PORTD = 0;
    }
    break;
  }
}

void processing()
{
  switch (CalculatorModes)
  {
  case M_INPUT_FIRST_INTEGER:
    for (int i = (counter - 1); i >= 0; i--)
    {
      if ((int)buffer[i] >= (int)'0' && (int)buffer[i] <= (int)'9')
      {
        Numbers[0] += (((int)buffer[i] - 48) * powerOf(10, (counter - 1) - i));
        buffer[i] = 0;
      }
    }
    counter = 0;
    CalculatorModes = M_INPUT_OPERATOR;
    CalculatorStage = S_INPUT;
    message = 1;
    break;

  case M_INPUT_OPERATOR:
    if (Operate != OPERATOR_NULL)
    {
      CalculatorModes = M_INPUT_SECOND_INTEGER;
      message = 1;
    }
    CalculatorStage = S_INPUT;
    break;

  case M_INPUT_SECOND_INTEGER:
    for (int i = (counter - 1); i >= 0; i--)
    {
      if ((int)buffer[i] >= (int)'0' && (int)buffer[i] <= (int)'9')
      {
        Numbers[1] += (((int)buffer[i] - 48) * powerOf(10, (counter - 1) - i));
        buffer[i] = 0;
      }
    }
    counter = 0;
    CalculatorModes = M_INPUT_FIRST_INTEGER;
    CalculatorStage = S_OUTPUT;
    break;
  }
}

void getInput()
{
  //get data
  if (Serial.available() > 0)
  {
    Serial.readBytes(&input, 1);
  }
  filterInput();
}

void filterInput()
{
  //filter the noise
  if (input != 0)
  {
    //cher the value
    switch (input)
    {
    case '\n':
      Serial.println();
      if (CalculatorStage == S_INPUT)
      {
        //Serial.print("Procesing");
        CalculatorStage = S_PROCESSING;
      }
      else if (CalculatorStage == S_PROCESSING)
      {
        // Serial.print("Input");
        CalculatorStage = S_OUTPUT;
      }
      break;

    case (char)0x08:
      Serial.print(input);
      Serial.print((char)0x20);
      Serial.print(input);
      counter--;
      break;

    //if it is an int value
    default:
      if (CalculatorModes == M_INPUT_FIRST_INTEGER || CalculatorModes == M_INPUT_SECOND_INTEGER)
      {
        if ((int)input >= (int)'0' && (int)input <= (int)'9')
        {
          if (counter <= 10)
          {
            Serial.print(input);
            buffer[counter] = input;
            counter++;
          }
        }
      }
      else if (CalculatorModes == M_INPUT_OPERATOR)
      {
        switch (input)
        {
        case '+':
          Operate = PLUS;
          Serial.print(input);
          break;

        case '-':
          Operate = MINUS;
          Serial.print(input);
          break;

        case '/':
          Operate = DEVISION;
          Serial.print(input);
          break;

        case '*':
          Operate = MULTYPLICATION;
          Serial.print(input);
          break;
        }
      }
      break;
    }
  }
  input = 0;
}