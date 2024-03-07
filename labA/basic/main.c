#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
// using namespace std;

char str[20];

void main(void) 
{
    
    SYSTEM_Initialize() ;
    UART_Initialize();
    while(1);
    return;
}

void __interrupt(high_priority) H_ISR(void)
{
;
}