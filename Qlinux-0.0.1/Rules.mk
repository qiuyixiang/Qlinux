# This Makefile Define All of the Build Tool Chain And File Path

# Define Global Path

CUR_DIR			=	$(CURDIR)

# General Purpose Directory Path
GLOBAL_INCLUDE	:=	$(CUR_DIR)/inclue
GLOBAL_BUILD	:=	$(CUR_DIR)/build
GLOBAL_SCRIPT	:=	$(CUR_DIR)/script

-include $(GLOBAL_SCRIPT)/func.mk

# Component Directory Path
GLOBAL_X86		:=	$(CUR_DIR)/x86
GLOBAL_KERNEL	:=	$(CUR_DIR)/kernel
GLOBAL_USER		:=	$(CUR_DIR)/user
GLOBAL_DRIVER	:=	$(CUR_DIR)/driver

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
ifndef TOOLCHAIN_PREFIX
	TOOLCHAIN_PREFIX 	:=		x86_64-elf-
endif

CXX			:=		$(TOOLCHAIN_PREFIX)gcc
AS			:=		$(TOOLCHAIN_PREFIX)as
LD			:=		$(TOOLCHAIN_PREFIX)ld
CPP			:=		$(TOOLCHAIN_PREFIX)gcc -E 
OBJDUMP		:=		$(TOOLCHAIN_PREFIX)objdump
OBJCOPY		:=		$(TOOLCHAIN_PREFIX)objcopy
QEMU		:=		qemu-system-x86_64
BOCHS		:=		bochs

export CXX AS LD CPP OBJCOPY OBJDUMP

# Switch Flags For Compilation
CPU_ARCH		:=	i686
BITS			:=	32
AS_SYNTAX		:=	intel

GCC_FLAGS		:=	
LD_FLAGS		:=	
AS_FLAGS		:=	-mmnemonic=$(AS_SYNTAX) -msyntax=$(AS_SYNTAX) --warn --$(BITS) -march=$(CPU_ARCH) -mtune=$(CPU_ARCH)


AS_FLAGS		+=	--gstabs

export GCC_FLAGS LD_FLAGS AS_FLAGS


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