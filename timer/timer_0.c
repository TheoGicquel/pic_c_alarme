#include "C:\Users\33695\Documents\git\software-semester2\architecture\TP\timer\timer_0.h"
#define presRAZ INPUT(PIN_B0)

#define M1 PIN_C3
#define M2 PIN_C4
#define S1 PIN_C5
#define S2 PIN_E0
#define C1 PIN_E1
#define C2 PIN_E2


int cent=0,sec=0,min=0;
int flag;
#int_TIMER1

void  TIMER1_isr(void) 
{ 
   set_timer1(15536);
   // on passe ici tous les centièmes de secondes
   cent++;
   if(cent==100){
      sec++;
      cent=0;
   }
   
   if(sec==60){
   min++;
   }
}

#int_EXT
void  EXT_isr(void) 
{
min=0;sec=0;cent=0;
}

#int_EXT1
void  EXT1_isr(void) 
{
   flag=!flag;
   if(flag){
      enable_interrupts(INT_TIMER1);
   }
   else
   {
   disable_interrupts(INT_TIMER1);
   }

}



void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_timer_2(T2_DISABLED,0,1);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts(GLOBAL);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!



while(true){
   printf("elapsed time %u M %u S %u C\n\r",min,sec,cent);

   output_d(sec%10);
   output_high(pin_e0);
   delay_us(5);
   output_low(pin_e0);
   
   output_d((sec%100)-(sec%10));
   output_high(pin
   

}

}
