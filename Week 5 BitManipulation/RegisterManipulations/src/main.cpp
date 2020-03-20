#include <Arduino.h>

#define PUSH_BUTTON_PIN PIND7
#define LED_PIN PINB2

#define Debounce_T 20
#define PWM_Cycle 5000

typedef enum LED_State
{
  OFF,
  ON
} LED_State;

LED_State ledState = OFF;

uint8_t lastState = 1;
uint32_t debounceTimer = 0;
uint32_t PWM_Timer = 0;

void ButtonState();
void pwmLEDBlink(uint8_t pinToBlink, uint32_t dutyCycle);

void setup()
{
  // DDRB, PORTB, PINB are mapped to pins 8 -> 15
  // DDRD, PORTD, PIND are mapped to pins 0 -> 7

  DDRB |= (1 << LED_PIN);          // sets the LED(pin 10) to Output
  DDRD &= ~(1 << PUSH_BUTTON_PIN); // sets the Button to Input

  PORTB &= ~(1 << LED_PIN);        // sets the state of the LED (pin 10) to LOW
  PORTD |= (1 << PUSH_BUTTON_PIN); // unables the pull-up resistor for the Button (pin 7)

  // PCMSK2 |= 1 << PCINT23; // Configure pin change interrupt on the button (pin 7)
  // PCIFR |= 1 << PCIF2;    // Clear interrupt flag
  // PCICR |= 1 << PCIE2;    // Enable interrupt for pins D0 -> D7

  // Serial.begin(9600);
}

void loop()
{
  ButtonState();
  if (ledState == ON)
  {
    pwmLEDBlink(LED_PIN, 255);
  }
  else
  {
    PORTB &= ~(1 << LED_PIN);
  }
}

void ButtonState()
{
  uint8_t currentState = (PIND >> PUSH_BUTTON_PIN) & 1;
  if (currentState != lastState)
  {
    lastState = currentState;
    if (millis() - debounceTimer > Debounce_T)
    {
      debounceTimer = millis();
      if (currentState == LOW)
      {
        if (((PINB >> LED_PIN) & 1) == 1)
        {
          ledState = OFF;
        }
        else
        {
          ledState = ON;
        }
      }
    }
  }
}

void pwmLEDBlink(uint8_t pinToBlink, uint32_t dutyCycle)
{
  //step 1 transform the dutyCycle(0, 255) to percentage
  if (dutyCycle > 255)
  {
    dutyCycle = 100;
  }
  else
  {
    dutyCycle = map(dutyCycle, 0, 255, 0, 100);
  }
  if (millis() - PWM_Timer > PWM_Cycle)
  {
    PWM_Timer = millis();
  }
  else
  {
    if (millis() - PWM_Timer > ((PWM_Cycle / 100) * dutyCycle))
    {
      PORTB &= ~(1 << pinToBlink);
    }
    else
    {
      PORTB |= (1 << pinToBlink);
    }
  }
}

// uint32_t timer = 0;

// // volatile int lastcurrentRegisterState_PIND;
// volatile uint8_t lastCheck;

// volatile uint16_t fillter = 0;

// volatile bool flag = false;

// void printStatus()
// {

//   if ((PIND >> PUSH_PUSH_BUTTON_PIN) & 1)
//   {
//     if (flag == true)
//     {
//       flag = false;
//     }
//     else
//     {
//       flag = true;
//     }
//     fillter = 0x0000;
//     sei();
//   }
// }

// ISR(PCINT2_vect)
// {
//   cli();
//   uint8_t check = (PIND >> PUSH_PUSH_BUTTON_PIN) & 1;
//   // fillter = (fillter << 1) | ((check >> PUSH_PUSH_BUTTON_PIN) ^ 1);
//   if (check != lastCheck) // c && fillter == 0xFF)
//   {
//     lastCheck = check;
//     printStatus();
//   }
//   // fillter = (fillter << 1) | ((PIND >> PUSH_PUSH_BUTTON_PIN) ^ 1) | 0xE000;
//   // if (fillter == 0xF000)
//   // {
//   //   printStatus(fillter == 0xF000);
//   // }

//   // int currentRegisterState_PIND = (PIND >> PUSH_PUSH_BUTTON_PIN) & 1;

//   // if (currentRegisterState_PIND != lastcurrentRegisterState_PIND)
//   // {
//   //   currentRegisterState_PIND = (PIND >> PUSH_PUSH_BUTTON_PIN) & 1;
//   //   if (currentRegisterState_PIND == 0)
//   //   {
//   //     printStatus(currentRegisterState_PIND == 0);
//   //   }
//   //   lastcurrentRegisterState_PIND = currentRegisterState_PIND;
//   // }
// }

// void setup()
// {
//   // DDRB, PORTB, PINB are mapped to pins 8 -> 15
//   // DDRD, PORTD, PIND are mapped to pins 0 -> 7

//   DDRB |= LED_PIN_MASK;            // sets the LED(pin 10) to Output
//   DDRD |= ~(1 << PUSH_PUSH_BUTTON_PIN); // sets the Button to Input

//   PORTB &= 0;                      // sets the state of the LED (pin 10) to LOW
//   PORTB |= (1 << PUSH_PUSH_BUTTON_PIN); // unables the pull-up resistor for the Button (pin 10)

//   PCMSK2 |= 1 << PCINT23; // Configure pin change interrupt on the button (pin 7)
//   PCIFR |= 1 << PCIF2;    // Clear interrupt flag
//   PCICR |= 1 << PCIE2;    // Enable interrupt for pins D0 -> D7

//   Serial.begin(9600);
// }

// void loop()
// {
//   // // put your main code here, to run repeatedly:
//   // if (millis() - timer > 1000)
//   // {
//   if (flag)
//   {
//     Serial.println(flag);
//   }
//   else
//   {
//     Serial.println(flag);
//   }
//   timer = millis();
//   // }
// }
