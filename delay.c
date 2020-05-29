#include "delay.h"
volatile int32_t TimeDelay;

void delay_ms_Init (void){
NVIC_ST_CTRL_R = 0; // disable SysTick during setup
NVIC_ST_RELOAD_R = 16000 - 1;// reload value
NVIC_ST_CURRENT_R = 0; // any write to current clears it
NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
NVIC_ST_CTRL_R = 0x04; // enable SysTick with core clock and interrupts
// enable interrupts after all initialization is finished
}

void SysTick_Handler (void) { // SysTick interrupt service routine
if (TimeDelay > 0) // Prevent it from being negative
	TimeDelay --; // TimeDelay is a global volatile variable
}
void delay_ms(uint32_t time ){ //nTime : specifies the delay time length
NVIC_ST_CTRL_R |= 0x03; 
TimeDelay= time ; // TimeDelay must be declared as volatile
while(TimeDelay != 0); // Busy wait
NVIC_ST_CTRL_R &= ~0x03; 
}

void delay_us(uint32_t time)
{
int i, j;
for(i = 0 ; i < time; i++)
  for(j = 0; j < 2; j++){}
}

