#ifndef keypad_H_
#define keypad_H_

//#include "delay_us.h"
typedef   signed          char int8_t;
typedef unsigned           int uint32_t;
typedef unsigned          char uint8_t;


#define SYSCTL_RCGC2_R          (*((volatile uint32_t *)0x400FE108))

//Port E, PIN 3-0 connected to the rows
#define GPIO_PORTE_AMSEL_R      (*((volatile uint32_t *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile uint32_t *)0x4002452C))
#define GPIO_PORTE_DIR_R        (*((volatile uint32_t *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile uint32_t *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile uint32_t *)0x4002451C))
#define GPIO_PORTE_DATA_R       (*((volatile uint32_t *)0x400243FC))

//Port D, PIN 3-0 connected to the columns
#define GPIO_PORTD_AMSEL_R      (*((volatile uint32_t *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile uint32_t *)0x4000752C))
#define GPIO_PORTD_DIR_R        (*((volatile uint32_t *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile uint32_t *)0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile uint32_t *)0x4000751C))
#define GPIO_PORTD_DATA_R       (*((volatile uint32_t *)0x400073FC))
	

void keypad_Init(void);
char keypad_getKey(void);

#endif
