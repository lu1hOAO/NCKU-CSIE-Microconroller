List p=18f4520
    include<p18f4520.inc>
    CONFIG OSC=INTIO67
    CONFIG WDT=OFF
    org 0x00
    
    initial:
	MOVLW 0X05
	MOVWF 0X01
	MOVLW 0X03
	MOVWF 0X02
	RCALL Fact
	GOTO Finish
	
    
    Fact:
	;r=0 return
	CLRF WREG
	INCF 0X00
	CPFSGT 0X02
	    RETURN
	DECF 0X00
	;n=r return
	MOVF 0X02,W
	INCF 0X00
	CPFSGT 0X01
	    RETURN
	DECF 0X00
	;n-1,r
	DECF 0X01
	RCALL Fact
	;n-1,r-1
	DECF 0X02
	RCALL Fact
	INCF 0X01
	INCF 0X02
	RETURN
	
    Finish:
	end
	
	
	


