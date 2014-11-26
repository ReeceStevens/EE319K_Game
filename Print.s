; Print.s
; Student names: Ramya Ramachandran and Reece Stevens
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; LCD_OutChar   outputs a single 8-bit ASCII character
; LCD_OutString outputs a null-terminated string 

    IMPORT   LCD_OutChar
    IMPORT   LCD_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

	PRESERVE8
    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

quo 	EQU	14
rem		EQU 15

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11

Digit EQU	0		; BIND local variable 'Digit', which is defined as an offset of the stack pointer

LCD_OutDec

; binding phase
char	EQU	0
num		EQU	10				; 32-bit unsigned number in R0-this local variable will be at the address SP + 10
; allocation phase
	PUSH	{R4-R11,R0,LR}
	SUB 	SP, #16			; allocate 4 32-bit variables
; access phase
	STR		R0, [SP, #num]	; input is stored on the stack-num=input
	MOV		R1, #10			; for Mod
	MOV		R4, #0			; counter of place values
Mod_Div
	CMP		R0, #0			; check if input requires Mod fcn or not
	BEQ		Next
	BL		Mod
	LDRB	R3, [SP, #rem]
	STRB	R3, [SP, R4]	; remainder is stored on the stack-R4=remainder
	ADD		R4, #1			; increment counter
	LDRB	R3, [SP, #quo]
	MOV		R0, R2			; the new quotient becomes the new input
	B		Mod_Div
Next
; some kind of output loop
	SUB		R4, #1			; decrement counter
Output
	LDRB	R0, [SP, R4]	; R0 = R4 (remainder)
	ADD		R0, #0x30
	BL		LCD_OutChar		; puts character on screen
	CMP		R4, #0			; check counter
	BLE		Done			; If all remainders have been outputted, task is complete.
	SUB		R4, #1
	B 		Output
Done
; deallocation phase
	ADD		SP, #16			
	POP		{R4-R11, R0, LR}

    ; Approach: Convert the decimal number to ASCII, call LCD_OutChar to print digit
    ; Recursively divide input by 10 to isolate each digit
    PUSH {R5, LR}
    PUSH {R4, R12}
    MOV R1, R0      ; Copy input to a scratch register
    MOV R12, SP     ; Save original Stack Pointer
	MOV R4, #10		; power of ten offset
	MOV R5, #0x30	; ASCII offset




getnum  
        ADD SP, #-4     ; ALLOCATE
		MOV R2, R1      ; Copy input to other scratch register
        UDIV R3, R2, R4
        MUL R3, R4     ; Modulus operator: R2 % 10
        SUB R2, R2, R3  
        ;ADD R2, #0x30   ; Convert digit to ASCII
        STR R2, [SP, #Digit]    ; store in stack, ACCESS
        UDIV R1, R4    ; move to next decimal place
		CMP R1, #0		; check if last number is zero
		BEQ read
        CMP R1, #10      
        BLO printOutDec ; If number is less than 10, ready to begin printing
        B getnum        ; Else, continue to isolate digits


printOutDec

    ADD R1, #0x30       ; convert last digit to ASCII
    MOV R0, R1          ; move to R0
    BL LCD_OutChar      ; write to screen
read LDR R0, [SP, #Digit]      ; load next number from stack (already ASCII formatted)
	ADD R0, #0x30		; Convert to ASCII
    BL LCD_OutChar      ; write to screen
    ADD SP, #4         ; DEALLOCATE the digit from the stack
    CMP R12, SP         ; compare frame pointer and stack pointer
    BNE read            ; if not equal, still values in stack; continue reading.

    POP {R4, R12}
    POP {R0, LR}
    BX LR
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 " 
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
	
LCD_OutFix

; binding phase
fix		EQU	0
char1	EQU	4
dec		EQU	5
char2	EQU	6
char3	EQU 7
char4	EQU 8
dot		EQU	0x2E
ast		EQU	0x2A
limit	EQU	9999
; allocation phase
	PUSH	{R4-R11, R0, LR}
	LDR		R1, =limit
	CMP		R0, R1
	SUB		SP, #16			; allocate space on stack
	BHS		BigNum
; access phase
	STR		R0, [SP, #fix]	; store the input into fix
	MOV		R1, #1000
	BL		Mod
	ADD		R4, R2, #0x30
	STRB	R4, [SP, #char1] ; store most significant digit (8 bits) to char1
	MOV		R0, R3
	MOV		R1, #100
	BL		Mod
	ADD		R4, R2, #0x30
	STRB	R4, [SP, #char2]
	MOV		R0, R3
	MOV		R1, #10
	BL 		Mod
	ADD		R4, R2, #0x30
	STRB	R4, [SP, #char3]
	ADD		R4, R3, #0x30
	STRB	R4, [SP, #char4]
; output fixed-point number
	LDRB	R0, [SP, #char1]
	BL		LCD_OutChar
	MOV		R0, #dot
	BL		LCD_OutChar
	LDRB	R0, [SP, #char2]
	BL		LCD_OutChar
	LDRB	R0, [SP, #char3]
	BL		LCD_OutChar
	LDRB	R0, [SP, #char4]
	BL		LCD_OutChar
	B		Return
BigNum
; output "*.***"
	MOV		R0, #ast
	BL		LCD_OutChar
	MOV		R0, #dot
	BL		LCD_OutChar
	MOV		R0, #ast
	BL		LCD_OutChar
	BL		LCD_OutChar
	BL		LCD_OutChar
; deallocation phase
Return
	ADD		SP, #16
	POP		{R4-R11, R0, LR}
	BX 		LR

    ; Approach: Convert the decimal number to ASCII, call LCD_OutChar to print digit
    ; Recursively divide input by 10 to isolate each digit
	
    PUSH {R5, LR}
    PUSH {R4, R12}
    MOV R1, R0      ; Copy input to a scratch register
    MOV R12, SP     ; Save original Stack Pointer
	MOV R4, #10		; power of ten offset
	MOV R5, #0x2710
	CMP R0, R5	; Check if overflow is true
	BHS overflowFix
	MOV R5, #0


getnumfix  
		ADD SP, #-4     ; Allocate 4 bytes of space for this loop's version of the local variable Digit
		MOV R2, R1      ; Copy input to other scratch register
        UDIV R3, R2, R4
        MUL R3, R4     ; Modulus operator: R2 % 10
        SUB R2, R2, R3  
        STR R2, [SP, #Digit]    ; store in stack
        UDIV R1, R4    ; move to next decimal place
		ADD R5, #1
		CMP R5, #4
        BEQ printOutFix      
		B getnumfix
		
overflowFix
	MOV R0, #0x2A	
	BL LCD_OutChar
	MOV R0, #0x2E
	BL LCD_OutChar
	MOV R0, #0x2A
	BL LCD_OutChar
	MOV R0, #0x2A
	BL LCD_OutChar
	MOV R0, #0x2A
	BL LCD_OutChar
	POP {R4, R12}
    POP {R0, LR}
    BX LR
	
printOutFix	
	MOV R12, SP
loopFix
	LDR R0, [SP, #Digit]
	ADD R0, #0x30
	BL LCD_OutChar
	ADD R5, #-1
	ADD SP, #4		; Deallocate the local variable after usage
	CMP R5, #3
	BNE continueFix
	MOV R0, #0x2E	; Catch the decimal after the first print out
	BL LCD_OutChar
continueFix
	CMP R5, #0
	BEQ doneFix
	B loopFix

   

doneFix
    POP {R4, R12}
    POP {R5, LR}
    BX LR


   BX LR

;* * * * * * * * End of LCD_OutFix * * * * * * * *

; ----------------------Mod-----------------------
; Divides number by some multiple of 10 and saves the remainder
; Inputs:  R0 has dividend
;		   R1 has divisor
; Outputs:  R3 has remainder and R2 has quotient
Mod
	UDIV	R2, R0, R1			
	MUL		R3, R2, R1
	SUB		R3, R0, R3			; gets least significant value
	STRB	R2, [SP, #quo]
	STRB	R3, [SP, #rem]
	BX 		LR
;* * * * * * * * * End of Mod * * * * * * * * * * * 	
	

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file



   BX LR
