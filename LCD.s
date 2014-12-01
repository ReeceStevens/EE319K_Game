; LCD.s
; Student names: Ramya Ramachandran and Reece Stevens
; Last modification date: 10/25/14

; As part of Lab 7, students need to implement these LCD_WriteCommand and LCD_WriteData
; This driver assumes two low-level LCD functions

; Runs on LM4F120/TM4C123
; Use SSI0 to send an 8-bit code to the Nokia5110 48x84 pixel LCD.

; Red SparkFun Nokia 5110 (LCD-10168)
; -----------------------------------
; Signal        (Nokia 5110) LaunchPad pin
; 3.3V          (VCC, pin 1) power
; Ground        (GND, pin 2) ground
; SSI0Fss       (SCE, pin 3) connected to PA3
; Reset         (RST, pin 4) connected to PA7
; Data/Command  (D/C, pin 5) connected to PA6
; SSI0Tx        (DN,  pin 6) connected to PA5
; SSI0Clk       (SCLK, pin 7) connected to PA2
; back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total

DC                      EQU   0x40004100
DC_COMMAND              EQU   0
DC_DATA                 EQU   0x40
SSI0_DR_R               EQU   0x40008008
SSI0_SR_R               EQU   0x4000800C
SSI_SR_RNE              EQU   0x00000004  ; SSI Receive FIFO Not Empty
SSI_SR_BSY              EQU   0x00000010  ; SSI Busy Bit
SSI_SR_TNF              EQU   0x00000002  ; SSI Transmit FIFO Not Full

      EXPORT   LCD_WriteCommand
      EXPORT   LCD_WriteData

      AREA    |.text|, CODE, READONLY, ALIGN=2
      THUMB
      ALIGN

; The Data/Command pin must be valid when the eighth bit is
; sent.  The SSI module has hardware input and output FIFOs
; that are 8 locations deep.  Based on the observation that
; the LCD interface tends to send a few commands and then a
; lot of data, the FIFOs are not used when writing
; commands, and they are used when writing data.  This
; ensures that the Data/Command pin status matches the byte
; that is actually being transmitted.
; The write command operation waits until all data has been
; sent, configures the Data/Command pin for commands, sends
; the command, and then waits for the transmission to
; finish.
; The write data operation waits until there is room in the
; transmit FIFO, configures the Data/Command pin for data,
; and then adds the data to the transmit FIFO.
; NOTE: These functions will crash or stall indefinitely if
; the SSI0 module is not initialized and enabled.



; ************** LCD_WriteCommand ************************
; This is a helper function that sends an 8-bit command to the LCD.
; inputs: R0  8-bit command to transmit
; outputs: none
; assumes: SSI0 and port A have already been initialized and enabled
; Invariables: This function must not permanently modify registers R4 to R11
LCD_WriteCommand
;1) Read SSI0_SR_R and check bit 4, 
;2) If bit 4 is high, loop back to step 1 (wait for BUSY bit to be low)
;3) Clear D/C=PA6 to zero
;4) Write the command to SSI0_DR_R
;5) Read SSI0_SR_R and check bit 4, 
;6) If bit 4 is high, loop back to step 5 (wait for BUSY bit to be low)


CheckBusy	
			LDR R1, =SSI0_SR_R
			LDR R2, [R1]				; Read SSIO_SR_R
			AND R2, #0x10				; Isolate bit 4
			CMP R2, #0					; Check bit 4
			BEQ Next 
			B CheckBusy

Next
			LDR R1, =DC 				
			LDR R2, [R1]
			BIC R2, #0x40				; clears D/C=PA6 to zero	
			STR R2, [R1]
			LDR R3, =SSI0_DR_R  
			STRB R0, [R3]				; writes the command (input) to SSIO_DR_R	
			
CheckBusy2			
			LDR R1, =SSI0_SR_R
			LDR R2, [R1]				; Read SSIO_SR_R
			AND R2, #0x10				; Isolate bit 4
			CMP R2, #0					; Check bit 4
			BEQ Done
			B CheckBusy2
			
Done						    

   

    BX  LR                          ; return

    
   


; ************** LCD_WriteData ************************
; This is a helper function that sends an 8-bit data to the LCD.
; inputs: R0  8-bit data to transmit
; outputs: none
; assumes: SSI0 and port A have already been initialized and enabled
; Invariables: This function must not permanently modify registers R4 to R11
LCD_WriteData
;1) Read SSI0_SR_R and check bit 1, 
;2) If bit 1 is low loop back to step 1 (wait for TNF bit to be high)
;3) Set D/C=PA6 to one
;4) Write the 8-bit data to SSI0_DR_R

CheckTNF	
			LDR R1, =SSI0_SR_R
			LDR R2, [R1]
			AND R2, #0x02				; Isolate bit 1
			CMP R2, #0
			BEQ CheckTNF
			B Next1


Next1
			LDR R1, =DC 
			LDR R2, [R1]
			ORR R2, #0x40				; sets D/C=PA6 to one	
			STR R2, [R1]
			LDR R3, =SSI0_DR_R  
			STRB R0, [R3]				; writes the data (input) to SSIO_DR_R


    
    BX  LR                          ; return

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file
    
    
    
   
    
