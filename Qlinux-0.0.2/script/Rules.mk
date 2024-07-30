# Makefile Rules And General Functions For The Project 
# @Copyright Copyright (C) QIUYIXIANG
# date: 07-27-2024
# This Makefile Rules All used for Main Makefile Except some Special Global Tools
# These Tools will export to the sub-makefile for more utility

# Definition for Global Tools Chain
ARCH		:=		i386
OS_NAME		:=		Qlinux
export ARCH OS_NAME

# Command For T (Used for specify particular tool chain prefix)
ifndef T
TOOLCHAIN_PREFIX	:=	i686-elf-
else
TOOLCHAIN_PREFIX	:=	$(T)
endif
# Command For Command S (Used to Silent the operation)
ifndef S
SILENT				:=	1
else
SILENT				:=	$(S)
endif
# Options for Command D (Used for debugger flags)
ifndef D
DEBUGGER			:=	0
else
DEBUGGER			:=	$(D)
endif

export SILENT
export DEBUGGER

# Definition For Directory Path
# Main Path Entry (Which Means these paths appear in the root directory)
INCLUDE_GLOBAL_PATH		:=	./include
BUILD_GLOBAL_PATH		:=	./build
KERNEL_GLOBAL_PATH		:=	./kernel
ARCH_GLOBAL_PATH		:=	./arch
LIB_GLOBAL_PATH			:=	./lib
SCRIPT_GLOBAL_PATH		:=	./script
USER_GLOBAL_PATH		:=  ./user
CONFIG_GLOBAL_PATH		:=	./config
ISO_GLOBAL_PATH			:=	./iso

# Definition For GNU Tool Chain
GCC			:=		$(TOOLCHAIN_PREFIX)gcc
AS			:=		$(TOOLCHAIN_PREFIX)as
LD			:=		$(TOOLCHAIN_PREFIX)ld
OBJDUMP		:=		$(TOOLCHAIN_PREFIX)objdump
OBJCOPY		:=		$(TOOLCHAIN_PREFIX)objcopy
# Export Tool Chain Name for global environment
export GCC
export AS
export OBJDUMP
export OBJCOPY

# Other Tools
GRUB_PREFIX		:=	grub-
GRUB_FILE		:= 	$(GRUB_PREFIX)file
GRUB_MKRESCUE	:=	$(GRUB_PREFIX)mkrescue 
BOCHS			:=	bochs
QEMU			:=	qemu-system-$(ARCH)

# GNU Compilation Flags
ifeq ($(DEBUGGER),1)
GCC_FLAGS		:=	-O0
else
GCC_FLAGS		:=	-O2
endif

GCC_FLAGS		+=	-Wall -Wextra -Wshadow
GCC_FLAGS		+=	-std=gnu99 -m32
GCC_FLAGS		+=	-fno-builtin -fno-builtin-function -ffreestanding
GCC_FLAGS		+=	-nostdlib -nolibc -nostdinc
GCC_MACRO_FLAGS	:=	

# LD Linker Flags
LD_FLAGS		:=	-m elf_$(ARCH) -EL
LD_FLAGS		+=	-nostdlib
LD_FLAGS		+=	-T $(SCRIPT_GLOBAL_PATH)/linker.ld

# AS Assembler Flags
AS_FLAGS		:=	--warn
AS_FLAGS		+=	--32
AS_FLAGS		+=	-march=$(ARCH) -mtune=$(ARCH) 
AS_FLAGS		+=	-msyntax=att -mmnemonic=att

ifeq ($(DEBUGGER),1)
GCC_FLAGS		+=	-g
AS_FLAGS		+=	-D --gstabs
endif

##### Configuration For GNU GCC Macros

# MultiBoot Version Configuration Macro
MULTIBOOT_V1		:=	1
MULTIBOOT_V2		:=	2
MULTIBOOT_VERSION	:=	$(MULTIBOOT_V1)

MULTIBOOT			:=	__MULTIBOOT_VERSION__
GCC_MACRO_FLAGS		+=	-D $(MULTIBOOT)=$(MULTIBOOT_VERSION)

 
GCC_FLAGS		+=	$(GCC_MACRO_FLAGS)
export GCC_FLAGS
export LD_FLAGS
export AS_FLAGS

# define some helper function
define execute
$(if $(filter $(SILENT), 1), @$(1), $(1))
endef

define print
	@echo $1
endef
