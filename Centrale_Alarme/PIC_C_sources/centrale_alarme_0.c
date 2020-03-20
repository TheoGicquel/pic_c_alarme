#include "C:\Users\33695\Documents\git\pic_c_alarme\Centrale_Alarme\PIC_C_sources\centrale_alarme_0.h"
// numpad config
   // columns
   int32 KeypadInput=0;
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
// sensors
   // immediat
   #define c_im1 input(pin_b1)
   #define c_im2 input(pin_b2)
   #define c_im3 input(pin_b3)
   #define c_im4  input(pin_b4)
   // retarded
   #define c_ret1 input(pin_b5)
   #define c_ret2 input(pin_b6)
//buzzer
   #define buzzer_on output_high(pin_a0)
   #define buzzer_off output_low(pin_a0)
//default parameters
   int32 codeArm=33;//code armement
   int32 codeDisarm=1664;//code desarmement
   int32 timeDelay=30;//delai avant armement apres entree du code
   int32 timeTempo=20;//temp avant alerte dans des zones differees
   int32 timeDeclench=180;//duree maximum de declenchement (limite à 180)
   int32 timeRearm=0;//delai avant rearmement une fois duree maximum ecoulee
   int32 nbrRearm;//Nombre de rearmements automatiques autorises après un declenchement 
   int32 timer_alert = 0;
   //int32 timer_activation = 0;
   //int32 timer_change_code = 0;
   int16 dix=0,sec=0;//min=0; // time units
   //int16 T1=0,T2=0,T3=0; // timers
   //int16 timer,enableTimer;
//other
   int alarm_active = 0;

/**--------------------------------FUNCTIONS---------------------------------**/  

/**-----------------------------------MODIFICATION PARAM---------------------**/

void ARM()
{
   alarm_active=1;
   output_high(pin_c0);
   printf("Alarme active dans 30 secondes \n\r");
   
   while(timer_alert!=0 && alarm_active)
   {
      buzzer_on;
      delay_ms(100);
   }
}

void DISARM(){
   alarm_active=0;
   output_low(pin_c0);
   printf("Alarme stoppee \n\r");}


//raz reglages alarme
void reset(){printf("[ALARME REMISE A ZERO] \n\r");codeArm=33;codeDisarm=1664;timeDelay=30;timeTempo=20;timeDeclench=180;timeRearm=0;nbrRearm=2;}
void changeArm(int newArm){codeArm=newArm;printf("[NOUVEAU CODE ARMEMENT: %lu ]\n\r",codeArm);}
void changeDisarm(int newDisarm){codeDisarm=newDisarm;printf("[NOUVEAU CODE DESARMEMENT: %lu ]\n\r",codeDisarm);}
void changeDelay(int newTimeDelay){timeDelay=newTimeDelay;printf("[NOUVEAU DELAI ZONE DIFFEREE: %lu ]\n\r",timeDelay);}
void changeTempor(int newTempo){timeTempo=newTempo;printf("[NOUVEAU TEMPORIS DECLENCH: %lu ]\n\r",timeTempo);}
void changeDeclench(int newDeclench){if(newDeclench<180){timeDeclench=newDeclench;}else{timeDeclench=180;} printf("[NOUVEAU TEMPS MAX DECLENCH: %lu ]\n\r",timeDeclench);}
void changeRearm(int newRearm){nbrRearm=newRearm;printf("[NOUVEAU NBR MAX DESARMEMENT: %lu ]\n\r",nbrRearm);}

void keypadInputRead()
{
   if(alarm_active==0){
      if(keypadInput==990000){reset();} // RaZ
      if(keypadInput>=1000 && keypadInput<1100){changeArm(keypadInput-1000);} // chg code arm
      if(keypadInput==110000 && keypadInput<120000){changeDisarm(keypadInput-110000);} // chg code desarmement
      if(keypadInput>=2000 && keypadInput<2100){changeDelay(keypadInput-2000);}// retard zone diff
      if(keypadInput>=2100 && keypadInput<2200){changeTempor(keypadInput-2100);}//temporisation
      if(keypadInput>=30000 && keypadInput<30180){changeDeclench(keypadInput-30000);} //duree declenc
      if(keypadInput>=3100 && keypadInput<3200){changeRearm(keypadInput-30000);} //nbr rearm auto
      if(keypadInput==codeArm){ARM();}
   }else
   {
      if(keypadInput==codeDisarm){DISARM();}      
   }
   
   keypadInput=0;
}




