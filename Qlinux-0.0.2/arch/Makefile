# This Makefile Used To Control Archtecture Related Files
# Current Support Architecture : 
#	- IA-32 i386

.DEFAULT_GOAL 	:=	make_arch

##### Architecture Related Source File Path
# Machine Architecture --
# May Be Supported Architecture i386 i686 x86_64

# Source File Path for i386
SRC_I386		:=	./i386
SRC_I386_BOOT	:=	$(SRC_I386)/boot
SRC_I386_CPU	:=	$(SRC_I386)/cpu

# Source File Path For x86_64
# Reversed Name Space
SRC_X86_64		:=	./x86_64

BUILD_PATH				:=	../build/arch
DEPEDENCIES_PATH		:=	../build/dep
INCLUDE_PATH			:=	../include

# Source File Path For Monitor
SRC_MONITOR				:=	./monitor

###### Objects File List
# Objects File List Need To Build
OBJECTS			:=		$(BUILD_PATH)/vga.o

DEPEDENT_INCLUDE_DIR	:=	$(wildcard $(DEPEDENCIES_PATH)/*.d)


# Special File For i386 Architecture
ifeq ($(ARCH), i386)
OBJECTS			+=	$(BUILD_PATH)/boot.o
endif

# Special File For X86_64 Architecture
ifeq ($(ARCH), x86_64)
OBJECTS			+=	
endif 

### Auxiliary GNU GCC Flags
GCC_INCLUDE_FLAGS	:= -I $(INCLUDE_PATH)

##### Build Related Targets
.PHONY: make_arch 
make_arch: $(OBJECTS)

# Build For i386 Boot
$(BUILD_PATH)/%.o:$(SRC_I386_BOOT)/%.S
	$(call execute, $(GCC) $(GCC_FLAGS) -c $(GCC_INCLUDE_FLAGS) -MD -MF $(DEPEDENCIES_PATH)/$*.d  $< -o $@)

# Build For Monitor
$(BUILD_PATH)/%.o:$(SRC_MONITOR)/%.c
	$(call execute, $(GCC) $(GCC_FLAGS) -c $(GCC_INCLUDE_FLAGS) -MD -MF $(DEPEDENCIES_PATH)/$*.d $< -o $@)

-include $(DEPEDENT_INCLUDE_DIR)

define execute
$(if $(filter $(SILENT), 1), @$(1), $(1))
endef