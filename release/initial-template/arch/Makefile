# This Makefile Used To Control Archtecture Related Files
# Current Support Architecture : 
#	- IA-32 i386

.DEFAULT_GOAL 	:=	make_arch

# May Be Supported Architecture
# Source File Path
SRC_I386		:=	./i386
SRC_BOOT		:=	$(SRC_I386)/boot
SRC_X86_64		:=	./x86_64

BUILD_PATH				:=	../build/arch
DEPEDENCIES_PATH		:=	../build/dep
INCLUDE_PATH			:=	../include

# Objects File Need To Build
OBJECTS			:=	
DEPEDENT_INCLUDE_DIR	:=	$(wildcard $(DEPEDENCIES_PATH)/*.d)


# Special File For i386 Architecture
ifeq ($(ARCH), i386)
OBJECTS			+=	$(BUILD_PATH)/boot.o
endif

# Special File For X86_64 Architecture
ifeq ($(ARCH), x86_64)
OBJECTS			+=	
endif 

.PHONY: make_arch 
make_arch: $(OBJECTS)

# Build For Boot
$(BUILD_PATH)/%.o:$(SRC_BOOT)/%.S
	$(call execute, $(GCC) $(GCC_FLAGS) -c -I $(INCLUDE_PATH) -MD -MF $(DEPEDENCIES_PATH)/$*.d  $< -o $@)


-include $(DEPEDENT_INCLUDE_DIR)

define execute
$(if $(filter $(SILENT), 1), @$(1), $(1))
endef