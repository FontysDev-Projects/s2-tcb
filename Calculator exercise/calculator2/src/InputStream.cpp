// #include <definition.h>

// void getInput()
// {
//   //get data
//   if (Serial.available() > 0)
//   {
//     Serial.readBytes(&input, 1);
//   }
//   filterInput();
// }

// void filterInput()
// {
//   //filter the noise
//   if (input != 0)
//   {
//     //cher the value
//     switch (input)
//     {
//     case '\n':
//       Serial.println();
//       if (CalculatorStage == S_INPUT)
//       {
//         Serial.print("Procesing");
//         CalculatorStage = S_PROCESSING;
//       }
//       else if (CalculatorStage == S_PROCESSING)
//       {
//         Serial.print("Input");
//         CalculatorStage = S_OUTPUT;
//       }
//       break;

//       if (CalculatorModes == M_INPUT_OPERATOR){
//       case '+':
//         Operate = PLUS;
//         Serial.print(input);
//         break;

//       case '-':
//         Operate = MINUS;
//         Serial.print(input);
//         break;

//       case '/':
//         Operate = DEVISION;
//         Serial.print(input);
//         break;

//       case '*':
//         Operate = MULTYPLICATION;
//         Serial.print(input);
//         break;
//       }

//     case (char)0x08:
//       Serial.print(input);
//       Serial.print((char)0x20);
//       Serial.print(input);
//       counter--;
//       break;

//     //if it is an int value
//     default:
//       if ((int)input >= (int)'0' && (int)input <= (int)'9')
//       {
//         if (counter <= 10)
//         {
//           Serial.print(input);
//           buffer[counter] = input;
//           counter++;
//         }
//       }
//       break;
//     }
//   }
//   input = 0;
// }