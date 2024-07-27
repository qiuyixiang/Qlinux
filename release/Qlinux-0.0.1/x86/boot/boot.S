; Boot : the responsibility is just do some initial work 
;        and load loader.S from hard disk to the proper memory
;        location.

%include "bootloader.inc"

BITS 16
ORG BOOT_START_ADDR
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
; Makesure DS is still 0x0000
    MOV AX, 0x0000
    MOV DS, AX

; Print Characters for loader successfully loaded
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
    NOP 
    NOP
; Print message about hard disk reading
    MOV AH, 0x13
    MOV AL, 0x01
    MOV BH, 0x00
    MOV BL, 0b00000111
    MOV BP, disk_info
    MOV CX, DS:[disk_info_len]
    MOV DH, 0x01
    MOV DL, 0x00
    MOV DI, 0x0000
    MOV ES, DI
    INT 0x10

_retry:
; Read From Hard disk for loader
    NOP
    MOV AH, 0x02
    MOV AL, LOADER_SECTOR_SIZE
    MOV BX, LOADER_START_ADDR
    MOV CH, 0x00
    MOV CL, 0x02
    MOV DH, 0x00
    MOV DL, 0x80
    MOV DI, 0x0000
    MOV ES, DI
    INT 0x13
; According BIOS Manual if carry that means error occurs and try again without 
; Save error message
    JC _retry

; Create Some Delay
    NOP
    NOP
; Print Successful Information
    MOV AH, 0x13
    MOV AL, 0x01
    MOV BH, 0x00
    MOV BL, 0b00001111
    MOV BP, success_info
    MOV CX, DS:[success_info_len]
    MOV DH, 0x02
    MOV DL, 0x00
    MOV SI, 0x0000
    MOV ES, SI
    INT 0x10
; Unconditional Jump to the loader address 0x0000:0x0900
    JMP 0x0000:LOADER_START_ADDR

; Boot Data Segment
    loader_info:
        DB "Bootloader setting up..."
    loader_info_len:
        DW $ - loader_info
    disk_info:
        DB "Reading OS loader from hard disk ..."
    disk_info_len:
        DW $ - disk_info
    success_info:
        DB "Reading OS loader Successfully !!! "
    success_info_len:
        DW $ - success_info
TIMES 510 - ($ - $$) DB 0x00
DB 0x55, 0xAA


    
    

