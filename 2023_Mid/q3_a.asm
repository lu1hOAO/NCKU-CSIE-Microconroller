List p=18f4520
    #include<p18f4520.inc>
    CONFIG OSC=INTIO67
    CONFIG WDT=OFF
    org 0x00
    MOVLW 0X34
    MOVWF 0X11
    MOVLW 0X86
    MOVWF 0X10
    MOVLW 0X75
    MOVWF 0X13
    MOVLW 0X70
    MOVWF 0X12
    MOVFF 0X13,WREG
    SUBWF 0X11,W
    MOVFF WREG,0X23
    MOVFF 0X12,WREG
    SUBWFB 0X10,W
    MOVFF WREG,0X22
check:
    MOVFF 0X23,WREG
    ADDWF 0X13,W
    DAW
    MOVFF WREG,0X33
    MOVFF 0X22,WREG
    ADDWFC 0X12,W
    DAW
    MOVFF WREG,0X32
    MOVFF 0X11,WREG
    CPFSEQ 0x33
	CALL sub
    MOVFF 0X11,WREG
    CPFSEQ 0x33
	CALL sub2
    MOVFF 0X10,WREG
    CPFSEQ 0x32
	CALL sub3
    MOVFF 0X10,WREG
    CPFSEQ 0x32
	CALL sub4
    BRA finish
sub:
    MOVLW 0X06
    SUBWF 0X33,F
    SUBWF 0X23,F
    RETURN
sub2:    
    MOVLW 0X60
    SUBWF 0X33,F
    SUBWF 0X23,F
    RETURN
sub3:
    MOVLW 0X06
    SUBWF 0X32,F
    SUBWF 0X22,F
    RETURN
sub4:
    MOVLW 0X60
    SUBWF 0X32,F
    SUBWF 0X22,F
    RETURN
finish:
    MOVFF 0X23,0X01
    MOVFF 0X22,0X00
    end


