SERIAL_PORT = /dev/tty.usbserial-A702PYFC

# arduino variant for nano board
ARD_BOARD_VARIANT = eightanaloginputs
ARD_SRC_PATH = arduino-src

CC = avr-gcc
CXX = avr-g++
AR = avr-ar
LD = avr-ld
OBJCOPY = avr-objcopy
SIZE = avr-size

ARD_CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p
ARD_CFLAGS += -I $(ARD_SRC_PATH)/hardware/arduino/avr/cores/arduino
ARD_CFLAGS += -I $(ARD_SRC_PATH)/hardware/arduino/avr/variants/$(ARD_BOARD_VARIANT)

ARD_CXXFLAGS = $(ARD_CFLAGS)

ARD_LDFLAGS =

$(ARD_SRC_PATH):
	mkdir -p arduino-src
	@echo ">> fetching arduino 1.5.x sources..."
	wget https://github.com/arduino/Arduino/archive/ide-1.5.x.zip
	unzip ide-1.5.x.zip
	mv Arduino-ide-1.5.x $(ARD_SRC_PATH)
	rm -f ide-1.5.x.zip
	@echo ">> fetch complete."

# remove fetched sources
clean-src:
	rm -rf arduino-src/
