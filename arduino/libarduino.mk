include config.mk

ARD_CORE_PATH = $(ARD_SRC_PATH)/hardware/arduino/avr/cores/arduino

C_SRCS =  $(wildcard $(ARD_CORE_PATH)/*.c)
CXX_SRCS = $(wildcard $(ARD_CORE_PATH)/*.cpp)


CXX_SRCS := $(filter-out $(ARD_CORE_PATH)/main.cpp, $(CXX_SRCS))

OBJS = $(patsubst %.c,%.o,$(C_SRCS))
OBJS += $(patsubst %.cpp,%.o,$(CXX_SRCS))

$(info OBJS = $(OBJS))

CFLAGS = $(ARD_CFLAGS)
CXXFLAGS = $(ARD_CXXFLAGS)

all: libarduino.a

libarduino.a: $(OBJS)
	$(AR) rcs libarduino.a $(OBJS)

# remove build artifacts
clean:
	rm -f $(OBJS)
	rm -f libarduino.a
