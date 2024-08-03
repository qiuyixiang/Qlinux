# Copyright (C) QIUYIXING

# Date 08/02/2024
# Tools Configure For Qlinux

# This Makefile Is Position Indepedent !

# Toolchain : Specify The Build ToolChain
ifndef T
TOOLCHAIN_PREFIX	:=	i686-elf-
else
TOOLCHAIN_PREFIX	:=	$(T)
endif
# Debugger : Specify Whether Include Some Debugger Information
ifndef D
DEBUG				:=	0
else 
DEBUG				:=	$(D)
endif
# Emulator : Specify The Default Emulator
ifndef E
_EMULATOR			:=	bochs
else
_EMULATOR			:=	$(E)
endif
# Architecture : Specify The Target Architecture
ifndef ARCH
ARCH				:=	i386
endif
# Silent : Don't Show Compilation Information
ifndef S
SILENT				:=	1
else
SILENT				:= 	$(S)
endif 

CPU			:=		$(ARCH)
OS_NAME		:=		Qlinux

# Definition For tool chain
CC			:=		$(TOOLCHAIN_PREFIX)gcc
CPP			:=		$(TOOLCHAIN_PREFIX)c++
CXX			:=		$(TOOLCHAIN_PREFIX)gcc -E
AS			:=		$(TOOLCHAIN_PREFIX)as
LD			:=		$(TOOLCHAIN_PREFIX)ld
OBJDUMP		:=		$(TOOLCHAIN_PREFIX)objdump
OBJCOPY		:=		$(TOOLCHAIN_PREFIX)objcopy
EMULATOR	:=		$(EMULATOR)
BOCHS		:=		bochs
QEMU		:=		qemu-system-$(CPU)
GRUB		:=		grub-

GRUB_FILE		:=		$(GRUB)file
GRUB_MKRESCUE	:=		$(GRUB)mkrescue

GRUB_FILE_F		:=	


# GCC CC Flags
CC_FLAGS		:=	-std=gnu99
CC_FLAGS		+=	-m32
CC_FLAGS		+=	-nostdlib -nostdinc -nolibc -ffreestanding
CC_FLAGS		+=	-fno-builtin  -fno-builtin-function -Waddress
CC_FLAGS		+=	-Wall -Wextra -Wshadow

ifeq ($(DEBUG), 1)
CC_FLAGS		+=	-O0
else
CC_FLAGS		+=  -O2
endif 

ifeq ($(DEBUG), 1)
CC_FLAGS		+=	-g -gstabs
endif  

# Definition For GNU GCC Macros
# Multiboot Macro
MULTI_BOOT1			:=		1
MULTI_BOOT2			:=		2
MACRO_MULTIBOOT		:=		$(MULTI_BOOT1)
MACROS_MULTIBOOT	:=		-D __CXX_MULTIBOOT__=$(MACRO_MULTIBOOT)
# Architecture Macro
MACRO_ARCH			:=		-D __CXX_ARCH__=$(ARCH)

# Hardware Driver Macro
DISPLAY_DRIVER		:=		__CXX_DISPLAY_VGA__
MACRO_DISPLAY		:=		-D $(__CXX_DISPLAY_VGA__)=1


CC_MACROS			:=		$(MACROS_MULTIBOOT) \
							$(MACRO_ARCH)


CC_FLAGS			+=		$(CC_MACROS)


# GCC AS Flags
AS_FLAGS		:=	
AS_FLAGS		+=	--32
AS_FLAGS		+=	-mtune=$(CPU) -march=$(CPU)
AS_FLAGS		+=	--warn
AS_FLAGS		+=	-msyntax=att -mmnemonic=att


ifeq ($(DEBUG), 1)
AS_FLAGS		+=	--gstabs -g
endif 

ifeq ($(MACRO_MULTIBOOT), 1)
GRUB_FILE_F		+=	--is-x86-multiboot
else
GRUB_FILE_F		+=	--is-x86-multiboot2
endif 


# GCC LD Flags
LD_FLAGS		:=	-m elf_$(CPU)
LD_FLAGS		+=	-EL 
LD_FLAGS		+=	-nostdlib


# Reversed For Further Use
export CC_FLAGS
export AS_FLAGS
export LD_FLAGS
export CC AS CPP CXX LD 
export ARCH CPU OS_NAME

# Function Definition
define check_dir
	if [ ! -d $(1) ]; then		\
		mkdir -p $(1);			\
	fi
endef

# Just A Wrapper Function 
define execute
$(if $(filter $(SILENT), 1), @$(1), $(1))
endef
	
define print
	@echo $(1)
endef