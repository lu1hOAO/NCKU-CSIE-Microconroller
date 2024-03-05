List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC=INTIO67
	CONFIG WDT=OFF
	org 0x00
	
	;Initial
	CLRF 0x00 ;input address
	CLRF 0x10
	CLRF 0x11
	CLRF 0x20
	CLRF 0x21
	CLRF 0x01 ;output address
	MOVLW 0x62;input value
	MOVWF 0x00
	MOVWF 0x10
	MOVWF 0x11
	
	
	RRNCF 0x11
	COMF 0x11,W
	MOVWF 0x21
	
	COMF 0x10,W
	MOVWF 0x20
	
	CLRF WREG
	ADDWF 0x00,W
	ANDWF 0x21,W
	MOVWF 0x01
	
	CLRF WREG
	ADDWF 0x20,W
	ANDWF 0x11,W
	IORWF 0x01
	
	
	BTFSS 0x00,7
	    BCF 0x01,7
	BTFSC 0x00,7
	    BSF 0x01,7
	
	
	
	
	end


