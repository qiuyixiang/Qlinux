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
CONFIG	:=	config
ISO		:=	iso

# Define For Sub-Build Path
BUILD_ARCH			:=	$(BUILD_GLOBAL_PATH)/arch
BUILD_KERNEL		:=	$(BUILD_GLOBAL_PATH)/kernel
BUILD_LIB			:=	$(BUILD_GLOBAL_PATH)/lib
BUILD_USER			:=	$(BUILD_GLOBAL_PATH)/user
BUILD_DEPEDENCIES	:=	$(BUILD_GLOBAL_PATH)/dep

OBJS				:=	$(BUILD_ARCH)/boot.o 	\
						$(BUILD_KERNEL)/main.o 	\
						$(BUILD_ARCH)/vga.o		\
						$(BUILD_ARCH)/gdt.o

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

.PHONY : info all clean config iso run dbg run_bin
# Show Basic And Help Info
info:
	$(call print, "\n  Qlinux Makefile Project Management Tools")
	$(call print, "Usage:")
	$(call print, "\\t make all \\t\\t build all depedent files and link them")
	$(call print, "\\t make iso \\t\\t build the final ISO Image File ")
	$(call print, "\\t make run \\t\\t run OS kernel in default emulator (ISO Image)")
	$(call print, "\\t make run_bin \\t\\t run OS kernel in raw mode (binary ELF file not ISO Image)")
	$(call print, "\\t make clean \\t\\t Clean Generated Target file and directory")
	$(call print, "\\t make dbg \\t\\t Using qemu and GNU gdb remote debugger(No Graphic)")
	$(call print, "Argument: ")
	$(call print, "\\t D= \\t\\t\\t Specify Tool Chain (i686-elf- by default)")
	$(call print, "\\t S= \\t\\t\\t Build Silently (1 by default)")
	$(call print, "\\t D= \\t\\t\\t Add Debugger Information to the file (0 by default)")
	$(call print, "Copyright '(C)' QIUYIXIANG  Qlinux Version is still in progress !")

# Show Project Configuration
config:
	$(call print, "Project Build Configuration For Qlinux")
	$(call print, "Building Target For Qlinux : $(ARCH)")
	$(call print, "Work Directory : $(CUR_DIR)")
	$(call print, "GNU Tool chain : $(GCC) ")
	$(call print, "Using GNU GRUB Multiboot Version : $(MULTIBOOT_VERSION)")
	$(call print, "[Makefile Configure] T=$(TOOLCHAIN_PREFIX)")
	$(call print, "[Makefile Configure] S=$(SILENT)")
	$(call print, "[Makefile Configure] D=$(DEBUGGER)")

# Build ISO Image File which must be a single one target apart from @all 
iso:
# Create Grub ISO Image Directory
	$(call execute, mkdir -p $(ISO_GLOBAL_PATH)/boot/grub)
	$(call execute, cp $(CONFIG_GLOBAL_PATH)/grub.cfg $(ISO_GLOBAL_PATH)/boot/grub/grub.cfg)
	$(call execute, cp $(BUILD_GLOBAL_PATH)/Qlinux.bin $(ISO_GLOBAL_PATH)/boot/Qlinux.bin)
	$(call execute, $(GRUB_MKRESCUE) $(ISO_GLOBAL_PATH) -o $(ISO_GLOBAL_PATH)/$(OS_NAME).iso)
	$(call print, "Building ISO Image File in : $(ISO_GLOBAL_PATH)/$(OS_NAME).iso")

# Link Objects
_link: $(OBJECTS)
	$(call execute, $(LD) $(LD_FLAGS) $(OBJS) -o $(BUILD_GLOBAL_PATH)/$(OS_NAME).bin)

# Main Build Receipt all
all: $(BUILD_DEPEDENCIES) $(MODULES)
ifeq ($(SILENT), 0)
	$(MAKE) $(CONFIG)
endif
	$(call execute, $(MAKE) _link)
	@if $(GRUB_FILE) --is-x86-multiboot $(BUILD_GLOBAL_PATH)/$(OS_NAME).bin; then \
		echo "[CONFIRM] Multiboot compatible file confirmed !"; \
	else \
		echo "ERROR: The file is not Multiboot compatible file !"; \
		exit -1; \
	fi
	$(call print, "[BUILD] Building All Depedent Files Successfully \\nNow you can use command <make iso> to build  \
		an Qlinux ISO Image File !")

# Run Emulator Using Bochs
run:
	$(BOCHS) -f $(CONFIG_GLOBAL_PATH)/bochsrc_cdrom.cfg -q

# Run Qemu Emulator in Raw Binary Mode Not ISO Image 
run_bin:
	$(QEMU) -kernel $(BUILD_GLOBAL_PATH)/$(OS_NAME).bin
# Using Debugger Mode Run the kernel Qemu with GNU GDB
dbg:
	$(QEMU) -cdrom  $(ISO_GLOBAL_PATH)/$(OS_NAME).iso

# Clean Generated Target File
clean:
	$(call execute, rm -rf $(BUILD_GLOBAL_PATH) $(ISO_GLOBAL_PATH))
