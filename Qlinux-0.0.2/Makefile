# Main Makefile Which Control All Building Process For The Project 
# @Copyright Copyright (C) QIUYIXIANG
# date: 07-27-2024

# Using this Makefile Build, Emulate and Debugger the whole project
# Some Command-Line Options Specify Here:
#	- Command For Command T (Used for specify particular tool chain prefix)
#	- Command For Command S (Used to Silent the operation)
#	- Command for Command D (Used for debugger flags)

SCRIPT	:=	./script
CUR_DIR	:=	$(CURDIR)

-include $(SCRIPT)/Rules.mk

# Default Goal Just Show Info
.DEFAULT_GOAL	:=	info

# Modules Defined Here
MODULES	:=	arch kernel # lib user

# Define For Sub-Build Path
BUILD_ARCH			:=	$(BUILD_GLOBAL_PATH)/arch
BUILD_KERNEL		:=	$(BUILD_GLOBAL_PATH)/kernel
BUILD_LIB			:=	$(BUILD_GLOBAL_PATH)/lib
BUILD_USER			:=	$(BUILD_GLOBAL_PATH)/user
BUILD_DEPEDENCIES	:=	$(BUILD_GLOBAL_PATH)/dep

# Check For Building Path
$(BUILD_ARCH):
	$(call execute, mkdir -p $(BUILD_ARCH))
$(BUILD_KERNEL):
	$(call execute, mkdir -p $(BUILD_KERNEL))
$(BUILD_LIB):
	$(call execute, mkdir -p $(BUILD_LIB))
$(BUILD_USER):
	$(call execute, mkdir -p $(BUILD_USER))
$(BUILD_DEPEDENCIES):
	$(call execute, mkdir -p $(BUILD_DEPEDENCIES))

# Call Sub-Makefile To Manage Modules Separately
arch: $(BUILD_ARCH)
	$(call execute, $(MAKE) -C $(ARCH_GLOBAL_PATH))
kernel: $(BUILD_KERNEL)
	$(call execute, $(MAKE) -C $(KERNEL_GLOBAL_PATH))
lib: $(BUILD_LIB)
	$(call execute, $(MAKE) -C $(LIB_GLOBAL_PATH))
user: $(BUILD_USER)
	$(call execute, $(MAKE) -C $(USER_GLOBAL_PATH))

.PHONY : info all clean 
# Show Basic And Help Info
info:
	$(call print, "\n  Qlinux Makefile Project Management Tools")
	$(call print, "Usage:")
	$(call print, "\\t make all \\t\\t build project and generate IOS file")
	$(call print, "\\t make run \\t\\t run OS kernel in default emulator")
	$(call print, "\\t make clean \\t\\t Clean Generated Target file and directory")
	$(call print, "\\t make dbg \\t\\t Using qemu and GNU gdb remote debugger")
	$(call print, "Argument: ")
	$(call print, "\\t D= \\t\\t\\t Specify Tool Chain (i686-elf- by default)")
	$(call print, "\\t S= \\t\\t\\t Build Silently (1 by default)")
	$(call print, "\\t D= \\t\\t\\t Add Debugger Information to the file (0 by default)")
	$(call print, "Copyright '(C)' QIUYIXIANG  Qlinux Version is still in progress !")


# Main Build Receipt all
all: $(BUILD_DEPEDENCIES) $(MODULES)
	

clean:
	$(call execute, rm -rf $(BUILD_GLOBAL_PATH))