// main.c
// Runs on TM4C123 using the simulator
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "keypad.h"
#include "lcd.h"
#include "delay.h"

void tostring(char str[], int16_t num);
void displayResult(char num1, char op, char num2);
void sendResultNumber(char result[]);

int main(void){
char result_str[10];
char num1, op, num2;
int8_t result, ipart;
float result_div, fpart;
delay_ms_Init();
lcd_Init();
keypad_Init();

	while(1){
		
		//read first number//
		lcd_send_string("num1 : ");
		do{
			num1 = keypad_getKey();
			lcd_command(firstRowLocation0 + 0x07);   							// set cursor location at (0,8)
			lcd_send_char(num1);
		}while(num1 == '+' || num1 == '-' || num1 == '*' || num1 == '/' || num1 == '=');					//repeat until a number is detected

		//read operation//
		lcd_command(clear_display);
		lcd_send_string("op :   ");
		do{
			op = keypad_getKey();
			lcd_command(firstRowLocation0 + 0x07);   							// set cursor location at (0,8)
			lcd_send_char(op);
		}while(	op == '=' || (op < 58 && op > 48) );    	// ascii code of 0 = 48, 9 = 57
		
		//read second number//
		lcd_command(clear_display);
		lcd_command(return_home);
		lcd_send_string("num2 : ");
		do{
			num2 = keypad_getKey();
			lcd_command(firstRowLocation0 + 0x07);   							// set cursor location at (0,8)
			lcd_send_char(num2);
		}while(num1 == '+' || num1 == '-' || num1 == '*' || num1 == '/' || num1 == '=');             //repeat until a number is detected
		
		//compute result //
		if(op == '+'){		
			result = (num1 - 48) + (num2 - 48);
			
			tostring(result_str, result);
			displayResult(num1, op, num2);
			sendResultNumber(result_str);
		}
		else if(op == '-'){
			if(num1 > num2){
				result = (num1 - 48) - (num2 - 48);
				
				tostring(result_str, result);
				displayResult(num1, op, num2);
				sendResultNumber(result_str);
			}else{
				result = (num2 - 48) - (num1 - 48);
				
				tostring(result_str, result);
				displayResult(num1, op, num2);
				sendResultNumber(result_str);
			}
		}
		else if(op == '*'){			
				result = (num1 - 48) * (num2 - 48);
				tostring(result_str, result);
				displayResult(num1, op, num2);
				sendResultNumber(result_str);
		}
		else{
				result_div = (float)(num1 - 48) / (float)(num2 - 48);
				ipart  = (int8_t)result_div;
				tostring(result_str, ipart);
				if(ipart == result_div){                   //no floating part
					displayResult(num1, op, num2);
					sendResultNumber(result_str);
				}else{                                     //floating part
					fpart = result_div - (float)ipart;
					fpart = (int8_t)(fpart * 10);            //only first number after the decimal point
					
					displayResult(num1, op, num2);
					sendResultNumber(result_str);             //integar part
					lcd_send_char('.');												//decimal point					
					lcd_send_char(fpart + 48);								//fraction part
				}
		}
		
		
			lcd_command(secondRowLocation0);            //Force cursor to beginning ( 2nd line)
			lcd_send_string("press 1 for reset");	
			
			while(keypad_getKey() != '1'){};
			lcd_command(clear_display);
	} 	
}


void tostring(char str[], int16_t num)
{
	int i, rem, len = 0, n;

	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
}

void displayResult(char num1, char op, char num2){
		lcd_command(clear_display);
		lcd_send_char(num1);
		lcd_send_char(op);
		lcd_send_char(num2);
		lcd_send_char('=');
}

void sendResultNumber(char result[]){
		int i =0;
		while(result[i] != '\0'){
			lcd_send_char(result[i]);
			i++;
		}
}
