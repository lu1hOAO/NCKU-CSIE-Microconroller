LIST p=18f4520
#include<p18f4520.inc>
    CONFIG OSC = INTIO67 ; 1 MHZ
    CONFIG WDT = OFF
    CONFIG LVP = OFF
    
    L1	EQU 0x14
    L2	EQU 0x15
    MASK EQU 0X10
    org 0x00
DELAY macro num1, num2 
    local LOOP1         ; innerloop
    local LOOP2         ; outerloop
    MOVLW num2          ; 2 cycles
    MOVWF L2
    LOOP2:
	MOVLW num1          ; 2 cycles
	MOVWF L1
    LOOP1:
	NOP                 ; 7 cycles
	NOP
	NOP
	NOP
	NOP
	NOP
	DECFSZ L1, 1
	BRA LOOP1
	DECFSZ L2, 1        ; 2 cycles
	BRA LOOP2
endm	
; init
MOVLW b'01100000'
MOVWF OSCCON
MOVLW 0x0F
MOVWF ADCON1            ;set digital IO
CLRF PORTB
BSF TRISB, 0            ;set RB0 as input TRISB = 0000 0001
BCF TRISA, 0		;set RA0 as output TRISA = 0000 0000
BCF TRISA, 1
BCF TRISA, 2
BCF TRISA, 3

re_set:
    CLRF WREG
    ANDWF LATA,F
    DELAY D'200',D'180'
    MOVLW 0X01
    MOVWF MASK
    
check_process:          
   BTFSC PORTB, 0
	BRA check_process
   BTFSC LATA,3
	GOTO re_set
   BRA lightup
   
    
lightup:
    DELAY d'243',d'256'
    CLRF WREG
    ANDWF LATA,F
    MOVFF MASK,WREG
    IORWF LATA,F
    DELAY D'200',D'180'
    RLNCF MASK,F
    BRA check_process
end



