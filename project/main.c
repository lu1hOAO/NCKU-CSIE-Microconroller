#include <xc.h>
#include <pic18f4520.h>
#include "song.h"

#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define SONG_NUM 4
#define _XTAL_FREQ 1000000
#define STATE_NUM 12

#pragma config OSC = INTIO67    // Oscillator Selection bits
#pragma config WDT = OFF        // Watchdog Timer Enable bit 
#pragma config PWRT = OFF       // Power-up Enable bit
#pragma config BOREN = ON       // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF        // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF        // Data EEPROM?Memory Code Protection bit (Data EEPROM code protection off)

void initTimer2andCCP1();
void pickSong();
void reinitCCP1();
//void getNote();
void TIMER1_Initial();

// Global varibles
int playing = 0;
int song_pick;
int led_index;
int delay_time;
int BECset[]={1,2,4,8,16,32,2,4,16,32,64,128};
int Dset[]={254, 253, 251, 247, 239, 223, 191, 127};
unsigned char B[12], C[12], D[12], E[12]; // X[index] = the LATx at state index at time
int star_Note[]={-1, -1,
					 1, -1, 1, -1, 5, -1, 5, -1, 6, -1, 6, -1, 5, -1, -1, -1,
					 4, -1, 4, -1, 3, -1, 3, -1, 2, -1, 2, -1, 1, -1, -1, -1,
					 5, -1, 5, -1, 4, -1, 4, -1, 3, -1, 3, -1, 2, -1, -1, -1,
					 5, -1, 5, -1, 4, -1, 4, -1, 3, -1, 3, -1, 2, -1, -1, -1,
					 1, -1, 1, -1, 5, -1, 5, -1, 6, -1, 6, -1, 5, -1, -1, -1,
					 4, -1, 4, -1, 3, -1, 3, -1, 2, -1, 2, -1, 1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int forever_Note[]={-1, -1, 
                    4, -1, 5, -1 ,6, -1, 4, -1, 8, -1, -1, -1, -1, -1, 6, -1, 5, -1, -1, -1, 8, -1, -1, -1, 5, -1, -1, -1, 4, -1, 2, -1,
                    6, -1, -1, -1, -1, -1, 4, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4, -1, 3, -1, 2, -1, -1, -1, 3, -1, -1, -1, 4, -1, 5, -1,
                    1, -1, -1, -1, 4, -1, -1, -1, 5, -1, 6, -1, 7, -1, -1, -1, 7, -1, 6, -1, 5, -1, 4, -1, 5, -1, -1, -1, -1, -1, -1, -1,
                    4, -1, 5, -1, 6, -1, 4, -1, 8, -1, -1, -1, -1, -1, 6, -1, 5, -1, -1, -1, 8, -1, -1, -1, 5, -1, -1, -1, 4, -1, 2,  -1, 
                    2, -1, -1, -1, 3, -1, 4, -1, 1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, 2, -1, -1, -1, 3, -1, -1, -1, 4, -1, 5, -1,
                    1, -1, -1, -1, 4, -1, -1, -1, 5, -1, 6, -1, 7, -1, -1, -1, 7, -1, 6, -1, 5, -1, 4, -1, 4, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; 
int Xmas_Note[]={-1, -1, 
                 5, -1, -1, -1, -1, -1, 5, -1, -1, -1, 4, -1, -1, -1, 1, -1, 				
                 5, -1, 5, -1, 6, -1, 4, -1, -1, -1, -1, -1, 2, -1, 4, -1,
                 5,-1, 5, -1, 6, -1, -1, -1, 4, -1, -1, -1, -1, -1, 4, -1, 
                 3, -1, 4, -1,3, -1, 2, -1,-1, -1, -1, -1, -1, -1, -1,-1, 
                 6, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, 2, -1, 
                 6, -1, 7, -1, 6, -1, -1, -1, 5, -1, -1, -1, -1, -1, 4, -1,
                 3,-1, 4, -1, 3, -1, 3, -1, -1, -1, 4, -1, 3,-1, 3, -1, -1, 
                 -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, 
                 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1}; 
int sakura_Note[]={-1, -1, 1, -1, 3, -1, 
                   4, -1, -1, 4, -1, -1, 5, -1, 5, -1, -1, -1, -1, -1, 5, -1, 
                   7, -1, 8, -1, 4, -1, 3, -1, 5, -1, -1, -1, 1, -1, 3, -1,
                   4, -1, -1, 4, -1, -1, 5, -1, 5, -1, -1, -1, -1, -1, 5, -1,
                   6, -1, 5, -1, 4, -1, 3, -1, 3, -1, -1, -1, 1, -1, 3, -1,
                   4, -1, -1, 4, -1, -1, 5, -1, 5, -1, -1, -1, -1, -1, 5, -1, 
                   7, -1, 8, -1, 4, -1, 3, -1, 5, -1, -1, -1, 1, -1, 3, -1,
                   6, -1, -1, -1, 5, -1, -1, -1, 4, -1, -1, -1, 3, -1, -1, -1,
                   4, -1, 5, -1, 1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1,
                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
//int star_len[] = {0,0,1,0,1,0,1,0,1,0,1,0,1,0,2,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,2,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,2,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,2,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,2,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,2,0,0,0};
//int forever_len[] = {0,0,1,1,1,1,1,0,0,1,1,0,1,0,1,0,1,1,1,0,0,1,1,0,0,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,0,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,0,0};
//int Xmas_len[]={0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0}; 
//int sakura_len[]={0,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1, 0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0}; 
int song_len[] = {98,194,130,134};
void __interrupt(low_priority)L_ISR(){
    LATB = 0x00;
    LATEbits.LATE1 = 0;
    LATEbits.LATE2 = 0;
    LATC = 0x00;
    LATD = 0xff;
    led_index=led_index+1;
    if(song_pick==0){ 
        if(star_Note[led_index] > 0){//stop the speaker
            PR2 = 0x00; //the PWM frequency set beyond audible range
            CCPR1L = 0;//in order to create a short silence between notes
            CCP1CONbits.DC1B = 0b00;
        }
    }
    else if(song_pick==1){ 
        if(forever_Note[led_index] > 0){//stop the speaker
            PR2 = 0x00; //the PWM frequency set beyond audible range
            CCPR1L = 0;//in order to create a short silence between notes
            CCP1CONbits.DC1B = 0b00;
        }
    }
    else if(song_pick==2){ 
        if(Xmas_Note[led_index] > 0){//stop the speaker
            PR2 = 0x00; //the PWM frequency set beyond audible range
            CCPR1L = 0;//in order to create a short silence between notes
            CCP1CONbits.DC1B = 0b00;
        }
    }
    else if(song_pick==3){ 
        if(sakura_Note[led_index] > 0){//stop the speaker
            PR2 = 0x00; //the PWM frequency set beyond audible range
            CCPR1L = 0;//in order to create a short silence between notes
            CCP1CONbits.DC1B = 0b00;
        }
    }
    if(led_index>=song_len[song_pick] + 1){
            PIE1bits.TMR1IE=0;
            led_index = song_len[song_pick];
            LATB = 0x00;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 0;
            LATC = 0x00;
            LATD = 0xff;
            reinitCCP1();
            playing = 0;
    }
    PIR1bits.TMR1IF=0;
    sing();
    return;
}

void main(void) {
    srand((time_t) time(NULL) );
//    srand(8);
    initTimer2andCCP1();
    // Digital mode
    ADCON1 = 0x0F;
    
    // Interrupt initial
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1; //open priority
    
    // Internal Oscillator Frequency, Fosc = 4MHz, Tosc = 0.25 ?s
    OSCCONbits.IRCF = 0b110;
    
    // set RB0 to input -> button for interrupt 
    // -> trigger motor to select a song
    TRISEbits.RE0 = 1; //input
//    __delay_ms(20);
    
    while(1){
        LATB = 0x00;
        LATEbits.LATE1 = 0;
        LATEbits.LATE2 = 0;
        LATC = 0x00;
        LATD = 0xff;
        initTimer2andCCP1();
        __delay_ms(30);
        while(PORTEbits.RE0==1); //polled wait for button pressed
    
        //start to choose song
        pickSong();
        while(playing == 0);
        
        if(playing == 1){
            led_index=0;
            reinitCCP1();
            TIMER1_Initial();
            led_index = -1; 
            // PORTA for button pressed -> set to input
            TRISA = 0xFF; //button input

            // PORTD for LED
            TRISB = 0x00; //led output
            TRISCbits.RC4 = 0;
            TRISCbits.RC5 = 0;
            TRISCbits.RC6 = 0;
            TRISCbits.RC7 = 0;
            TRISD = 0x00;
            TRISEbits.RE1 = 0;
            TRISEbits.RE2 = 0;
            LATB = 0x00;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 0;
            LATC = 0x00;
//            LATCbits.LATC4 = 0;
//            LATCbits.LATC5 = 0;
//            LATCbits.LATC6 = 0;
//            LATCbits.LATC7 = 0;
            LATD = 0xff;
        }
        
        while(playing == 1);
    }
    return;
}

void TIMER1_Initial(void){
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    T1CONbits.RD16=0b1;//16 mode
    T1CONbits.T1CKPS=0b11; //8
    if(song_pick==0){
        TMR1H=158;//0.25s
        TMR1L=88;//0.25s
    }
    else if(song_pick==1){
//        T1CONbits.T1CKPS=0b10; //8
        T1CONbits.T1CKPS=0b01; //test
        TMR1H=232;//0.25s
        TMR1L=72;//0.25s
    }
    else if(song_pick==2){
        T1CONbits.T1CKPS=0b01; //8
        TMR1H=232;//0.25s
        TMR1L=72;//0.25s
    }
    else if(song_pick==3){
        T1CONbits.T1CKPS=0b01; //8
        TMR1H=232;//0.25s
        TMR1L=72;//0.25s
    }
    PIE1bits.TMR1IE=1;
    PIR1bits.TMR1IF=0;
    IPR1bits.TMR1IP=0; //low priority
    T1CONbits.TMR1ON=1;
}

void initTimer2andCCP1(){
    // Timer2 -> On, prescaler -> 16
    T2CONbits.TMR2ON = 0b1;
    T2CONbits.T2CKPS = 0b10;

    // Internal Oscillator Frequency, Fosc = 4 MHz, Tosc = 1/4M = 0.25 ?s
    OSCCONbits.IRCF = 0b0110;
    
    // PWM mode, P1A, P1C active-high; P1B, P1D active-high
    CCP2CONbits.CCP2M = 0b1100;
    
    // CCP2/RC1 -> Output
    TRISCbits.RC1 = 0;
//    LATC = 0;
    
    // Set up PR2, CCP to decide PWM period and Duty Cycle
    /* 
     * PWM period
     * = (PR2 + 1) * 4 * Tosc * (TMR2 prescaler)
     * = (0x9b + 1) * 4 * 0.25us * 16
     * = 2496us
     */
    PR2 = 0x9b;
    
    /*
     * Duty cycle
     * = (CCPR1L:CCP1CON<5:4>) * Tosc * (TMR2 prescaler)
     * = (0x0b*4 + 0b01) * 0.25?s * 16
     * = 0.00180s ~= 1800?s
     */
    
    //0.25?s * 16 = 4
    
    // -90 : 500us, 500 / 4 = 125, 125 = 4*31 + 1, CCPR1L = 0x1F; CCP1CONbits.DC1B = 0b01;
    // -45 : 975us, 975 / 4 = 243.75, 244 = 4*61 + 0. CCPR1L = 0x3D; CCP1CONbits.DC1B = 0b00;
    // 0: 1450us, 1450 / 4 = 362.5, 363 = 4*90 + 3, CCPR1L = 0x5A; CCP1CONbits.DC1B = 0b03;
    // 45 : 1925us, 1925 / 4 = 481.25, 481 = 120*4 + 1, CCPR1L = 0x78; CCP1CONbits.DC1B = 0b01;
    // 90 : 2400us, 2400 / 4 = 600, 515 = 150*4 + 0, CCPR1L = 0x96; CCP1CONbits.DC1B = 0b00;
    CCPR2L = 0x1F;
    CCP2CONbits.DC2B = 0x01;
}

void pickSong(){
    int random_number = rand();
    song_pick = random_number % SONG_NUM;
//    song_pick = 2;
    int clockwise = 0;
    for(int i = 2000; i > 0; i--){
            if(!clockwise){
                if (CCP2CONbits.DC2B != 0x03) {
                    CCP2CONbits.DC2B ++;
                }
                else{
                    CCPR2L++;
                    CCP2CONbits.DC2B = 0;
                }
                if (CCPR2L == 0x96 && CCP2CONbits.DC2B == 0x00) {
                    clockwise = 1;
                }
            }else{
                if (CCP2CONbits.DC2B != 0x00) {
                    CCP2CONbits.DC2B --;
                }
                else{
                    CCPR2L--;
                    CCP2CONbits.DC2B = 0x03;
                }
                if (CCPR2L == 0x1F && CCP2CONbits.DC2B == 0x01) {
                    clockwise = 0;
                    if(i < 500) break;
                }
            }
            __delay_ms(6);
        }
        int nums_nieh[4] = {45, 89, 105, 149}; 
        int num_of_CCPR2L = nums_nieh[song_pick];
        while(CCPR2L != num_of_CCPR2L){
            if(!clockwise){
                if (CCP2CONbits.DC2B != 0x03) {
                    CCP2CONbits.DC2B ++;
                }
                else{
                    CCPR2L++;
                    CCP2CONbits.DC2B = 0;
                }
                if (CCPR2L == 0x96 && CCP2CONbits.DC2B == 0x00) {
                    clockwise = 1;
                }
            }else{
                if (CCP2CONbits.DC2B != 0x00) {
                    CCP2CONbits.DC2B --;
                }
                else{
                    CCPR2L--;
                    CCP2CONbits.DC2B = 0x03;
                }
                if (CCPR2L == 0x1F && CCP2CONbits.DC2B == 0x01) {
                    clockwise = 0;
                }
            }
            __delay_ms(6);
        }    
    __delay_ms(5000);
    CCPR2L = 0x1F;
    CCP2CONbits.DC2B = 0x01;
    __delay_ms(40);
//    TRISCbits.RC1 = 1; //close motor
    CCP2CONbits.CCP2M = 0b0000;
    __delay_ms(5000);
    playing = 1;
    return;
}

void get_Notes(int img_time,int Note[]){ 
    // if time = 0 
    for(int i = 0; i < 12; i ++){ // init RD 
     B[i] = 0; 
     C[i] = 0; 
     D[i] = 255; 
     E[i] = 0; 
   } 
     
    for(int i = 0; i < 6; i++){//each row in RB, time 0 ~ 5 
        int curr_state = i; 
        int curr_note = Note[ curr_state + img_time ] - 1; 
        if(Note[ curr_state + img_time] >= 0){ 
            B[curr_state]+=BECset[curr_state]; 
            D[curr_state]=Dset[curr_note];
        } 
    } 
     
    for(int i = 1; i <= 2; i++){//each row in RE, time 6 ~ 7 
        int curr_state = i + 5; 
        int curr_note = Note[ curr_state + img_time ] - 1; 
        if(Note[ curr_state + img_time] >= 0){ 
            E[curr_state]+=BECset[curr_state]; 
            D[curr_state]=Dset[curr_note]; 
        }
    } 
     
    for(int i = 4; i <= 7; i++){//each row in RC, time 8 ~ 11
        int curr_state = i + 4; 
        int curr_note = Note[ curr_state + img_time ] - 1; 
        if(Note[ curr_state + img_time] >= 0){ 
            C[curr_state]+=BECset[curr_state]; 
            D[curr_state]=Dset[curr_note]; 
        } 
    } 
}

void sing(void){ 
    if(song_pick == 0){
        get_Notes(led_index,star_Note);
    }
    else if(song_pick == 1){
//        get_Notes(led_index,forever_Note);
        get_Notes(led_index,forever_Note);
    }
    else if(song_pick == 2){
        get_Notes(led_index,Xmas_Note);
    }
    else if(song_pick == 3){
        get_Notes(led_index,sakura_Note);
    }
    while(PIR1bits.TMR1IF == 0){
        for(int state_index=0; state_index < STATE_NUM ;state_index++){
           LATE=E[state_index];
           LATC=C[state_index];
           LATB=B[state_index];
           LATD=D[state_index];
           __delay_ms(1);
           button_pressed_check();
       }   
    }
}
