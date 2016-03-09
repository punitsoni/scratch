all: libarduino.a

include config.mk

ARD_CORE_PATH = $(ARD_SRC_PATH)/hardware/arduino/avr/cores/arduino

C_SRCS =  $(wildcard $(ARD_CORE_PATH)/*.c)
CXX_SRCS = $(wildcard $(ARD_CORE_PATH)/*.cpp)

OBJS = $(patsubst %.c,%.o,$(C_SRCS))
OBJS += $(patsubst %.cpp,%.o,$(CXX_SRCS))

CFLAGS = $(ARD_CFLAGS)
CXXFLAGS = $(ARD_CXXFLAGS)

libarduino.a: $(OBJS)
	$(AR) rcs libarduino.a $^
	@echo "[$@] DONE."

# remove build artifacts
clean:
	rm -f $(OBJS)
	rm -f libarduino.a
