PROJECT = led

C_SRCS = led.o

CXX_SRCS =

################################################################################
all: $(PROJECT).hex

include config.mk

OBJS = $(patsubst %.c,%.o,$(C_SRCS))
OBJS += $(patsubst %.cpp,%.o,$(CXX_SRCS))

CFLAGS = $(ARD_CFLAGS)
LDFLAGS = $(ARD_LDFLAGS)

$(PROJECT).hex: $(PROJECT)
	$(OBJCOPY) -O ihex -R .eeprom $(PROJECT) $(PROJECT).hex

$(PROJECT): $(OBJS) libarduino.a
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROJECT) libarduino.a

libarduino.a:
	make -f libarduino.mk

upload: $(PROJECT).hex
	avrdude -F -V -c arduino -p ATMEGA328P -P $(SERIAL_PORT) \
	 -b 57600 -U flash:w:$(PROJECT).hex

clean:
	rm -f $(OBJS) $(PROJECT) $(PROJECT).hex

cleanlib: clean
	make -f libarduino.mk clean

cleanall: clean clean-src cleanlib
