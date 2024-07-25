; Boot : the responsibility is just do some initial work 
;        and load loader.S from hard disk to the proper memory
;        location.

%include "bootloader.inc"

BITS 16
ORG LOADER_START_ADDR
section .text
global _start
_start:  
; The Code Segment Register Will be Initialized With 0 by BIOS
; Initialize General Purpose Register
    MOV AX, CS
    MOV BX, AX
    MOV CX, AX
    MOV DX, AX
    MOV DI, AX
    MOV SI, AX
; Initialize Segment Register
    MOV DS, AX
    MOV ES, AX
    MOV FS, AX
    MOV GS, AX
; Initialize Stack
    MOV AX, REAL_MODE_STACK_BASE
    MOV SS, AX
    MOV SP, REAL_MODE_STACK_OFFSET
    MOV BP, SP
; Clear The Screen
    MOV AH, 0x06
    MOV AL, 0x00
    MOV CH, VGA_LU_ROW
    MOV CL, VGA_LU_COLUMN
    MOV DH, VGA_RD_ROW
    MOV DL, VGA_RD_COLUMN

    INT 0x10

    MOV AX, 0x0000
    MOV DS, AX

; Print Characters
    MOV AH, 0x13
    MOV AL, 0x01
    MOV BH, 0x00    ; Current Display Page 0
    MOV BL, 0b00000111
    MOV CX, DS:[loader_info_len]
    MOV DH, VGA_LU_ROW
    MOV DL, VGA_LU_COLUMN
    MOV BP, loader_info
    MOV SI, 0x0000
    MOV ES, SI
    INT 0x10

    BOCHS_MAGIC_BREAK
_loop:
    JMP _loop

loader_info:
    DB "Bootloader setting up..."
loader_info_len:
    DW $ - loader_info
TIMES 510 - ($ - $$) DB 0x00
DB 0x55, 0xAA


    
    

