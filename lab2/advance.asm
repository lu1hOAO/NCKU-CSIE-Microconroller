List p=18f4520
    #include<p18f4520.inc>
    CONFIG OSC=INTIO67
    CONFIG WDT=OFF
    org 0x00
    
    ;initial
    MOVLW 0x0A
    MOVWF 0x00
    MOVLW 0x03
    MOVWF 0x18
    
    LFSR 0,0x000 ;left
    LFSR 1,0x018 ;right
 
   
    MOVLW 0x10
    MOVWF 0x19 ;16times
    
    start:
    ;add
    BTFSS 0x19,0
	GOTO add_tag
    ;SUB
    BTFSC 0X19,0
	GOTO sub_tag
    add_tag:
	MOVF INDF1,WREG
	ADDWF INDF0,W
	MOVWF 0x1A ;temp
	MOVLW 0x01
	MOVFF 0x1A,PLUSW0
	GOTO back
    sub_tag:
	MOVF POSTDEC1,WREG
	SUBWF POSTINC0,W
	MOVWF INDF1
	GOTO back
    back:
	DECFSZ 0X19
	    GOTO start
    end
    

    


