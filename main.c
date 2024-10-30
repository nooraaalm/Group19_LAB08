#include <stdint.h>
#include "tm4c123gh6pm.h"


void UART0_Init(void);
char UART0_Received(void);
void UART0_Send(char data);
void LED_Init(void);
void LED_ON_OFF(char choice);
int main(void) {

    UART0_Init();

    char receivedChar;
    while (1) {

        receivedChar = UART0_Received();
        UART0_Send(receivedChar);
        LED_ON_OFF(receivedChar);
    }
}
void LED_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_DEN_R |= 0x0E;
}
void UART0_Init(void) {
 SYSCTL_RCGCUART_R |= 0x01;
        SYSCTL_RCGCGPIO_R |= 0x01;          // Enable PORTA

        UART0_CTL_R &= ~0x01;               // Disable UART0
        UART0_IBRD_R = 104;                 // Set integer part for baud rate (assuming 16 MHz and 9600 baud)
        UART0_FBRD_R = 11;                  // Set fractional part for baud rate
        UART0_LCRH_R = 0x70;                // 8-bit, no parity, 1-stop bit, FIFOs
        UART0_CTL_R = 0x301;                // Enable UART0, TX, and RX

        GPIO_PORTA_AFSEL_R |= 0x03;         // Enable PA0 and PA1 as alternate function
        GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x11;
        GPIO_PORTA_DEN_R |= 0x03;
}

char UART0_Received(void) {
    while ((UART0_FR_R & 0x10) != 0);
    return UART0_DR_R & 0xFF;           // Read and return the received character
}

// Send data to UART0
void UART0_Send(char data) {
    while ((UART0_FR_R & 0x20) != 0);   // Wait until the transmitter is not full
    UART0_DR_R = data;                  // Send the character
}
void LED_ON_OFF(char choice) {
    GPIO_PORTF_DATA_R &= ~0x0E;
    if(choice=='R') {

            GPIO_PORTF_DATA_R |= 0x02;
    }
    else if(choice=='B') {
  GPIO_PORTF_DATA_R |= 0x04;
       }
    else if(choice=='G') {

               GPIO_PORTF_DATA_R |= 0x08;
       }
    else {
        GPIO_PORTF_DATA_R |= 0x00;
    }
}
