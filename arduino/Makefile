SERIAL_PORT = /dev/tty.usbserial-A702PYFC

PROJECT = led

OBJS = led.o

IDE_PATH = $(PWD)/arduino-1.5

CC = avr-gcc
LD = avr-gcc
OBJCPY = avr-objcopy

CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p
LDFLAGS = -mmcu=atmega328p

$(PROJECT).hex: $(PROJECT)
	$(OBJCPY) -O ihex -R .eeprom $(PROJECT) $(PROJECT).hex

$(PROJECT): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROJECT)

upload: $(PROJECT).hex
	avrdude -F -V -c arduino -p ATMEGA328P -P $(SERIAL_PORT) \
	 -b 57600 -U flash:w:$(PROJECT).hex

clean:
	rm -f $(OBJS) $(PROJECT) $(PROJECT).hex
