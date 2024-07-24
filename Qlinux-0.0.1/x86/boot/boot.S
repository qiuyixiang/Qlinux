; Boot : the responsibility is just do some initial work 
;        and load loader.S from hard disk to the proper memory
;        location.


BITS 16
section .text
global _start
_start:  
    MOV AX, 0x0000
    MOV BX, AX
    MOV CX, AX
    MOV DX, AX
    XCHG BX, BX
_loop:
    JMP _loop

TIMES 510 - ($ - $$) DB 0x00
DB 0x55, 0xAA


    
    

