#include "C:\Users\33695\Documents\git\software-semester2\architecture\TP\Centrale_Alarme\PIC_C_sources\centrale_alarme_1.h"
// numpad config
   // columns
   #define c1h output_high(pin_d0)
   #define c1l output_low(pin_d0)

   #define c2h output_high(pin_d1)
   #define c2l output_low(pin_d1)

   #define c3h output_high(pin_d2)
   #define c3l output_low(pin_d2)

   // rows
   #define l1 input(pin_d3)
   #define l2 input(pin_d4)
   #define l3 input(pin_d5)
   #define l4 input(pin_d6)

#define buzzer_on output_high(pin_a0)
#define buzzer_off output_low(pin_a0)

#int_TIMER1
void  TIMER1_isr(void) 
{

}

#int_EXT1
void  EXT1_isr(void) 
{

}



void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT1);
   enable_interrupts(GLOBAL);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!

}
