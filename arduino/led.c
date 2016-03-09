#include "Arduino.h"

/* default initialization steps for arduino */
void arduino_init(void)
{
    init();
#ifdef USBCON
	USBDevice.attach();
#endif
}

int main(void)
{
    arduino_init();
    pinMode(13, OUTPUT);
    while (1) {
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(1500);
    }
}
