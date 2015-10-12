TARGET = h_uio
KDIR = /lib/modules/$(shell uname -r)/build

obj-m += $(TARGET).o

$(TARGET)-objs := hello.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
