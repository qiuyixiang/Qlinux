; This File Include Some Macro used for boot.S and loader.S
; This Header file also exported to some public Macros to the C format Header File

; Real Mode memory Layout:
;   - 0x7c00 - 0x7dff       boot memory location loaded by the BIOS
;   - 0x0900 - 0x0d00       loader memory location loaded by the boot
;   - 0x0500 - 0x0900       Saved Hardware information And GTD, IO Data for Kernel use

; Define For Program Component Address 
%define MAXI_REAL_MODE_ADDRESS  0xfffff
%define BOOT_START_ADDR         0x7c00
%define LOADER_START_ADDR       0x0900
%define KERNEL_START_ADDR       (MAXI_REAL_MODE_ADDRESS + 1)
%define KERNEL_BASE_ADDR        0x0001

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

; Definition For the Global Descriptor
%define GDT_CON_OFFSET      32
%define GDT_BASE_ADDRESS(BASE_LOW_16, BASE_MIDDLE_8, BASE_HIGH_8)   ((BASE_LOW_16 << 16) | (BASE_MIDDLE_8 << GDT_CON_OFFSET) \
                                                                    | (BASE_HIGH_8 << (GDT_CON_OFFSET + 24)))
%define GDT_LIMIT(LIMIT_LOW_16, LIMIT_HIGH_4)                       (LIMIT_LOW_16 | (LIMIT_HIGH_4 << (GDT_CON_OFFSET + 16)))
%define GDT_DPL(DPL_2)              (DPL_2 << (GDT_CON_OFFSET + 13))
%define GDT_G(G_1)                  (G_1 << (GDT_CON_OFFSET + 23))
%define GDT_P(P_1)                  (P_1 << (GDT_CON_OFFSET + 15))
%define GDT_S(S_1)                  (S_1 << (GDT_CON_OFFSET + 12))
%define GDT_TYPE(TYPE_4)            (TYPE_4 << (GDT_CON_OFFSET + 8))
%define GDT_DB(DB_1)                (DB_1 << (GDT_CON_OFFSET + 22))


; Definition For the Global Descriptor Selector
%define GDS_RPL0        0b00
%define GDS_RPL1        0b01
%define GDS_RPL2        0b10
%define GDS_RPL3        0b11
%define GDS_GDT         0b000
%define GDS_LGD         0b100
%define GD_SELECTOR(INDEX, TI, RPL)     (INDEX << 3) | (TI | RPL)

; Define Macros for Segment Selector
%define CODE_SEG_SELECTOR       GD_SELECTOR(1, GDS_GDT, GDS_RPL0)
%define DATA_SEG_SELECTOR       GD_SELECTOR(2, GDS_GDT, GDS_RPL0)