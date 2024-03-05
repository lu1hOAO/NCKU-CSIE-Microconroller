#include"xC.inc"
GLOBAL _is_square
    
PSECT mytext,local,class=CODE,reloc=1
    
_is_square:
    ;initial
    MOVLW 0X0F
    MOVWF 0X02
    ;begin
    GOTO loop
    finish:
	CLRF WREG
	CPFSGT 0X02
	    GOTO nope
	MOVLW 0X01
	GOTO re
    nope:
	MOVLW 0XFF
    re:
	RETURN

    loop:
	MOVFF 0X02,WREG
	MULWF 0X02
	MOVFF PRODL,0X03
	MOVFF 0X01,WREG
	SUBWF 0X03
	BZ finish
	DECF 0X02
	BNZ loop
	GOTO finish


