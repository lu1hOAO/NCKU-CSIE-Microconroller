List p=18f4520
    #include<p18f4520.inc>
    CONFIG OSC=INTIO67
    CONFIG WDT=OFF
    org 0x00
    
    ;init
    MOVLW 0x15
    MOVLB 0x1
    MOVWF 0x00,1
    MOVLW 0x12
    MOVWF 0x01,1
    MOVLW 0x07
    MOVWF 0x00,0;7
    

    LFSR 0,0x100
    LFSR 1,0x101
    LFSR 2,0x102
start:
    MOVF POSTINC0,WREG ;i
    BTFSC 0x00,0 
	ADDWF POSTINC1,W ;odd
    BTFSS 0x00,0
	SUBWF POSTINC1,W ;even
    MOVWF POSTINC2
    DECFSZ 0x00
	GOTO start
    end

