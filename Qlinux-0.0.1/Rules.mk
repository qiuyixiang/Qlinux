# This Makefile Define All of the Build Tool Chain And File Path

# Define Global Path

CUR_DIR			:=	$(CURDIR)
KERNEL_VERSION	:=	0.0.1

# General Purpose Directory Path
GLOBAL_INCLUDE	:=	$(CUR_DIR)/inclue
GLOBAL_BUILD	:=	$(CUR_DIR)/build
GLOBAL_SCRIPT	:=	$(CUR_DIR)/script
GLOBAL_CONFIG	:=	$(CUR_DIR)/config

-include $(GLOBAL_SCRIPT)/func.mk
export GLOBAL_BUILD

# Component Directory Path
GLOBAL_X86		:=	$(CUR_DIR)/x86
GLOBAL_KERNEL	:=	$(CUR_DIR)/kernel
GLOBAL_USER		:=	$(CUR_DIR)/user
GLOBAL_DRIVER	:=	$(CUR_DIR)/driver

DISK_PATH		:=	$(GLOBAL_BUILD)
DISK_NAME		:=	Qlinux

# Absolute Include Path (Header File)
INCLUDE_ABS			:=	$(GLOBAL_INCLUDE)
INCLUDE_KERNEL_ABS	:=	$(INCLUDE_ABS)/kernel
INCLUDE_X86_ABS		:=	$(INCLUDE_ABS)/x86
INCLUDE_USER_ABS	:=	$(INCLUDE_ABS)/user
INCLUDE_DRIVER_ABS	:=	$(INCLUDE_ABS)/driver

# Export Public Global Variables For Sub-Makefile 
export INCLUDE_ABS
export INCLUDE_KERNEL_ABS
export INCLUDE_X86_ABS
export INCLUDE_USER_ABS
export INCLUDE_DRIVER_ABS

# There are four main components in this project
GLOBAL_COMPONENT_LIST	:=	user kernel driver x86

# Path Depedent Variables For Tools
ifdef T
	TOOLCHAIN_PREFIX 	:=	$(T)
else
	TOOLCHAIN_PREFIX	:=	x86_64-elf-
endif

GCC			:=		$(TOOLCHAIN_PREFIX)gcc
AS			:=		$(TOOLCHAIN_PREFIX)as
LD			:=		$(TOOLCHAIN_PREFIX)ld
CPP			:=		$(TOOLCHAIN_PREFIX)gcc -E 
OBJDUMP		:=		$(TOOLCHAIN_PREFIX)objdump
OBJCOPY		:=		$(TOOLCHAIN_PREFIX)objcopy
NASM		:=		nasm
QEMU		:=		qemu-system-x86_64
BOCHS		:=		bochs
BXIMAGE		:=		bximage
GDB			:=		gdb
DD			:=		dd

ifndef E
	EMULATOR	:=	$(BOCHS)
else
	EMULATOR	:=	$(E)
endif

export GCC AS LD CPP OBJCOPY OBJDUMP NASM

# Switch Flags For Compilation
CPU_ARCH		:=	i686
BITS			:=	32
AS_SYNTAX		:=	intel
HARD_DISK_SIZE	:=	64M

BOOT_SECTOR_SIZE	:=	1
LOADER_SECTOR_SIZE	:=	2
KERNEL_SECTOR_SIZE	:=	32

KERNEL_MAIN_ENTRY	:=	__kernel_main
KERNEL_START_ADDR	:=	0x00100000

# Flags For GNU GCC Compiler Collection
GCC_FLAGS		:=	-std=gnu11 -fno-builtin -ffreestanding -O0 -m32 -nostdinc
GCC_WARNING		:=	-Wextra  -Wall
GCC_FLAGS 		+=	$(GCC_WARNING) 

LD_FLAGS		:=	-nostdlib -m elf_i386 -e $(KERNEL_MAIN_ENTRY) -Ttext=$(KERNEL_START_ADDR) -EL -T $(GLOBAL_SCRIPT)/linker.ld
NASM_FLAGS		:=	-f bin -Wall
AS_FLAGS		:=	-mmnemonic=$(AS_SYNTAX) -msyntax=$(AS_SYNTAX) --warn --$(BITS) -march=$(CPU_ARCH) -mtune=$(CPU_ARCH)
BOCHS_FLAGS		:=	-f $(GLOBAL_CONFIG)/bochsrc -q
BXIMAGE_FLAGS	:=	-func=create -hd=$(HARD_DISK_SIZE) -imgmode=flat -sectsize=512 -q $(DISK_PATH)/$(DISK_NAME).hd 

export GCC_FLAGS 
export LD_FLAGS
export AS_FLAGS

#### Optional Flags
# The DEBUGGER equals to zero by default
DEBUGGER ?= 0

# SILENT Flags used to control Build Information -S (S=1) by default
ifdef S
	SILENT	:=	$(S)
else
	SILENT	:=	1
endif

# Switch For Debugger if Defined DEBUGGER Flag it will add some debugger info to the compilation process
# Debugger Flags -D	(D=0) by default
ifdef D
	DEBUGGER 	:= $(D)
else
	DEBUGGER	:=	0
endif 

ifeq ($(DEBUGGER), 1)
AS_FLAGS		+=	--gstabs
GCC_FLAGS		+=	-g
endif

# This Function only used to test path consistency
define _path_check
	$(call print, "Debugger Checker for Absolute Path : ")
	$(call print, "\\t Debugger -- Global Include Path : $(GLOBAL_INCLUDE)")
	$(call print, "\\t Debugger -- Global Build Path : $(GLOBAL_BUILD)")
	$(call print, "\\t Debugger -- Global Kernel Component Path : $(GLOBAL_KERNEL)")
	$(call print, "\\t Debugger -- Global User Component Path : $(GLOBAL_USER)")
	$(call print, "\\t Debugger -- Global X86 Component Path : $(GLOBAL_X86)")
	$(call print, "\\t Debugger -- Global Driver Component Path : $(GLOBAL_DRIVER)")
endef