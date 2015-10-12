TARGET = h_uio
KDIR = /lib/modules/$(shell uname -r)/build

obj-m += $(TARGET).o

$(TARGET)-objs := hello.o

all: module test

module:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf hello-test

test:
	$(CC) hello_test.c -o hello-test

