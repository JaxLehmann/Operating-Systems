obj-m += hw1.o
# This specifies a loadable kernel object (.ko file) that should be built
# This tells the build system to compile lab2sies.o into lab2sies.ko
# .ko is a kernel object file

KDIR:=/lib/modules/$(shell uname -r)/build # Points to the kernel source directory for the currently running kernel
PWD:=$(shell pwd) # Stores current working directory where the module is located

all:
	make -C $(KDIR) M=$(PWD) modules
	# -C $(KDIR) switches the kernel source directory
	# M tells the kernel build system to compile the module in PWD
	# Modules - instructs the kernel build system to build a module
	
clean:
	make -C $(KDIR) M=$(PWD) clean
	# clean removes the compiled files ensuring a fresh build
