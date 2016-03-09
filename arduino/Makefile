PROJECT = led

C_SRCS = led.c

CXX_SRCS =

################################################################################
all: $(PROJECT).hex

include config.mk

OBJS = $(patsubst %.c,%.o,$(C_SRCS))
OBJS += $(patsubst %.cpp,%.o,$(CXX_SRCS))

CFLAGS = $(ARD_CFLAGS) -g -Wall

CXXFLAGS = $(ARD_CXXFLAGS) -g -Wall

LDFLAGS = $(ARD_LDFLAGS)

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -O ihex -R .eeprom $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(OBJS) libarduino.a
	$(LD) $(LDFLAGS) -o $(PROJECT).elf $(OBJS) libarduino.a
	@echo "-------- PROGRAM SIZE --------"
	@$(SIZE) -A $(PROJECT).elf
	@echo "------------------------------"


libarduino.a:
	make -f libarduino.mk

upload: $(PROJECT).hex
	avrdude -F -vv -c arduino -p ATMEGA328P -P $(SERIAL_PORT) \
	 -D -b 57600 -U flash:w:$(PROJECT).hex

clean:
	rm -f $(OBJS) $(PROJECT).elf $(PROJECT).hex

cleanlib: clean
	make -f libarduino.mk clean

cleanall: clean clean-src cleanlib
