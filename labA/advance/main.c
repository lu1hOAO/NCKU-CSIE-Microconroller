#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include <pic18f4520.h>
#include "stdio.h"
#include "string.h"
// using namespace std;
#define _XTAL_FREQ 1000000
void BOTTOM_Initialize();
void LIGHT_Initialize();
char data;
unsigned char mask;
void main(void) 
{
    
    SYSTEM_Initialize() ;
    BOTTOM_Initialize();
    LIGHT_Initialize();
    data='0';
    while(1){
        if(data<=57)
            UART_Write(data);
        else{
            UART_Write('1');
            UART_Write(data-10);
        }
    }
    
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{
    if(INTCONbits.INT0IF){
        mask+=2;
        data+=1;
        if(mask==32){
            mask=0;
            data='0';
        }
        LATA=mask;
        __delay_ms(500);
        
        INTCONbits.INT0IF=0;
    }
    return;
}
void BOTTOM_Initialize(){
    ADCON1=0X0f;
    TRISBbits.RB0=0b1;
    INTCONbits.INT0IF=0;
    INTCONbits.INT0IE=1;
    INTCONbits.GIE=1;
    return;
}
void LIGHT_Initialize(){
    TRISAbits.RA1=0;
    TRISAbits.RA2=0;
    TRISAbits.RA3=0;
    TRISAbits.RA4=0;
    LATA=0;
    mask=0;
    return;
}
