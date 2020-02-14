// #include <definition.h>

// void processing(){
//     switch (CalculatorModes)
//   {
//   case M_INPUT_FIRST_INTEGER:
//     for (int i = (counter - 1); i >= 0; i--)
//     {
//       if ((int)buffer[i] >= (int)'0' && (int)buffer[i] <= (int)'9')
//       {
//         Numbers[0] += (((int)buffer[i] - 48) * powerOf(10, (counter - 1) - i));
//         buffer[i] = 0;
//       }
//     }
//     counter = 0;
//     CalculatorModes = M_INPUT_OPERATOR;
//     CalculatorStage = S_INPUT;
//     break;


//   case M_INPUT_OPERATOR:
//     if (Operate != OPERATOR_NULL)
//     {
//         CalculatorModes = M_INPUT_SECOND_INTEGER;
//     }
//     CalculatorStage = S_INPUT;
//     break;
  

//   case M_INPUT_SECOND_INTEGER:
//     for (int i = (counter - 1); i >= 0; i--)
//     {
//       if ((int)buffer[i] >= (int)'0' && (int)buffer[i] <= (int)'9')
//       {
//         Numbers[1] += (((int)buffer[i] - 48) * powerOf(10, (counter - 1) - i));
//         buffer[i] = 0;
//       }
//     }
//     counter = 0;
//     CalculatorModes = M_INPUT_FIRST_INTEGER;
//     // CalculatorStage = S_OUTPUT;
//     break;
//   }
// }