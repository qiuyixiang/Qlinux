# Makefile For Kernel Component

SCRIPT_PATH	:=	../script

-include $(SCRIPT_PATH)/func.mk

.DEFAULT_GOAL 	:=	main

# Define Build Path
BUILD_PATH			:=	$(GLOBAL_BUILD)/kernel
INCLUDE_RELATIVE	:=	../include

# All Depedencies Define Here
DEPENDENCIES	:=	main.o
.PHONY: main
main: $(DEPENDENCIES)

# Build For main.o
main.o: ./main.c
	$(call dir_check, $(BUILD_PATH))
	$(GCC) -c $(GCC_FLAGS) -I $(INCLUDE_RELATIVE) $< -o $(BUILD_PATH)/$@

