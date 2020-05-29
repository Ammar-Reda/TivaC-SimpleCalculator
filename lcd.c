#include "lcd.h"
#include "delay.h"

void lcd_Init(void){volatile unsigned long c_delay;
 SYSCTL_RCGC2_R |= 0x0000000A; // 1) activate clock for Port D,B 1010
 c_delay = SYSCTL_RCGC2_R; // allow time for clock to start
	
	//DATA PORTB PIN7-0
 GPIO_PORTB_AMSEL_R = 0x00; // 3) disable analog on PB
 GPIO_PORTB_PCTL_R = 0x00000000; // 4) PCTL GPIO on PB7-0
 GPIO_PORTB_DIR_R = 0xFF; // 5) PE out
 GPIO_PORTB_AFSEL_R = 0x00; // 6) disable alt funct on PF7-0
 GPIO_PORTB_DEN_R = 0xFF; // 7) enable digital I/O on PE7-0
 
	//RS EN PORTD PIN5 PIN4
 GPIO_PORTD_LOCK_R = 0x4C4F434B; // 2) unlock GPIO Port F
 GPIO_PORTD_CR_R |= 0x30; // allow changes to PF4-0
 GPIO_PORTD_AMSEL_R &= ~0x30; // 3) disable analog on PD5-4
 GPIO_PORTD_PCTL_R &= ~0x00FF0000; // 4) PCTL GPIO on PD5-4
 GPIO_PORTD_DIR_R |= 0x30; // 5) PD5-4 out
 GPIO_PORTD_AFSEL_R &= ~0x30; // 6) disable alt funct on PD5-4
 GPIO_PORTD_DEN_R |= 0x30; // 7) enable digital I/O on PD5-4

	
	//Initializing The LCD
 GPIO_PORTB_DATA_R = 0x00; 		//data port is 00 as init value
 GPIO_PORTD_DATA_R &= ~0x10;  //clear E,  (PORTD PIN4)
	
	//after power up should wait about 15ms before sending initializing commands to the LCD	
	delay_ms(2); 

	lcd_command(0x38);     //init. LCD 2 lines, 5 x 7 matrix
	lcd_command(0x0E);		 //display on, cursor on
	lcd_command(0x01);     //clear LCD 
	delay_ms(2); 					 //wait
	lcd_command(0x06);     //shift cursor right
	
}

void lcd_command(int8_t cmd){
		GPIO_PORTB_DATA_R = cmd;     			//send command to data port
		GPIO_PORTD_DATA_R &= ~0x20;  			//RS 0 for command (PORTD PIN5)
		GPIO_PORTD_DATA_R |=  0x10;  			//EN =1 for H - L Pulse,  (PORTD PIN4)
		delay_us(1); 						 					//wait to make enable wide
		GPIO_PORTD_DATA_R &= ~0x10;  			//clear E,  (PORTD PIN4)
		delay_us(100); 						 				//wait to make enable wide
}

void lcd_send_char(int8_t data){
		GPIO_PORTB_DATA_R = data;     		//send command to data port
		GPIO_PORTD_DATA_R |= 	0x20;  			//RS 1 for data (PORTD PIN5)
		GPIO_PORTD_DATA_R |=  0x10;  			//EN =1 for H - L Pulse,  (PORTD PIN4)
		delay_us(1); 						 					//wait to make enable wide
		GPIO_PORTD_DATA_R &= ~0x10;  			//clear E,  (PORTD PIN4)
		delay_us(100); 						 				//wait to make enable wide
}

void lcd_send_string(char *str){
	int8_t i =0;
	while(str[i]!=0){lcd_send_char(str[i]) ; i++;}
}
