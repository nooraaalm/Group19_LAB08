#include <stdint.h>
#include "tm4c123gh6pm.h"


void UART0_Init(void);
char UART0_Received(void);
void UART0_Send(char data);
void LED_Init(void);
void LED_ON_OFF(char choice);

