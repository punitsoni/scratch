//#include <avr/io.h>
//#include <util/delay.h>
#include "Arduino.h"

int main (void)
{
    /* arduino wiring init */
    init();

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    while(1);
#if 0
 /* set pin 5 of PORTB for output*/
 DDRB |= _BV(DDB5);

 while(1) {
  /* set pin 5 high to turn led on */
  PORTB |= _BV(PORTB5);
  _delay_ms(BLINK_DELAY_MS);

  /* set pin 5 low to turn led off */
  PORTB &= ~_BV(PORTB5);
  _delay_ms(BLINK_DELAY_MS);
 }
#endif
}
