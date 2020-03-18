#include "C:\Users\33695\Desktop\main.h"


void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!
   output_d(0b100001);   
   while(true){
      delay_ms(5000);
      if (input(pin_b7))
      {
         output_d(0b010001);
         delay_ms(1000);         
         output_d(0b001001);
         delay_ms(1000);
         output_d(0b100001);
      }      
      delay_ms(5000);
      if (input(pin_b5))
         {
         output_d(0b010001);
         delay_ms(1000);         
         output_d(0b001100);
         delay_ms(1000);         
         output_d(0b001010);
         delay_ms(1000);
         output_d(0b100001);
         delay_ms(1000);
         }
   }

}
