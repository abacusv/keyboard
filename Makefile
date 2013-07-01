obj-m := keyDevice.o

KERNEL_SRC=/usr/src/linux

compile_keyModule: keyDevice.c
	make -C ${KERNEL_SRC} M=${PWD} modules

compile_app: read_device.c
	gcc -o read_device read_device.c


clean:
	rm -f keyDevice.ko keyDevice.mod.o keyDevice.o keyDevice.mod.c modules.order Module.symvers read_device 

all: compile_keyModule compile_app

