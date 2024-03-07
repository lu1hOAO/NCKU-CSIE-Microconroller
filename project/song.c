#include <xc.h>
#include <pic18f4520.h>
#define _XTAL_FREQ 1000000

//define timer scaling value for each note
#define C1 0x3a//262 hz = 3.8 ms = pr2 59
#define D1 0x34//294 hz = 3.4 ms = pr2 53
#define E1b 0x32//311 hz = 3.2 ms = pr2 50
#define E1 0x2e//330 hz = 3.0 ms = pr2 47
#define F1 0x2c//349 hz = 2.9 ms = pr2 45
#define G1 0x27//392 hz = 2.5 ms = pr2 39
#define A1b 0x26//415 hz = 2.4 ms = pr2 38
#define A1 0x23//440 hz = 2.3 ms = pr2 36
#define B1b 0x21//466 hz = 2.1 ms = pr2 33
#define B1 0x1f//494 hz = 2.0 ms = pr2 31
#define C2 0x1d//523 hz = 1.9 ms = pr2 29
#define D2b 0x1c//554 hz = 1.8 ms = pr2 28
#define D2 0x1a//587 hz = 1.7 ms = pr2 26
#define E2 0x17//659 hz = 1.5 ms = pr2 23
#define G2b 0x14//740 hz = 1.3 ms = pr2 20
#define A2b 0x13//830 hz = 1.2 ms = pr2 19
#define A2 0x11//880 hz = 1.1 ms = pr2 17
/*
 * speed 1000 = bpm 165
 * speed 2000 = bpm 88
 * speed 4000 = bpm 52
 */
#define speed 1000
#define len 1

int led_index;
int song_pick;

void reinitCCP1(){
    //speaker initialize
    T2CONbits.TMR2ON = 0b1; //open timer2
    T2CONbits.T2CKPS = 0b10; //prescaler -> 16
    CCP1CONbits.CCP1M = 0b1100; // PWM mode, P1A, P1C active-high; P1B, P1D active-high
    // CCP1/RC2 -> Output
    TRISCbits.RC2 = 0;
    PR2 = 0x01; //PWM period = frequency
    //duty cycle = volume
    CCPR1L = PR2 / 2;
    CCP1CONbits.DC1B = 0b00;
    return;
}

void delay_ms(unsigned int milliseconds) {
   while(milliseconds > 0) {
      milliseconds--;
       __delay_us(990);
   }
}

void speaker(unsigned char tone){    
    PR2 = tone;
    if(tone == A1){//set PWM frequency according to entries in song array
        CCPR1L = PR2 / 5;
    }
    else{
        CCPR1L = PR2 / 2;
    }
     
}

