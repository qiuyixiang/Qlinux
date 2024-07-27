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
; Show Enter PM Message
    MOV AH, 0x13
    MOV AL, 0x01
    MOV BH, 0x00
    MOV BL, 0b00000111
    MOV BP, enter_message
    MOV CX, DS:[enter_message_len]
    MOV DH, 0x03
    MOV DL, 0x00
    MOV SI, 0x0000
    MOV ES, SI
    INT 0x10
; From Here Do some preparation For Enter Protected Mode 
; Enter Protected Mode :
; Close Interrupt
    CLI
; Open A20 Switch enable wider Memory Access
    IN AL, 0x92
    OR AL, 0b00000010
    OUT 0x92, AL
; Load GDT to gdtr register
    LGDT DS:[gdt_ptr]
; Enable Protected Mode (Make cr0 Least Significant bits to 1) 
    MOV EAX, CR0
    OR EAX, 0x00000001
    MOV CR0, EAX
; Flash the processor instruction catch
; And Jump to the protected Mode entry point
    JMP CODE_SEG_SELECTOR:_protect_mode_entry

BITS 32
_protect_mode_entry:
; Initialize General Purpose Register
    MOV EAX, 0x00000000
    MOV EBX, EAX
    MOV ECX, EAX
    MOV EDX, EAX
    MOV EDI, EAX
    MOV ESI, EAX
; Initialize New Stack Position to : 0x00000900
    MOV ESP, LOADER_START_ADDR
    MOV EBP, ESP
; Initialized New Segment Selector
    MOV AX, DATA_SEG_SELECTOR
    MOV DS, AX
    MOV SS, AX
    MOV ES, AX
    MOV FS, AX
    MOV GS, AX
    XCHG BX, BX
; Jump to the kernel entry at 0x00100000
    JMP CODE_SEG_SELECTOR:KERNEL_START_ADDR

; Data For Global Descriptor Table (This is only temporary GDT, after Enter Protected Mode
;   it will make a copy of this temporary GDT to the data buffer area ! and the kernel
;   procedure will make control of this table, it may be rebuild of edit this table !)
temp_gdt:
    gdt_base_seg:
        DQ      GDT_BASE_ADDRESS(0x0000, 0x00, 0x00) | GDT_LIMIT(0x0000, 0x0) | GDT_DPL(0b00) \
                | GDT_G(0) | GDT_P(0) | GDT_S(0) | GDT_TYPE(0b0000) | GDT_DB(0)
    gdt_code_seg:
        DQ      GDT_BASE_ADDRESS(0x0000, 0x00, 0x00) | GDT_LIMIT(0xffff, 0xf) | GDT_DPL(0b00) \
                | GDT_G(1) | GDT_P(1) | GDT_S(1) | GDT_TYPE(0b1000) | GDT_DB(1)
    gdt_data_seg:
        DQ      GDT_BASE_ADDRESS(0x0000, 0x00, 0x00) | GDT_LIMIT(0xffff, 0xf) | GDT_DPL(0b00) \
                | GDT_G(1) | GDT_P(1) | GDT_S(1) | GDT_TYPE(0b0010) | GDT_DB(1)
    gdt_size        EQU     $ - gdt_base_seg
    gdt_limit       EQU     gdt_size - 1
; This global descriptor table register used to store the gdtr register
gdt_ptr:
    DW  gdt_limit
    DD  temp_gdt

enter_message:
    DB "Enable Protected Mode (IA-32)32bits "
enter_message_len:
    DW $ - enter_message

