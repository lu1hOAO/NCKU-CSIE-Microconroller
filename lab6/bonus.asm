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
	NOP                 ; 8 cycles
	NOP
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
CLRF LATA
BCF TRISA, 0		;set RA0 as output TRISA = 0000 0000
BCF TRISA, 1
BCF TRISA, 2
BCF TRISA, 3

initial_state:
    CLRF WREG
    ANDWF LATA
    DELAY d'243',d'256'
    MOVLW 0X01
    MOVWF MASK
    
check_process_1:          
   BTFSS PORTB, 0
	BRA state1
   BRA check_process_1
    
state1:
    CLRF WREG
    ANDWF LATA
    MOVFF MASK,WREG
    IORWF LATA
    DELAY d'243',d'256'
    BTFSC LATA,3
	GOTO check_process_2
    RLNCF MASK
    GOTO state1

check_process_2:          
   BTFSS PORTB, 0
	BRA state2
   MOVLW 0X01
   MOVWF MASK
   BRA state1

state2:
    CLRF WREG
    ANDWF LATA
    MOVFF MASK,WREG
    IORWF LATA
    DELAY d'243',d'256'
    BTFSC LATA,0
	GOTO check_process_3
    RRNCF MASK
    GOTO state2
    
check_process_3:          
   BTFSS PORTB, 0
	BRA initial_state
   MOVLW 0X08
   MOVWF MASK
   BRA state2
    
end


