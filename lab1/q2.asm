List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC=INTIO67
	CONFIG WDT=OFF
	org 0x00
	
	Initial:
	    MOVLW 0xEA
	    MOVWF 0x00
	    MOVLW 0x20
	    MOVWF 0x02
	    MOVLW 0x08
	    MOVWF 0x01
	    
	loop:
	    BTFSS 0x00,0
		INCF 0x02
	    BTFSC 0x00,0
		DECF 0x02
	    RRNCF 0x00
	    DECFSZ 0x01
		GOTO loop
	    NOP
	    
    
	
	end


