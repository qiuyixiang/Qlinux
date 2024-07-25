; This File Include Some Macro used for boot.S and loader.S
; This Header file also exported to some public Macros to the C format Header File

; Real Mode memory Layout:
;   - 0x7c00 - 0x7dff       boot memory location loaded by the BIOS
;   - 0x0900 - 0x0d00       loader memory location loaded by the boot
;   - 0x0500 - 0x0900       Saved Hardware information And GTD, IO Data for Kernel use

; Define For Program Component Address 
%define BOOT_START_ADDR         0x7c00
%define LOADER_START_ADDR       0x0900

; Define For Real Mode Data Storgae Memory Address
%define R_MODE_DATA_AREA            0x0500

; Define For Real Mode Stack
%define REAL_MODE_STACK_BASE        0x0000
%define REAL_MODE_STACK_OFFSET      0x7c00

; Utility Macros 
%define BOCHS_MAGIC_BREAK           XCHG BX, BX

; Basic Text VGA Related Macro
; Baisc Text VGA Display Mode (80 * 25)
%define VGA_LU_ROW                  0x00
%define VGA_LU_COLUMN               0x00
%define VGA_RD_ROW                  0x18    ; row 24
%define VGA_RD_COLUMN               0x4f    ; column 79

; Hard Disk Operation Varibales
%define LOADER_SECTOR_SIZE          0x02
%define BOOT_SECTOR_SIZE            0x01

; Definition For the GDT
%define GDT_DATA_ADDRESS            R_MODE_DATA_AREA
