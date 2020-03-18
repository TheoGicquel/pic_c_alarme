#include "D:\Cours\M2101\TP\m2101\TP Alarme\PIC C\main.h"
#define b1 input(PIN_B1)
#define b2 input(PIN_B2)
#define b3 input(PIN_B3)
#define b4 input(PIN_B4)
#define b5 input(PIN_B5)
#define b6 input(PIN_B6)
#define buzzer(1) output_high(pin_a0)
#define buzzer(0) output_low(pin_a0)
#define masterArmSwitch output_c
#define ledb1 output_c(0b01)
#define ledb2 output_c(0b001)
#define ledb3 output_c(0b000001)
#define ledb4 output_c(0b00001)
#define ledb5 output_e(0b1)
#define ledb6 output_e(0b01)
#define AlarmOn Output_high(PIN_B7)
#define AlarmOff Output_low(PIN_B7)
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


int32 dix = 0, timer = 0, timerStart = 0;
int masterArm = 1;
int entry = 0;

#int_TIMER1
void  TIMER1_isr(void) 
{
   if(timerStart == 1){
      set_timer1(3036);
      dix++;
      if(dix>=10){
         dix=0;
         timer++;
      }
      timer=timer%500;
   }
}

#int_EXT
void  EXT_isr(void) 
{
   // column 1
   c1h;c2l;c3l;
   if(l1){printf("1");entry=10*entry+1;}
   if(l2){printf("4");entry=10*entry+4;}
   if(l3){printf("7");entry=10*entry+7;}
   if(l4){printf("*");}

   // column 2
   c1l;c2h;c3l;
   if(l1){printf("2");entry=10*entry+2;}
   if(l2){printf("5");entry=10*entry+5;}
   if(l3){printf("8");entry=10*entry+8;}
   if(l4){printf("0");entry=10*entry;}

   // column 3
   c1l;c2l;c3h;
   if(l1){printf("3");entry=10*entry+3;}
   if(l2){printf("6");entry=10*entry+6;}
   if(l3){printf("9");entry=10*entry+9;}
   if(l4){printf("#");Read();}
   
   // reset columns
   c1h;c2h;c3h;
}

void Read()
{
   //instructions
   entry=0;
}

void MasterArmON()
{
   timerStart = 1;
   while(timer<30){
      buzzer(1);
   }
   buzzer(0);
   timerStart = 0;
   timer = 0;
   master
}

void alarm(){
   timerStart = 1;
   while(timer<180){
      AlarmON;
   }
   AlarmOff;
   timerStart=0;
   timer = 0;
}

int instant(){
   int bool = 0;
   if(!b1 || !b2 || !b3 || !b4){
      bool = 1;
   }
   
   if(b1){
      ledb1;
   }else if(b2){
      ledb2;
   }else if(b3){
      ledb3;
   }else if(b4){
      ledb4;
   }
   
   return bool;
}

int retarded(){
   int bool = 0;
   if(!b5 || !b6){
      bool = 1;
   }
   
   if(b5){
      ledb5;
   }else if(b6){
      ledb6;
   }
   return bool;
}

void retardedLaunch(){
   timerStart = 1;
   while(timer<20){
      buzzer(1);
   }
   buzzer(0);
   timerStart = 0;
   timer = 0;
   alarm();
}

void check(){
   if(retarded() == 1 && instant() == 0){
      masterArm = 0;
      retardedLaunch();
   }else if(instant() == 1){
      masterArm = 0;
      alarm();
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
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!
   while(true){
      /*if(masterArm == 1){
         check();
         masterArmSwitch(masterArm);
      }*/
   }
}
