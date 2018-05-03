## ALP for sorting of an 32 bit numbers in ascending order

        AREA LIST, DATA, READONLY
        DCD 0x0000008F, 0x00000012, 0x00000024, 0x00000023, 0x00000011
This is where you initialise the array to be sorted. Accessed as `[LIST]`

        ALIGN	
        AREA DST, DATA, READWRITE
    SPACE 10
    LEN EQU 05
        AREA PROGRAM, CODE, READONLY
        ENTRY
        export start 
    start
        LDR R0,=LEN
        LDR R5,=LIST
        LDR R6,=DST
    UP  LDR R1,[R5]
        STR R1,[R6]
        ADD R5,#04
        ADD R6,#04
        SUB R0,#1
        CMP R0,#00
        BNE UP
        LDR R0,=LEN
    TOP2 LDR R6,=DST
        LDR R1,=LEN
        SUB R1,#1
    TOP LDR R2,[R6]
        ADD R6,#4
        LDR R3,[R6]
        CMP R2,R3      ;CHANGE CMP R3,R2 FOR DESCENDING
        BLE DN
        STR R2,[R6]
        SUB R6,#4
        STR R3,[R6]
        ADD R6,#4
    DN  SUB R1,#01
        CMP R1,#00
        BLE DN1
        B TOP
    DN1 SUB R0,#1
        CMP R0,#00
        BLE DN2
        B TOP2
    DN2 B DN2
        END


