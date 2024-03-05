#include"xC.inc"
    GLOBAL _multi_signed
    PSECT mytext,local,class=CODE,reloc=1
    
_multi_signed:
    ;initial 
    MOVFF 0X01,0X12
    MOVFF 0X01,0X22
    MOVWF 0X11 ;Multliplicand L
    MOVWF 0X21 
    CLRF 0X10  ;multliplicnd H
    CLRF 0X20
    CLRF 0X00 ;read
    CLRF 0X01
    CLRF 0X02 ;PH
    CLRF 0X03 ;PL
    MOVLW 0X08
    MOVWF 0X13
    
    loop:
	BTFSC 0X12,0
	    CALL add
	CALL rotate
	DECF 0X13
	BNZ loop
	GOTO finish
	
    add:
	MOVFF 0X11,WREG
	ADDWF 0X03
	MOVFF 0X10,WREG
	ADDWFC 0X02
	CLRF WREG
	RETURN
    
    rotate:
	RRNCF 0X12
	RLNCF 0X10
	BTFSC 0X11,7
	    BSF 0X10,0
	RLNCF 0X11
	BCF 0X11,0
	RETURN
    
    finish:
	MOVFF 0X03,0X01
	MOVFF 0X21,WREG
	BTFSC 0X22,7
	    SUBWF 0X02
	MOVFF 0X22,WREG
	BTFSC 0X21,7
	    SUBWF 0X02
	RETURN
	    
	
    
    
    
    


