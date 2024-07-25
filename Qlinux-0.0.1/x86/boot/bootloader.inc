; This File Include Some Macro used for boot.S and loader.S
; This Header file also exported to some public Macros to the C format Header File

; Define For General Address 
%define LOADER_START_ADDR       0x7c00


%define REAL_MODE_STACK_BASE        0x0000
%define REAL_MODE_STACK_OFFSET      0x7bff

%define R_MODE_DATA_AREA            0x0500

%define BOCHS_MAGIC_BREAK           XCHG BX, BX

; Basic Text VGA Related Macro
; Baisc Text VGA Display Mode (80 * 25)
%define VGA_LU_ROW                  0x00
%define VGA_LU_COLUMN               0x00
%define VGA_RD_ROW                  0x18    ; row 24
%define VGA_RD_COLUMN               0x4f    ; column 79