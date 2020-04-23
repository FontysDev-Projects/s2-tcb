#include <Arduino.h>
#define BUTTON_1 PINB2
#define BUTTON_2 PINB3
#define GREEN_LED PIND5
#define RED_LED PIND6
#define LED_TIMER 500

#define buttonsMask (1 << BUTTON_1 | 1 << BUTTON_2)
#define ledMask (1 << GREEN_LED | 1 << RED_LED)

#define isPrinted 1
#define hasChanged 2
#define Check_SFOR(a) (SFOR & (1 << a))
#define Toggle_SFOR(a) (SFOR ^= (1 << a))
#define SetFalse_SFOR(a) (SFOR &= ~(1 << a))
#define SetTrue_SFOR(a) (SFOR |= (1 << a))

void LedBlinking();
void PrintHello();

uint8_t SFOR = 0;

volatile uint8_t SoftwareFlagRegister = 0;

void ISR_ButtonFunc(uint8_t button, uint8_t buttonState);

ISR(PCINT0_vect)
{
  static int LastButton1State = HIGH;
  static int LastButton2State = HIGH;

  uint8_t button1Status = (PINB & (1 << BUTTON_1));
  uint8_t button2Status = (PINB & (1 << BUTTON_2));

  if (button1Status != LastButton1State)
  {
    ISR_ButtonFunc(BUTTON_1, button1Status);
    LastButton1State = button1Status;
  }
  if (button2Status != LastButton2State)
  {
    ISR_ButtonFunc(BUTTON_2, button2Status);
    LastButton2State = button2Status;
  }
}

void ISR_ButtonFunc(uint8_t button, uint8_t buttonState)
{
  static uint32_t timeCheck = 0;
  if (millis() - timeCheck > 20)
  {
    timeCheck = millis();
    if (buttonState == LOW)
    {
      SoftwareFlagRegister ^= (1 << button);
    }
  }
}

void setup()
{
  // setting up Button1 and Button2 (pin 10 & pin 11) to INPUT_PULLUP
  DDRB &= ~(buttonsMask);
  PORTB |= (buttonsMask);

  // setting up Green and Red LED to OUTPUT and LOW as init state
  DDRD |= (ledMask);
  PORTD &= ~(ledMask);

  //starting up the serial communication
  Serial.begin(9600);

  // SETING UP THE INTERUPTS FOR PIN 10 AND PIN 11
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << BUTTON_1) | (1 << BUTTON_2);
  PCIFR |= (1 << PCIF0); // clearing interrupt flag register
  sei();                 // Unabling interrupts
}

void loop()
{
  switch (SoftwareFlagRegister)
  {
  case (1 << BUTTON_1):
    PORTD |= (1 << GREEN_LED);
    PORTD &= ~(1 << RED_LED);
    PrintHello();
    break;

  case (1 << BUTTON_2):
    PORTD |= (1 << RED_LED);
    PORTD &= ~(1 << GREEN_LED);
    PrintHello();
    break;

  case buttonsMask:
    LedBlinking();
    SetTrue_SFOR(isPrinted);
    break;

  default:
    PORTD &= ~(ledMask);
    SetTrue_SFOR(isPrinted);
    break;
  }
}

void LedBlinking()
{
  static uint32_t timeCheck = 0;
  if (millis() - timeCheck > LED_TIMER)
  {
    timeCheck = millis();
    Toggle_SFOR(hasChanged);
    if (Check_SFOR(hasChanged))
    {
      PORTD |= (1 << GREEN_LED);
      PORTD &= ~(1 << RED_LED);
    }
    else
    {
      PORTD &= ~(1 << GREEN_LED);
      PORTD |= (1 << RED_LED);
    }
  }
}

void PrintHello()
{
  if (Check_SFOR(isPrinted))
  {
    Serial.println("Hello World");
    SetFalse_SFOR(isPrinted);
  }
}