List p=18f4520
    #include<p18f4520.inc>
    CONFIG OSC=INTIO67
    CONFIG WDT=OFF
    org 0x00
    
    MOVLW 0X02
    MOVWF TRISA ;multiplicand
    MOVLW 0XEF
    MOVWF TRISB ;multiplier
    CLRF TRISC
    
    ;0
    MOVF TRISC,W
    BTFSC TRISB,0
	ADDWF TRISA,W
    MOVWF TRISC
    RLNCF TRISA
    RRNCF TRISB
    ;1
    MOVF TRISC,W
    BTFSC TRISB,0
	ADDWF TRISA,W
    MOVWF TRISC
    RLNCF TRISA
    RRNCF TRISB
    ;2
    MOVF TRISC,W
    BTFSC TRISB,0
	ADDWF TRISA,W
    MOVWF TRISC
    RLNCF TRISA
    RRNCF TRISB
    ;3
    MOVF TRISC,W
    BTFSC TRISB,0
	ADDWF TRISA,W
    MOVWF TRISC
    end
    
    
    
	
	
	
    

    
  
    


