# Main Makefile For Control Kernel Module
# Build The Most Important Pat of this Project
# Qlinux Kernel:

.DEFAULT_GOAL		:=	make_kernel


# Define Source File Path
BUILD_PATH			:=	../build/kernel
DEPEDENCIES_PATH	:=	../build/dep

# Define Header File Path
INCLUDE_PATH		:=	../include

# All Objects 
OBJECTS	:=	$(BUILD_PATH)/main.o 

# Search Depedent File
DEPEDENT_INCLUDE_DIR	:=	$(wildcard $(DEPEDENCIES_PATH)/*.d)


.PHONY: make_kernel 
# Main Target
make_kernel: $(OBJECTS)



# Build For Main Directory File
$(BUILD_PATH)/%.o: ./%.c
	$(call execute, $(GCC) $(GCC_FLAGS) -I $(INCLUDE_PATH) -c -MD -MF $(DEPEDENCIES_PATH)/$*.d $< -o $@)


-include $(DEPEDENT_INCLUDE_DIR)

define execute
$(if $(filter $(SILENT), 1), @$(1), $(1))
endef