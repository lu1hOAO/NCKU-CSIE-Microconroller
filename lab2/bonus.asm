List P=18f4520
    #include<p18f4520.inc>
    CONFIG OSC=INTIO67
    CONFIG WDT=OFF
    org 0x00
    ;initial
    MOVLB 0x01 ;choose bank
    
    MOVLW 0x23 
    MOVWF 0x00,1
    MOVWF 0x10,1
    
    MOVLW 0x23
    MOVWF 0x01,1
    MOVWF 0x11,1
    
    MOVLW 0x12
    MOVWF 0x02,1
    MOVWF 0x12,1
    
    MOVLW 0x1C
    MOVWF 0x03,1
    MOVWF 0x13,1
    
    MOVLW 0xF7
    MOVWF 0x04,1
    MOVWF 0x14,1
    
    MOVLW 0xFF
    MOVWF 0x05,1
    MOVWF 0x15,1
    
    LFSR 0,0x110 ;left_pointer
    LFSR 1,0x115 ;right_pointer
    LFSR 2,0x110 ;iteration_pointer
    
    MOVLW 0x00
    MOVWF 0x01 ;left
    MOVLW 0x05
    MOVWF 0x02 ;right
    MOVFF 0x01,0x03
    
    
    loop_1:
	MOVLW 0x01
	MOVFF PLUSW2,WREG ;i+1
	CPFSGT INDF2
	    GOTO continue_1
    change_tag_1:
	MOVWF 0x00 ;temp=i+1
	MOVLW 0x01 
	MOVFF INDF2,PLUSW2 ;i+1=i
	MOVFF 0x00,INDF2 ;i=temp
    continue_1:
	CLRF WREG
	ADDWF POSTINC2 ;i++
	INCF 0x03      ;r++
	MOVFF 0x03,WREG
	CPFSEQ 0x02   ;right>r
	    GOTO loop_1
	
	CLRF WREG
	ADDWF POSTDEC1 ;right--
	ADDWF POSTDEC2 ;r[i]=right
	DECF 0x02     ;r--
	DECF 0x03
	MOVFF 0x02,WREG 
	CPFSEQ 0x01 ;left<=right
	    GOTO loop_2
	GOTO back
    loop_2:
	MOVFF POSTDEC2,WREG ;i+1
	CPFSGT INDF2 ;i<i+1
	    GOTO continue_2
    change_tag_2:
	MOVWF 0x00 ;temp=i+1
	MOVLW 0x01 
	MOVFF INDF2,PLUSW2 ;i+1=i
	MOVFF 0x00,INDF2 ;i=temp	
    continue_2:
	DECF 0x03      ;r--
	MOVFF 0x01,WREG
	CPFSEQ 0x03    ;r[i]>=LEFT
	    GOTO loop_2	
	CLRF WREG
	ADDWF POSTINC0 ;left++
	ADDWF POSTINC2
	INCF 0x01      ;l++
	INCF 0x03
	MOVFF 0x02,WREG 
	CPFSEQ 0x01 ;left<=right
	    GOTO loop_1
    back:
	NOP
    end
    
    
    
    
    

	
	

	    
	    
	    
		 
	    
	    
	
	


