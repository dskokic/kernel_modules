# Linux Kernel Modules

Linux kernel modules (LKM) extend the capabilities of Linux kernel. Kernel module could implement a filesystem driver, or hardware device driver, or something else. Kernel modules can be linked to linux kernel either statically or dynamically. 

Statically linked modules are linked to linux kernel during kernel compilation and are permanently (statically) integrated (linked) to linux kernel .

Kernel modules can be also integrated with (linked to) linux kernel dynamically, at the time when the linux kernel is already running. We say then that the module is dynamically loaded to kernel. After being loaded, linux kernel module becomes part of linux kernel as it was with static linking, except that it can also be unloaded, which is not the case with static kernel module. 

## Prerequisites

To be able to build linux kernel module, you need to install *linux kernel header* package:

Ubuntu: 			> `sudo apt install linux-headers-$(uname -r)`
Raspberry Pi:	> `sudo apt install raspberrypi-kernel-headers`

This command will install kernel header source files in directory `/usr/src/linux-headers-$(uname -r)` folder, and will create soft link to it, named `build` in `/lib/modules/$(uname -r)` folder.

For instance, if kernel version is 5.10.11-v7l+ , which you can get by executing command `uname -r`, then
soft link named `build` (`/lib/modules/5.10.11-v7l+/build`) will be created and will point to  `/usr/src/linux-headers-5.10.11-v7l+` folder.

You don't need to be root user to build LKM, but to be able to load LKM to kernel (with `insmod` or `modprobe` commands), or to unload it from the running kernel (with `rmmod` or `modprobe -r` commands) you need to be. This is usually accomplished by prefixing named command with `sudo` command (`sudo insmod`, ...).