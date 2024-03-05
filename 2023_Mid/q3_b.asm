List p=18f4520
    #include<p18f4520.inc>
    CONFIG OSC=INTIO67
    CONFIG WDT=OFF
    org 0x00
    MOVLW 0XF8
    MOVWF 0X11
    MOVLW 0X03
    MOVWF 0X12
    CLRF 0X14 ;Q
    MOVLW 0X09
    MOVWF 0X15;COUNTER
    CALL div
    BRA finish
div:
    CALL sub
    CALL rotate_q
    BTFSC 0X10,7
	CALL add
    CALL rotate_or
    DECFSZ 0X15,F
	BRA div
    RETURN
sub:
    MOVFF 0X13,WREG
    SUBWF 0X11,F
    MOVFF 0X12,WREG
    SUBWFB 0X10,F
    RETURN
rotate_q:
    BCF STATUS,0
    RLCF 0X14
    BSF 0X14,0
    RETURN
add:
    MOVFF 0X13,WREG
    ADDWF 0X11,F
    MOVFF 0X12,WREG
    ADDWFC 0X10,F
    BCF 0X14,0
    RETURN
rotate_or:
    BCF STATUS,0
    RRCF 0X12
    RRCF 0X13
    RETURN
finish:
    MOVFF 0X11,0X01
    MOVFF 0X14,0X00
    end
