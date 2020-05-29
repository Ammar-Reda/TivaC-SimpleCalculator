#ifndef lcd_H_
#define lcd_H_

#define SYSCTL_RCGC2_R          (*((volatile uint32_t *)0x400FE108))

//port B, PIN7-0 connected to the data pins
#define GPIO_PORTB_AMSEL_R      (*((volatile uint32_t *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile uint32_t *)0x4000552C))
#define GPIO_PORTB_DIR_R        (*((volatile uint32_t *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile uint32_t *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile uint32_t *)0x4000551C))
#define GPIO_PORTB_DATA_R       (*((volatile uint32_t *)0x400053FC))

//Port D, PIN5 -> RS, PIN4 -> EN
#define GPIO_PORTD_AMSEL_R      (*((volatile uint32_t *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile uint32_t *)0x4000752C))
#define GPIO_PORTD_DIR_R        (*((volatile uint32_t *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile uint32_t *)0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile uint32_t *)0x4000751C))
#define GPIO_PORTD_DATA_R       (*((volatile uint32_t *)0x400073FC))

#define GPIO_PORTD_LOCK_R       (*((volatile uint32_t *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile uint32_t *)0x40007524))

#define clear_display 						0x01
#define return_home  	 						0x02
#define firstRowLocation0					0x80
#define secondRowLocation0 				0xC0

typedef   signed          char int8_t;
typedef unsigned           int uint32_t;

void lcd_Init(void);
void lcd_command(int8_t cmd);
void lcd_send_char(int8_t data);
void lcd_send_string(char *str);

#endif
