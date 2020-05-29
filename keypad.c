#include "keypad.h"
#include "delay.h"

// Define the Keymap
/*
char keys_map[4][4] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};*/
char current_key = 'n';

char keys_map[4][4] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'c','0','=','/'}
};

/// rows output portD 
/// cols input portE
uint8_t col, row;

void keypad_Init(void){ volatile unsigned long delay;
 SYSCTL_RCGC2_R 			|= 0x00000018; 				// 1) activate clock for Port E, D
 delay = SYSCTL_RCGC2_R; // allow time for clock to start
 
	//COLS PORTE PIN3-0 INPUT
 GPIO_PORTE_AMSEL_R 	&= ~0x0F; 			// 3) disable analog on PE
 GPIO_PORTE_PCTL_R 		&= ~0x0000FFFF; // 4) PCTL GPIO on PE3-0
 GPIO_PORTE_DIR_R 		&= ~0x0F; 			// 5) PF3-0 input pins
 GPIO_PORTE_AFSEL_R 	&= ~0x0F; 			// 6) disable alt funct on PE3-0
 GPIO_PORTE_DEN_R 		|= 0x0F; 				// 7) enable digital I/O on PE3-0
 
	//ROWS PORTD PIN3-0 OUTPUT
 GPIO_PORTD_AMSEL_R 	&= ~0x0F; 			// 3) disable analog on PD
 GPIO_PORTD_PCTL_R 		&= ~0x0000FFFF; // 4) PCTL GPIO on PD3-0
 GPIO_PORTD_DIR_R 		|= 0x0F; 				// 5) PD3-0 output pins
 GPIO_PORTD_AFSEL_R 	&= ~0x0F; 			// 6) disable alt funct on PD7-0
 GPIO_PORTD_DEN_R 		|= 0x0F; 				// 7) enable digital I/O on PD4-0
}

char keypad_getKey(void){
	
/*		
		do
		{
			GPIO_PORTD_DATA_R &= ~0x0F;
			col = GPIO_PORTE_DATA_R & 0x0F;
		}while(col != 0x0F);
*/	
		do{
			do{
				delay_ms(20);  											//delay 20ms
				col = GPIO_PORTE_DATA_R & 0x0F; 		//see if any key pressed
			}while(col == 0x0F);									//keep checking for key pressed 
			
			delay_ms(20);  												//call delay 20ms for debounce
			col = GPIO_PORTE_DATA_R & 0x0F; 			//read cols
		}while(col == 0x0F);	
	
		while(1){
			GPIO_PORTD_DATA_R |= 0x0E;           //ground row 0;    //
			col = GPIO_PORTE_DATA_R & 0x0F; 		  //read cols
			
			if(col != 0x0F){   										//column detected 
				row = 0;														//save row location
				break;															//exit while loop
			}
		
			GPIO_PORTD_DATA_R |= 0x0D;           //ground row 1;   //D
			col = GPIO_PORTE_DATA_R & 0x0F; 		  //read cols
			
			if(col != 0x0F){   										//column detected 
				row = 1;														//save row location
				break;															//exit while loop
			}
		
			GPIO_PORTD_DATA_R |= 0x0B;           //ground row 2;  //B
			col = GPIO_PORTE_DATA_R & 0x0F; 		  //read cols
			
			if(col != 0x0F){   										//column detected 
				row = 2;														//save row location
				break;															//exit while loop
			}
			
			GPIO_PORTD_DATA_R |= 0x07;           //ground row 3;
			col = GPIO_PORTE_DATA_R & 0x0F; 		  //read cols
			
			if(col != 0x0F){   										//column detected 
				row = 3;														//save row location
				break;															//exit while loop
			}	
		}
		
		//check column and send save result to currentkey;
		if(col == 0x0E)
			current_key = (keys_map[row][0]);
		else if (col == 0x0D)
			current_key = (keys_map[row][1]);
		else if (col == 0x0B)
			current_key = (keys_map[row][2]);
		else if (col == 0x07)
			current_key = (keys_map[row][3]);
		
		//wait for all keys to be released//
		do
		{
			GPIO_PORTD_DATA_R &= ~0x0F;
			col = GPIO_PORTE_DATA_R & 0x0F;
		}while(col != 0x0F);                    

	return current_key;
}

