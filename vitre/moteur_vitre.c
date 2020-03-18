#include "C:\Users\33695\Documents\git\software-semester2\architecture\TP\moteur_vitre.h"

#define descend INPUT(PIN_B2)
#define remonte INPUT(PIN_B1)

#define remontecomp INPUT(PIN_B0)
#define descendcomp INPUT(PIN_B3)

#define fch INPUT(PIN_B6)
#define fcb INPUT(PIN_B7)


#define m_desc OUTPUT_D(0b11)
#define m_mont OUTPUT_D(0b01)
#define m_stop OUTPUT_D(0b00)

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
   while(true){
      if(remonte && !fch){
         m_mont;
      }

      if(!remonte && !descend){
         m_stop;
      }

      if(descend && !fcb){
         m_desc;
      }

int i;
int up,down;
      if(remonte && !fch && !descend);
      {
        m_mont;
        i=0;
        while (remonte)
        {
           delay_ms(100);
           i++;
           if(i>=15){
            up=1;
           }
        }
         
      }
      


   }
}