/**-----------------------------------SONNERIES-----------------------------**/

void beep(){
   buzzer_on;
   delay_ms(200);
   buzzer_off;
   delay_ms(800);
}


void trigger_alert()
{
   timer_alert = timeDeclench; //the alarm rings for Xs
   while(timer_alert!=0 && alarm_active)
   {
      buzzer_on;
      delay_ms(100);
   }
   buzzer_off;
   timer_alert = timeDelay; //the alarm can't be trigered during the x next seconds

   

}


void trigger_tempo()
{
   timer_alert=timeTempo;
   while (timer_alert!=0 && alarm_active)
   {
      beep();
   }
   
}

/**-----------------------------------DETECTEURS-----------------------------**/

int detect_im(){
   int result=0;
   if (c_im1){result=1;output_high(pin_c1);}else{output_low(pin_c1);}
   if (c_im2){result=1;output_high(pin_c2);}else{output_low(pin_c2);}
   if (c_im3){result=1;output_high(pin_c5);}else{output_low(pin_c5);}
   if (c_im4){result=1;output_high(pin_c4);}else{output_low(pin_c4);}
   return result;
}

int detect_ret(){
   int result=0;
   if (c_ret1){result=1;output_high(pin_e0);}else{output_low(pin_e0);}
   if (c_ret2){result=1;output_high(pin_e1);}else{output_low(pin_e1);}
   return result;
}


/**--------------------------------INTERRUPTS-------------------------------**/  


#int_TIMER1
void  TIMER1_isr(void) //each .1 seconds
{
   disable_interrupts(INT_TIMER1);

     
      set_timer1(3036);
      dix++;
      if(dix>=10){
         dix=0;
         sec++;
         if (timer_alert>0){timer_alert--;}
         if (timeRearm>0 && !timer_alert){timeRearm--;}
      }

  enable_interrupts(INT_TIMER1);
}

#int_EXT
void  EXT_isr(void) 
{
   disable_interrupts(INT_EXT);
   // column 1
   c1h;c2l;c3l;
   if(l1){printf("1");keypadInput=10*keypadInput+1;}
   if(l2){printf("4");keypadInput=10*keypadInput+4;}
   if(l3){printf("7");keypadInput=10*keypadInput+7;}
   if(l4){printf("*");}
   // column 2
   c1l;c2h;c3l;
   if(l1){printf("2");keypadInput=10*keypadInput+2;}
   if(l2){printf("5");keypadInput=10*keypadInput+5;}
   if(l3){printf("8");keypadInput=10*keypadInput+8;}
   if(l4){printf("0");keypadInput=10*keypadInput;}
   // column 3
   c1l;c2l;c3h;
   if(l1){printf("3");keypadInput=10*keypadInput+3;}
   if(l2){printf("6");keypadInput=10*keypadInput+6;}
   if(l3){printf("9");keypadInput=10*keypadInput+9;}
   if(l4){printf("#\r\n");keypadInputRead();}
   // reset columns
   c1h;c2h;c3h;
   enable_interrupts(INT_EXT);
}


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
  // T1=100; // en sec
   //T2=3600; // en sec

   c1h;c2h;c3h;

   
while (1)
   {      
      if(alarm_active){
         if(detect_im() && !timeRearm && !timeDelay)
         {
            printf("Intrusion detectee");
            trigger_alert();
         }

         if(detect_ret())
         {
            if(!timeRearm) //alarm is active
            {
               trigger_tempo();
               trigger_alert();///A CHANGER POUR TEST
            }
         }
      }
   }
}
