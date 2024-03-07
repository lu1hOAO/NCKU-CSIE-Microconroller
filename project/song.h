#ifndef	_Song
#define _Song
void reinitCCP1();
void delay_ms(unsigned int milliseconds);
void speaker(unsigned char tone);
void button_pressed_check();
void get_Notes(int time,int Note[]);
void sing();
#endif 