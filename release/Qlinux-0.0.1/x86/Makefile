# Makefile For X86 Architecture Related Component

# This File Describe Some Rules For Building X86 Architecture Depedent Component

SCRIPT_PATH	:=	../script

-include $(SCRIPT_PATH)/func.mk

.DEFAULT_GOAL 	:=	main

# Build Path for All Components
BUILD_PATH			:=	$(GLOBAL_BUILD)/x86
INCLUDE_X86			:=	$(INCLUDE_X86_ABS)
INCLUDE_RELATIVE	:=	../include

# Different Directory for different Modules
BOOT_DIR	:=	./boot
CPU_DIR		:=	./cpu

# All Small Individual Components
DEPENDENCIES	:=	boot.bin loader.bin gdt.o

.PHONY: main
main: $(DEPENDENCIES)

# Rules for building boot.bin
boot.bin: $(BOOT_DIR)/boot.S $(BOOT_DIR)/bootloader.inc
	$(call dir_check, $(BUILD_PATH))
	$(NASM) $(NASM_FLAGS) -I$(BOOT_DIR) $< -o $(BUILD_PATH)/$@

# Rules for building loader.bin
loader.bin: $(BOOT_DIR)/loader.S $(BOOT_DIR)/bootloader.inc
	$(NASM) $(NASM_FLAGS) -I$(BOOT_DIR) $< -o $(BUILD_PATH)/$@

# Rules for building All object File
%.o: $(CPU_DIR)/%.c
	$(GCC) -c $(GCC_FLAGS) -I $(INCLUDE_RELATIVE) $< -o $(BUILD_PATH)/$@