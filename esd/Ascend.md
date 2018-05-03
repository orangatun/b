## ALP for sorting of an 32 bit numbers in ascending order

        AREA LIST, DATA, READONLY
        DCD 0x0000008F, 0x00000012, 0x00000024, 0x00000023, 0x00000011
        ALIGN	
This is where you initialise the array to be sorted. The list can be accessed as `[LIST]`

        AREA DST, DATA, READWRITE
    SPACE 10
    LEN EQU 05
This is where you create space to store the sorted array.
You're also creating a constant `LEN` which will have the value `05`.

The main code starts here:
        AREA PROGRAM, CODE, READONLY
        ENTRY
        export start 
    start
        LDR R0,=LEN
        
You store the length of the list in R0
        
        LDR R5,=LIST
You store the **memory location/address** of the list of unsorted numbers in `R5`. Source
        
        LDR R6,=DST
You store the **memory location/address** of the list of sorted numbers in `R6`. Destination
    
    UP  LDR R1,[R5]
Loading the **number at address** `R5` into `R1` register
        
        STR R1,[R6]
Storing the number in `R1` register **at address stored in** `R6` register
        
        ADD R5,#04
        
Since the memory is in bytes(8-bits) and the numbers are 32-bit, each number requires 4 bytes(8\*4=32)
So, you add 4 to `R5` register and move to the next number in the unsorted list
        
        ADD R6,#04
        
Similarly, you add 4 to `R6` register to move to the next memory address to store the next number
        
        SUB R0,#1
        
You subtract the `R0` register, which you're using as a counter here.
        
        CMP R0,#00
        BNE UP
        
You check if the counter `R0` reached 0. If it did not, you go back and copy the next number from source to destination directly.
#### Upto this point, you did not do any sorting. You only copied the unsorted list from readonly source to readwrite destination.
        
You start with the sorting now:
        
        LDR R0,=LEN
        
You store the length of the list in `R0`
You'll be using this `R0` register as the counter for the outer loop

    TOP2 LDR R6,=DST

This is the starting of the outer loop
You store the **address** of the first number in the list in `R6`
        
        LDR R1,=LEN

You'll be using `R1` register as the counter for the inner loop

        SUB R1,#1
        
When you have 5 numbers, you only compare 4 times. So, you subtract 1 from the counter `R1`

    TOP LDR R2,[R6]
    
This is the starting of the inner loop
You load the first number to be compared from **address stored in** `R6` into `R2` register
    
        ADD R6,#4
        
You increment the address stored in `R6` by 4, to go to the next number
        
        LDR R3,[R6]
        
You now load the next number to be compared from the **address stored in** `R6` into `R3` register
        
        CMP R2,R3      
        
Compare the Value in `R2`(first number) with the value in `R3`(next number)
This will set the LessThan, EqualTo, and GreaterThan flags.

Change this line to `CMP R3,R2` for Descending order
        
        BLE DN
        
If the value in `R2` is less than the `R3` (for ascending), it will just branch/jump to `DN` label
Basically, it won't swap the two numbers.


If the value in `R3` is less than the `R2` (for descending), it will just branch/jump to `DN` label
Basically, it won't swap the two numbers.


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


