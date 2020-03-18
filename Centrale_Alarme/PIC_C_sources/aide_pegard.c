#include "C:\Users\33695\Documents\git\software-semester2\architecture\TP\Centrale_Alarme\PIC_C_sources\centrale_alarme_0.h"

// numpad config
   // columns
   #define c1h output_high(pin_d0)
   #define c1l output_low(pin_d0)

   #define c2h output_high(pin_d1)
   #define c2l output_low(pin_d1)

   #define c3h output_high(pin_d2)
   #define c3l output_low(pin_d2)

   // row
   #define l1 input(pin_d3)
   #define l2 input(pin_d4)
   #define l3 input(pin_d5)
   #define l4 input(pin_d6)


// Memory
int32 input=0;
int8 dix=0,sec=0,min=0; // time units
int16 T1=0,T2=0,T3=0; // timers

/**--------------------------------INTERRUPTS-------------------------------**/  


#int_TIMER1
void  TIMER1_isr(void) //each .1 seconds
{
   set_timer1(3036);
   printf("#! \r\n");}
   
}

#int_EXT
void  EXT_isr(void) 
{
   // column 1
   c1h;c2l;c3l;
   if(l1){printf("1");input=10*input+1;}
   if(l2){printf("4");input=10*input+4;}
   if(l3){printf("7");input=10*input+7;}
   if(l4){printf("*");}

   // column 2
   c1l;c2h;c3l;
   if(l1){printf("2");input=10*input+2;}
   if(l2){printf("5");input=10*input+5;}
   if(l3){printf("8");input=10*input+8;}
   if(l4){printf("0");input=10*input;}

   // column 3
   c1l;c2l;c3h;
   if(l1){printf("3");input=10*input+3;}
   if(l2){printf("6");input=10*input+6;}
   if(l3){printf("9");input=10*input+9;}
   if(l4){printf("#");inputRead();}
   
   // reset columns
   c1h;c2h;c3h;
}

/**--------------------------------FUNCTIONS---------------------------------**/  



/**-----------------------------------MAIN-----------------------------------**/  
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
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab
   T1=100; // en sec
   T2=3600; // en sec

   c1h;c2h;c3h;
   
    while (true)
   {

   }
}
