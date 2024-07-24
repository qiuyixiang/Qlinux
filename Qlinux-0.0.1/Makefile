
# This Makefile Control All of the project

# Copyright : @QIUYIXIANG
# Create on : 2023-07-23

# Include Rules Makefile
-include $(CURDIR)/Rules.mk

# Define All Depedencies 
DEPENDENCIES	:=	$(GLOBAL_COMPONENT_LIST)

### Main Target
# Main Target for building this whole project !
.DEFAULT_GOAL	:=	info
.PHONY: info 
info:
	@$(call print, "\\n Makefile for Qlinux-$(KERNEL_VERSION) There are some depedent build \
		toolchains and make sure you install them !")
	@$(call print, "Usage:")
	@$(call print, "\\t make all    \\t\\tbuild kernel")
	@$(call print, "\\t make run    \\t\\tcalling bochs as default emulator")
	@$(call print, "\\t make dbg    \\t\\tdebugger mode using GDB and qemu \\n")
	@$(call print, "Macros used to control compilation: ")
	@$(call print, "\\t D=1 \\t\\t\\t Add some GNU debugger information '(D=0 by default)'")
	@$(call print, "\\t S=0 \\t\\t\\t Show compilation process details '(S=1 by default)'")
	@$(call print, "\\t E=emulator \\t\\t Using Other Emulator but need specify arguments '(S=1 by default)'")
	@$(call print, "\\t T=tool \\t\\t Configure toolchain prefix '($(TOOLCHAIN_PREFIX) by default)'")
	@$(call print, "")

.PHONY: all $(DEPENDENCIES) run dbg

# make all
all: $(DEPENDENCIES)
ifeq ($(SILENT), 0)
	@$(call _path_check)
endif

# make run
run:
# First Check Whether the directory exists
	$(call dir_check, $(GLOBAL_BUILD))
# Second Check Whether the virtual hard disk file exists
	$(call file_check, $(DISK_PATH)/$(DISK_NAME).hd, $(BXIMAGE) $(BXIMAGE_FLAGS))
# Finally Run the Emulator
	$(EMULATOR) $(BOCHS_FLAGS)

# make dbg
dbg:


# Build For User Component
user:
ifeq ($(SILENT), 1)
	@$(MAKE) -C $(GLOBAL_USER) -s
else
	$(MAKE) -C $(GLOBAL_USER)
endif

# Build For Kernel Component
kernel:
ifeq ($(SILENT), 1)
	@$(MAKE) -C $(GLOBAL_KERNEL) -s 
else
	$(MAKE) -C $(GLOBAL_KERNEL)
endif

# Build For Driver Component
driver:
ifeq ($(SILENT), 1)
	@$(MAKE) -C $(GLOBAL_DRIVER) -s 
else
	$(MAKE) -C $(GLOBAL_DRIVER)
endif

# Build For X86 Component
x86:
ifeq ($(SILENT), 1)
	@$(MAKE) -C $(GLOBAL_X86) -s 
else
	$(MAKE) -C $(GLOBAL_X86)
endif

### Clean Target
# Clean All the Build Target
.PHONY: clean
clean:
ifeq ($(SILENT), 1)
	@rm -rf ./build
else
	rm -rf $(GLOBAL_BUILD)
endif