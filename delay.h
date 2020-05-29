#ifndef delay_H_
#define delay_H_

typedef   signed           int int32_t;
typedef unsigned           int uint32_t;

#define NVIC_ST_CTRL_R          (*((volatile uint32_t *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile uint32_t *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile uint32_t *)0xE000E018))
#define NVIC_SYS_PRI3_R         (*((volatile uint32_t *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile uint32_t *)0xE000E010))

//void SysTick_Initialize(uint32_t ticks);              //SysTick_Initialize
void delay_ms_Init(void);              //SysTick_Initialize
void delay_ms(uint32_t time);
void delay_us(uint32_t time);

#endif