void button_pressed_check(){
    if(song_pick == 0 && PORTAbits.RA0 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD0 == 0){
        LATDbits.LATD0 = 1;
        speaker(C1);
        return;
    }
    else if(song_pick == 1 && PORTAbits.RA0 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD0 == 0){
        LATDbits.LATD0 = 1;
        speaker(C1);
        return;
    }
    else if(song_pick == 2 && PORTAbits.RA0 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD0 == 0){
        LATDbits.LATD0 = 1;
        speaker(A1);
        return;
    }
    else if(song_pick == 3 && PORTAbits.RA0 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD0 == 0){
        LATDbits.LATD0 = 1;
        speaker(D1);
        return;
    }
    if(song_pick == 0 && PORTAbits.RA1 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD1 == 0){
        LATDbits.LATD1 = 1;
        speaker(D1);
        return;
    }
    else if(song_pick == 1 && PORTAbits.RA1 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD1 == 0){
        LATDbits.LATD1 = 1;
        speaker(D1);
        return;
    }
    else if(song_pick == 2 && PORTAbits.RA1 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD1 == 0){
        LATDbits.LATD1 = 1;
        speaker(B1);
        return;
    }
    else if(song_pick == 3 && PORTAbits.RA1 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD1 == 0){
        LATDbits.LATD1 = 1;
        speaker(E1);
        return;
    }
    if(song_pick == 0 && PORTAbits.RA2 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD2 == 0){
        LATDbits.LATD2 = 1;
        speaker(E1);
        return;
    }
    else if(song_pick == 1 && PORTAbits.RA2 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD2 == 0){
        LATDbits.LATD2 = 1;
        speaker(E1);
        return;
    }
    else if(song_pick == 2 && PORTAbits.RA2 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD2 == 0){
        LATDbits.LATD2 = 1;
        speaker(D2b);
        return;
    }
    else if(song_pick == 3 && PORTAbits.RA2 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD2 == 0){
        LATDbits.LATD2 = 1;
        speaker(F1);
        return;
    }
    if(song_pick == 0 && PORTAbits.RA3 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD3 == 0){
        LATDbits.LATD3 = 1;
        speaker(F1);
        return;
    }
    else if(song_pick == 1 && PORTAbits.RA3 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD3 == 0){
        LATDbits.LATD3 = 1;
        speaker(F1);
        return;
    }
    else if(song_pick == 2 && PORTAbits.RA3 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD3 == 0){
        LATDbits.LATD3 = 1;
        speaker(D2);
        return;
    }
    else if(song_pick == 3 && PORTAbits.RA3 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD3 == 0){
        LATDbits.LATD3 = 1;
        speaker(G1);
        return;
    }
    if(song_pick == 0 && PORTAbits.RA4 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD4 == 0){
        LATDbits.LATD4 = 1;
        speaker(G1);
        return;
    }
    else if(song_pick == 1 && PORTAbits.RA4 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD4 == 0){
        LATDbits.LATD4 = 1;
        speaker(G1);
        return;
    }
    else if(song_pick == 2 && PORTAbits.RA4 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD4 == 0){
        LATDbits.LATD4 = 1;
        speaker(E2);
        return;
    }
    else if(song_pick == 3 && PORTAbits.RA4 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD4 == 0){
        LATDbits.LATD4 = 1;
        speaker(A1);
        return;
    }
    if(song_pick == 0 && PORTAbits.RA5 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD5 == 0){
        LATDbits.LATD5 = 1;
        speaker(A1);
        return;
    }
    else if(song_pick == 1 && PORTAbits.RA5 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD5 == 0){
        LATDbits.LATD5 = 1;
        speaker(A1);
        return;
    }
    else if(song_pick == 2 && PORTAbits.RA5 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD5 == 0){
        LATDbits.LATD5 = 1;
        speaker(G2b);
        return;
    }
    else if(song_pick == 3 && PORTAbits.RA5 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD5 == 0){
        LATDbits.LATD5 = 1;
        speaker(B1b);
        return;
    }
    if(song_pick == 0 && PORTAbits.RA6 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD6 == 0){
        LATDbits.LATD6 = 1;
        speaker(B1);
        return;
    }
    else if(song_pick == 1 && PORTAbits.RA6 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD6 == 0){
        LATDbits.LATD6 = 1;
        speaker(B1b);
        return;
    }
    else if(song_pick == 2 && PORTAbits.RA6 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD6 == 0){
        LATDbits.LATD6 = 1;
        speaker(A2b);
        return;
    }
    else if(song_pick == 3 && PORTAbits.RA6 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD6 == 0){
        LATDbits.LATD6 = 1;
        speaker(C2);
        return;
    }
    if(song_pick == 0 && PORTAbits.RA7 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD7 == 0){
        LATDbits.LATD7 = 1;
        speaker(C2);
        return;
    }
    else if(song_pick == 1 && PORTAbits.RA7 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD7 == 0){
        LATDbits.LATD7 = 1;
        speaker(C2);
        return;
    }
    else if(song_pick == 2 && PORTAbits.RA7 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD7 == 0){
        LATDbits.LATD7 = 1;
        speaker(A2);
        return;
    }
    else if(song_pick == 3 && PORTAbits.RA7 == 0 && LATBbits.LATB0 == 1 && LATDbits.LATD7 == 0){
        LATDbits.LATD7 = 1;
        speaker(D2);
        return;
    }
    return;
}
