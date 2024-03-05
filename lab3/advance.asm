List p=18f4520
    #include<p18f4520.inc>
    CONFIG OSC=INTIO67
    CONFIG WDT=OFF
    org 0x00
    
    ;init
    MOVLW 0X76
    MOVWF 0X00
    MOVLW 0X12
    MOVWF 0X01
    MOVLW 0X44
    MOVWF 0X10
    MOVLW 0X93
    MOVWF 0X11
    
    
    MOVF 0X01,W
    ADDWF 0X11,W
    MOVWF 0X21
    BTFSC STATUS,0
	INCF 0X20
    MOVF 0X00,W
    ADDWF 0X10,W
    ADDWF 0X20
    
    end
	

    
	
    


