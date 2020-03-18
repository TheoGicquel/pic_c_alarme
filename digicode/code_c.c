#include "C:\Users\33695\Documents\git\software-semester2\architecture\TP\digicode\code_c.h"


#define ligne1 input(pin_B4)
#define ligne2 input(pin_B5)
#define ligne3 input(pin_B6)
#define ligne4 input(pin_B7)

#define colgauche output_d(1)
#define colmilieu output_d(2)
#define coldroite output_d(4)

int32 n=0;

void open(){
  printf("\n\r CODE VALIDE \n\r");
}

void close(){

}

void incorrect(){
  printf("\n\r CODE NON VALIDE  \n\r");
}






#int_EXT
void  EXT_isr(void) 
{ disable_interrupts(INT_EXT);

colgauche; // active colonne de gauche
if(ligne1){printf("1");n=10*n+1;}
if(ligne2){printf("4");n=10*n+4;}
if(ligne3){printf("7");n=10*n+7;}
if(ligne4){printf("*");}

colmilieu;
if(ligne1){printf("2");n=10*n+2;}
if(ligne2){printf("5");n=10*n+5;}
if(ligne3){printf("8");n=10*n+8;}
if(ligne4){printf("0");n=10*n;}

coldroite;
if(ligne1){printf("3");n=10*n+3;}
if(ligne2){printf("6");n=10*n+6;}
if(ligne3){printf("9");n=10*n+9;}
if(ligne4){printf("\n\r[%lu] \n\r",n);
    if(n==1664){open();}
    else{incorrect();}
    
    n=0;
}

output_d(7);
enable_interrupts(INT_EXT);
}


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
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!
   output_d(7);
   while (true)
   {
     
   }
   

}