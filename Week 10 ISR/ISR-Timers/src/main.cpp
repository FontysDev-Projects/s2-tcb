#include <Arduino.h>

// BUTTONS PINS AND MACROS
#define BUTTON_SPEED_UP PIND5
#define BUTTON_SLOW_DOWN PIND6
#define BUTTONS_MASK (_BV(BUTTON_SPEED_UP) | _BV(BUTTON_SLOW_DOWN))
//Buttons interrupt setup routine --start--
#define BUTTONS_INTERRUPT_SETUP ({  PCICR |= _BV(PCIE2);  \
                                    PCIFR &= ~_BV(PCIF2); \
                                    PCMSK2 |= BUTTONS_MASK; })
//--end--

// LEDS PINS AND MACROS
#define LED_BIT_0 PINB1
#define LED_BIT_1 PINB2
#define LED_BIT_2 PINB3
#define LED_BIT_3 PINB4
#define LEDS_MASK (_BV(LED_BIT_0) | _BV(LED_BIT_1) | _BV(LED_BIT_2) | _BV(LED_BIT_3))
//Leds Counting algorithm--start--
#define LED_COUNTER(a) ({  PORTB &= ~LEDS_MASK; \
                           PORTB ^= ((a > (LEDS_MASK / 2)) ? a = 0 : a) << 1; })
//--end--

//TIMER MACROS
#define TIMER_TOP_VALUE 62499
#define TIMER_BOTTOM_VALUE 100
//Timer 1 setup routine --start--
#define TIMER_COUNTER_1_SETUP(a) ({ TCCR1A &= ~(_BV(COM1A0) | _BV(COM1A1) | _BV(WGM10) | _BV(WGM11));       \
                                    TCCR1B &= ~(_BV(WGM13) | _BV(ICES1) | _BV(ICNC1) | _BV(CS12) | _BV(5)); \
                                    TCCR1B |= _BV(CS10) | _BV(CS11) | _BV(WGM12);                           \
                                    OCR1A = a;                                                              \
                                    TIMSK1 |= _BV(OCIE1A);                                      \
                                    sei(); })
//--end--
//Changing Timer Resolution--start--
#define CHANGE_TIMER_RESOLUTION(a) ({ uint8_t sreg = SREG;\
                                      cli();\
                                      if(a == TIMER_BOTTOM_VALUE) \
                                        (OCR1A > a * 2) ? OCR1A = OCR1A / 2 : OCR1A = a; \
                                      if (a == TIMER_TOP_VALUE)\
                                        (OCR1A < a / 2) ? OCR1A = OCR1A * 2 : OCR1A = a;\
                                      SREG = sreg; })
//--end--

// TIMER 1 CTC ISR HANDLER
ISR(TIMER1_COMPA_vect)
{
  static uint8_t BitValue = 0;
  uint8_t sreg = SREG;
  cli();
  LED_COUNTER(BitValue);
  BitValue++;
  SREG = sreg;
}

//Pin change interupt for the buttons ISR Handler
ISR(PCINT2_vect)
{
  static int LastButton1State = HIGH;
  static int LastButton2State = HIGH;
  static uint32_t timeCheckSpeedUp = 0;
  static uint32_t timeCheckSlowDown = 0;
  uint8_t buttonSpeedUpStatus = (PIND & (1 << BUTTON_SPEED_UP));
  uint8_t buttonSlowDownStatus = (PIND & (1 << BUTTON_SLOW_DOWN));

  if (buttonSpeedUpStatus != LastButton1State)
  {
    LastButton1State = buttonSpeedUpStatus;
    if (millis() - timeCheckSpeedUp > 20)
    {
      timeCheckSpeedUp = millis();
      if (buttonSpeedUpStatus == LOW)
      {
        CHANGE_TIMER_RESOLUTION(TIMER_BOTTOM_VALUE);
        Serial.println(OCR1A);
      }
    }
  }

  if (buttonSlowDownStatus != LastButton2State)
  {
    LastButton2State = buttonSlowDownStatus;
    if (millis() - timeCheckSlowDown > 20)
    {
      timeCheckSlowDown = millis();
      if (buttonSlowDownStatus == LOW)
      {
        CHANGE_TIMER_RESOLUTION(TIMER_TOP_VALUE);
        Serial.println(OCR1A);
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  // BUTTONS PIN SETUP (INPUT_PULLUP RESISTOR - ON)
  DDRD &= ~BUTTONS_MASK;
  PORTD |= BUTTONS_MASK;

  // LEDS PIN SETUP (INIT STATE LOW)
  DDRB |= LEDS_MASK;
  PORTB &= ~LEDS_MASK;

  //BUTTONS PIN CHANGE INTERRUPT SETUP
  BUTTONS_INTERRUPT_SETUP;

  // TIMER 1 SETUP
  TIMER_COUNTER_1_SETUP(TIMER_TOP_VALUE);
}

void loop() {}