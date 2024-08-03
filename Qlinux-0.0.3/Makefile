# Copyright (C) QIUYIXING

# Date 08/02/2024
# Main Makefile For Qlinux Using GNU Make

# Path Declaration
CUR_DIR			:=	$(CURDIR)
CONFIG_DIR		:=	$(CUR_DIR)/config
INCLUDE_DIR		:=	./include
SRC_DIR			:=	./src
BUILD_DIR		:=	./build
SCRIPT_DIR		:=	./script
ISO_DIR			:=	./iso
DEPDENT_DIR		:=	$(BUILD_DIR)/dep

-include $(CONFIG_DIR)/config.mk

ARCH_MAIN		:=	$(SRC_DIR)/arch
ARCH_DIR		:=	$(ARCH_MAIN)/$(ARCH)
KERNLE_DIR		:=	$(BUILD_DIR)

KERNEL_LINK		:=	$(OS_NAME).bin
# Binary Kernel Name and Position
KERNEL			:=	$(KERNLE_DIR)/$(KERNEL_LINK)

# Postfix Declaration
C_POSTFIX		:=	c
ASM_POSTFIX		:=	S
CPP_POSTFIX		:=	cpp
OBJ_POSFIX		:=	o 

POSTFIX_LIST	:=	$(C_POSTFIX) 	\
					$(ASM_POSTFIX)	\
					$(CPP_POSTFIX)	

ALL_TARGETS_LIST	:=	$(DEPDENT_DIR) $(OBJECTS_LIST) $(KERNEL)
DEPEDENCIES_LIST	:=	$(wildcard $(DEPDENT_DIR)/*.d)

# Source File List
SOURCE_LIST		:=	$(shell find $(SRC_DIR) -name "*[$(POSTFIX_LIST)]" -type f ! -path "$(ARCH_MAIN)/*")
SOURCE_LIST		+=	$(shell find $(ARCH_DIR) -type f -name "*[$(POSTFIX_LIST)]")

# Object File List
OBJECTS_LIST	=	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.c.o, $(SOURCE_LIST))
OBJECTS_LIST	:=	$(patsubst $(SRC_DIR)/%.S, $(BUILD_DIR)/%.S.o, $(OBJECTS_LIST))
OBJECTS_LIST	:=	$(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.cpp.o, $(OBJECTS_LIST))

# Build Rules For All Objects File
$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
ifeq ($(SILENT), 1)
	$(call print, "+ CC \\t\\t $@")
endif
	$(call execute, $(call check_dir, $(dir $@)))
	$(call execute, $(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) -MD -MF $(DEPDENT_DIR)/$(basename $(notdir $@)).d -c $< -o $@)
	
$(BUILD_DIR)/%.S.o: $(SRC_DIR)/%.S
ifeq ($(SILENT), 1)
	$(call print, "+ AS \\t\\t $@")
endif
	$(call execute, $(call check_dir, $(dir $@)))
	$(call execute, $(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) -MD -MF $(DEPDENT_DIR)/$(basename $(notdir $@)).d -c $< -o $@)

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(error Doesn't Support For Compile C++ Source File Now !)
ifeq ($(SILENT), 1)
	$(call print, "+ CXX \\t\\t $@")
endif
	$(call execute, $(call check_dir, $(dir $@)))

$(DEPDENT_DIR):
	$(call execute, $(call check_dir, $(DEPDENT_DIR)))

$(KERNEL): $(OBJECTS_LIST)
	$(call execute, $(LD) $(LD_FLAGS) -T $(SCRIPT_DIR)/linker.ld $^ -o $@)
ifeq ($(SILENT), 1)
	$(call print, "+ LD \\t\\t $@")
endif

# Build Receipts
.DEFAULT_GOAL	:=		info
.PHONY:	all clean run info

# The Argument Option will be abandoned after the support for Kconfig
info:
	$(call print, "\\nMakefile For Build Qlinux ")
	$(call print, "Usage:")
	$(call print, "\\t make all \\t\\t build all binary file")
	$(call print, "\\t make iso \\t\\t build ISO Image file ")
	$(call print, "\\t make run \\t\\t run OS in emulator")
	$(call print, "\\t make clean \\t\\t clean all targets")
	$(call print, "Argument:")
	$(call print, "\\t ARCH \\t\\t\\t Specify target Architecture")
	$(call print, "\\t D \\t\\t\\t Debugger Information")
	$(call print, "\\t S \\t\\t\\t Silent Build")
	$(call print, "\\t E \\t\\t\\t Specify Emulator")
	$(call print, "\\t T \\t\\t\\t Specify Toolchain")
	$(call print, "Copyright (C) QIUYIXIANG ")
   	

all: $(ALL_TARGETS_LIST)
	@:

iso: $(KERNEL)
	@if $(GRUB_FILE) $(GRUB_FILE_F) $(KERNEL); then 	\
		echo "MultiBoot Confirmed !";					\
	else												\
		echo "Not a MultiBoot Compitable File !"; 		\
		exit -1;										\
	fi
	$(call execute, mkdir -p $(ISO_DIR)/boot/grub)
	$(call execute, cp $(KERNEL) $(ISO_DIR)/boot/)
	$(call execute, cp $(CONFIG_DIR)/grub.cfg $(ISO_DIR)/boot/grub/)
	$(call execute, $(GRUB_MKRESCUE) $(ISO_DIR) -o $(ISO_DIR)/$(OS_NAME).iso)
	$(call print, "+ Create ISO Image FIle : $(ISO_DIR)/$(OS_NAME).iso")

clean:
	$(call execute, rm -rf $(BUILD_DIR) $(ISO_DIR))

run:
	$(call execute, $(BOCHS) -f $(CONFIG_DIR)/bochs_cdrom.cfg -q)

# This target make no sense just for git push
DATE :=	$(shell date)
git:
	@git add .
	@git commit -m "$(DATE)"
	@git push

-include $(DEPEDENCIES_LIST) 