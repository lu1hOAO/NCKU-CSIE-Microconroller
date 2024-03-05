List p=18f4520
    #include<p18f4520.inc>
    CONFIG OSC=INTIO67
    CONFIG WDT=OFF
    org 0x00
    
    ;init
    MOVLW 0XF0
    MOVWF TRISA
    MOVWF 0X00 ;KEEP DATA
    RRNCF TRISA
    BTFSC 0X00,7
	BSF TRISA,7
    BTFSS 0X00,7
	BCF TRISA,7
    RRNCF TRISA
    BCF TRISA,7
    
    
    
    end


