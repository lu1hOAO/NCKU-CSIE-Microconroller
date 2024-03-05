#include"xC.inc"
    GLOBAL _lcm
    PSECT mytext,local,class=CODE,reloc=1
    
    _lcm:
	;initial
	MOVFF 0X01,0X21
	MOVFF 0X03,0X23
	MOVFF 0X03,WREG
	CPFSGT 0X01
	    CALL swap
	MOVFF 0X03,0X02
	;zero
	MOVF 0X02
	BZ zero
	;else
	MOVFF 0X03,0X13
	CALL sets
	;gcd
	CALL gcd
	;first
	MOVFF 0X01,0X02
	MOVFF 0X21,0X01
	CALL sets
	CALL div
	;mul
	MOVFF 0X04,WREG
	MULWF 0X23
	MOVFF PRODH,0X02
	MOVFF PRODL,0X01
	;labels
	final:
	    RETURN
	zero:
	    CLRF 0X00
	    CLRF 0X01
	    GOTO final
	swap:
	    MOVFF 0X01,0X03
	    MOVWF 0X01
	    RETURN  
	sets:
	CLRF 0X03
	CLRF 0X04
	MOVLW 0X09
	MOVWF 0X05 ;counter
	RETURN
	gcd:
	    CALL div
	    GOTO change
	cont:
	    MOVF 0X02
	    BNZ gcd
	    RETURN   
	change:
	    CLRF 0X00
	    CLRF 0X02
	    MOVFF 0X01,0X02
	    MOVFF 0X13,0X01
	    MOVFF 0X02,0X13
	    CALL sets
	    GOTO cont   
	;0X00 0X01 reminder
	;0X02 0X03 Divisor
	;0X04 Q
	div:
	    CALL sub
	    BTFSC 0X00,7
		GOTO small
	    BTFSS 0X00,7
		GOTO big
	continue:
	    DECF 0X05
	    BNZ div
	    RETURN
	sub:
	    MOVFF 0X03,WREG
	    SUBWF 0X01
	    MOVFF 0X02,WREG
	    SUBWFB 0X00
	    RETURN
	small:
	    MOVFF 0X03,WREG
	    ADDWF 0X01
	    MOVFF 0X02,WREG
	    ADDWFC 0X00
	    RLNCF 0X04
	    BCF 0X04,0
	    CALL rotate
	    GOTO continue    
	big:
	    RLNCF 0X04
	    BSF 0X04,0
	    CALL rotate
	    GOTO continue
	rotate:
	    RRNCF 0X03
	    BTFSC 0X02,0
		BSF 0X03,7
	    BTFSS 0X02,0
		BCF 0X03,7
	    RRNCF 0X02
	    BCF 0X02,7
	    RETURN
	




