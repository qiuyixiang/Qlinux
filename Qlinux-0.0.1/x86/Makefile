# Makefile For X86 Architecture Related Component

# This File Describe Some Rules For Building X86 Architecture Depedent Component

SCRIPT_PATH	:=	../script

-include $(SCRIPT_PATH)/func.mk

.DEFAULT_GOAL 	:=	main

# Build Path for All Components
BUILD_PATH		:=	$(GLOBAL_BUILD)/x86
INCLUDE_X86		:=	$(INCLUDE_X86_ABS)

# Different Directory for different Modules
BOOT_DIR	:=	./boot
CPU_DIR		:=	./cpu

# All Small Individual Components
DEPENDENCIES	:=	boot.bin

.PHONY: main
main: $(DEPENDENCIES)

# Rules for building boot.o
boot.bin: $(BOOT_DIR)/boot.S
	$(call dir_check, $(BUILD_PATH))
	$(NASM) $(NASM_FLAGS) $< -o $(BUILD_PATH)/$@

