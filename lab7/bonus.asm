#include "p18f4520.inc"

; CONFIG1H
  CONFIG  OSC = INTIO67         ; Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

; CONFIG2L
  CONFIG  PWRT = OFF            ; Power-up Timer Enable bit (PWRT disabled)
  CONFIG  BOREN = SBORDIS       ; Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
  CONFIG  BORV = 3              ; Brown Out Reset Voltage bits (Minimum setting)

; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale Select bits (1:32768)

; CONFIG3H
  CONFIG  CCP2MX = PORTC        ; CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
  CONFIG  PBADEN = ON           ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
  CONFIG  LPT1OSC = OFF         ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
  CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
  CONFIG  XINST = OFF           ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; CONFIG5L
  CONFIG  CP0 = OFF             ; Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
  CONFIG  CP1 = OFF             ; Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
  CONFIG  CP2 = OFF             ; Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
  CONFIG  CP3 = OFF             ; Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

; CONFIG5H
  CONFIG  CPB = OFF             ; Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
  CONFIG  CPD = OFF             ; Data EEPROM Code Protection bit (Data EEPROM not code-protected)

; CONFIG6L
  CONFIG  WRT0 = OFF            ; Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
  CONFIG  WRT1 = OFF            ; Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
  CONFIG  WRT2 = OFF            ; Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
  CONFIG  WRT3 = OFF            ; Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

; CONFIG6H
  CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
  CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
  CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM not write-protected)

; CONFIG7L
  CONFIG  EBTR0 = OFF           ; Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR1 = OFF           ; Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR2 = OFF           ; Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR3 = OFF           ; Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

; CONFIG7H
  CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

    org 0x00
    GOTO initial
isr:
    org 0x08
    BSF PIE1,TMR2IE
    BTFSC INTCON,INT0IF
	BRA button
time:
    MOVFF 0X12,LATA
    DCFSNZ 0X11
	BRA t_end
    BTFSC 0X13,0
	DECF 0X12
    BTFSS 0X13,0
	INCF 0X12
t_re:
    BCF PIR1,TMR2IF
    RETFIE 
t_end:
    CLRF LATA
    CLRF 0X12
    BCF PIE1,TMR2IE
    BCF PIR1,TMR2IF
    RETFIE 
button:
    CLRF 0X12
    MOVFF 0X12,LATA
next:
    MOVLW 0X10
    MOVWF 0X11
    COMF 0X13
    RLNCF 0X10
    BTFSC 0X10,3
	CALL re_tst
    BRA tst
re_tst:
    RRNCF 0X10
    RRNCF 0X10
    RRNCF 0X10
    RETURN
tst:
    BTFSC 0X10,0
	MOVLW D'61'
    BTFSC 0X10,1
	MOVLW D'122'
    BTFSC 0X10,2
	MOVLW D'244'
    MOVWF PR2
cst:
    BTFSC 0X13,0
	MOVLW 0X0F
    BTFSS 0X13,0
	MOVLW 0X01
    MOVWF 0X12
    BCF INTCON,INT0IF
    RETFIE 
    
    

initial:
   ;io
   MOVLW 0X0F
   MOVWF ADCON1 
   CLRF TRISA
   CLRF LATA
   BSF TRISB,1
   ;INTERRUPT
   MOVLW b'00100000'
   MOVWF OSCCON
   BSF RCON,IPEN
   BSF INTCON,GIE
   BCF INTCON,INT0IF
   BSF INTCON,INT0IE
   ;TIMER
   BSF PIE1,TMR2IE     ;ENABLE
   BSF IPR1, TMR2IP    ;MATCH PRIORITY
   BCF PIR1, TMR2IF    ;FLAG	
   MOVLW b'11111111'	        
   MOVWF T2CON	      ;POSTSCALAR PRESCALAR
   MOVLW D'61'
   MOVWF PR2
  ;OTHERS
   CLRF 0X12
   MOVLW 0X11
   MOVWF 0X11
   CLRF 0X10
   BSF 0X10,0 ;time_STATE
   BCF 0X13,0 ;c_ST

main:
    BRA main
    end
    
    
    
   
