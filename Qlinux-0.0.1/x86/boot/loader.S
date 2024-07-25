; The responsibility of loader.S is divided into different small parts

; Create on 07/25/2024
; Duty of loader.S

; Initialize and read some Basic data and IO information and store it at 0x500
; Construct GDT and store it in a specific memory location
; Enable Protected Mode

%include "bootloader.inc"

ORG LOADER_START_ADDR
BITS 16
section .text
global _loader


_loader:


    XCHG BX, BX
_hlt:
    JMP _hlt

; Data For Global Descriptor Table (This is only temporary GDT, after Enter Protected Mode
;   it will make a copy of this temporary GDT to the 0x0500 data buffer area ! and the kernel
;   procedure will make control of this table, it may be rebuild of edit this table !)
temp_gdt:



