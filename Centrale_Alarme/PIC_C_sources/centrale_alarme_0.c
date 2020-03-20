#include "C:\Users\33695\Documents\git\pic_c_alarme\Centrale_Alarme\PIC_C_sources\centrale_alarme_0.h"
/*******************************************************************************
 *      Thibaud MACRET    -   Theo GICQUEL     )      GROUPE F
 ******************************************************************************/

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
   int16 timer_beep=0;
   int16 defaultBoucle=0; 
   int16 ARM_ON=0;
   int16 ALERT_ON=0;
   int16 TEMPO_ON=0;
   

   int16 dix=0,sec=0;//min=0; // time units
  int intrusion=0;
//other
   int alarm_active = 0;

/**--------------------------------FUNCTIONS---------------------------------**/
// prototypages indispensables  
void beep(); int detect_im(); int detect_ret();void keypadInputRead(); void DISARM(); void ARM();
void changeArm(int);
void changeDisarm(int);
void changeDelay(int);
void changeTempor(int);
void changeDeclench(int);
void changeRearm(int);
void reset();

/**--------------------------------INTERRUPTS-------------------------------**/  

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






#int_TIMER1
void  TIMER1_isr(void) //each .1 seconds
{
   disable_interrupts(INT_EXT);disable_interrupts(INT_TIMER1);

      
               
      set_timer1(3036);
      dix++;
      if(timer_beep>0){timer_beep--;}

      if(dix>=10){
         dix=0;
         sec++;
         if (timer_alert>0){timer_alert--;}
         if (timeRearm>0 && !timer_alert){timeRearm--;}
      }


   // printing area
   if(intrusion){printf("Intrusion detectee");}
   if(defaultBoucle==1){defaultBoucle=2;printf("Defaut de boucle \n\r");}



   enable_interrupts(INT_EXT);enable_interrupts(INT_TIMER1);
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


/**-----------------------------------MODIFICATION PARAM---------------------**/

void ARM()
{  defaultBoucle=0; 
   timer_alert=timeDelay;
   output_high(pin_c0);
   printf("Alarme active dans %lu secondes \n\r",timer_alert);
   ARM_ON=1;
}

void DISARM(){
   defaultBoucle=0;
   alarm_active=0;
   output_low(pin_c0);
   printf("Alarme stoppee \n\r");
}


//raz reglages alarme
void reset(){printf("[ALARME REMISE A ZERO] \n\r");codeArm=33;codeDisarm=1664;timeDelay=30;timeTempo=20;timeDeclench=180;timeRearm=0;nbrRearm=2;}
void changeArm(int newArm){codeArm=newArm;printf("[NOUVEAU CODE ARMEMENT: %lu ]\n\r",codeArm);}
void changeDisarm(int newDisarm){codeDisarm=newDisarm;printf("[NOUVEAU CODE DESARMEMENT: %lu ]\n\r",codeDisarm);}
void changeDelay(int newTimeDelay){timeDelay=newTimeDelay;printf("[NOUVEAU DELAI ZONE DIFFEREE: %lu ]\n\r",timeDelay);}
void changeTempor(int newTempo){timeTempo=newTempo;printf("[NOUVEAU TEMPORIS DECLENCH: %lu ]\n\r",timeTempo);}
void changeDeclench(int newDeclench){if(newDeclench<180){timeDeclench=newDeclench;}else{timeDeclench=180;} printf("[NOUVEAU TEMPS MAX DECLENCH: %lu ]\n\r",timeDeclench);}
void changeRearm(int newRearm){nbrRearm=newRearm;printf("[NOUVEAU NBR MAX DESARMEMENT: %lu ]\n\r",nbrRearm);}





/**-----------------------------------SONNERIES-----------------------------**/

void beep(){
   buzzer_on;
   delay_ms(200);
   buzzer_off;
   delay_ms(800);
}



/**-----------------------------------DETECTEURS-----------------------------**/
// si capteur immediat active
int detect_im(){
   disable_interrupts(INT_EXT);disable_interrupts(INT_TIMER1);
   int result=0;
   if (c_im1){result=1;output_high(pin_c1);}else{output_low(pin_c1);}
   if (c_im2){result=1;output_high(pin_c2);}else{output_low(pin_c2);}
   if (c_im3){result=1;output_high(pin_c5);}else{output_low(pin_c5);}
   if (c_im4){result=1;output_high(pin_c4);}else{output_low(pin_c4);}
   enable_interrupts(INT_EXT);enable_interrupts(INT_TIMER1);
   return result;
}
// si capteur differre active
int detect_ret(){
   disable_interrupts(INT_EXT);disable_interrupts(INT_TIMER1);
   int result=0;
   if (c_ret1){result=1;output_high(pin_e0);}else{output_low(pin_e0);}
   if (c_ret2){result=1;output_high(pin_e1);}else{output_low(pin_e1);}
      enable_interrupts(INT_EXT);enable_interrupts(INT_TIMER1);
   return result;
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
   c1h;c2h;c3h;

   // debug area
   timeDelay=5;
   timeTempo=3;
   timeDeclench=10;
   
while (true)
   {

      if(ARM_ON)
      {
         if(timer_alert!=0)
         {  
            if(detect_im()){
               if(defaultBoucle==0){defaultBoucle=1;}
               buzzer_on;
            }
            else
            {
               beep();
            }

            if(timer_alert==0 && defaultBoucle==0){
            
               alarm_active=1;

               ARM_ON=0;
               buzzer_off;
            }
         }
      }

      if(alarm_active)
      {

         if(detect_im() && timeRearm==0 && timeDelay==0)
         {
            if(ALERT_ON==0){
            timer_alert = timeDeclench; //the alarm rings for Xs
            intrusion=1;
            ALERT_ON=1;  
            }
         }
      
         if(ALERT_ON && timer_alert!=0)
         {
            buzzer_on;
         }
         if(ALERT_ON && timer_alert==0){
            buzzer_off;
            timer_alert=timeRearm;
            ALERT_ON=0;
         }


         if(detect_ret())
         {
            if(TEMPO_ON==0) //alarm is active
            {
               timer_alert=timeTempo;
               TEMPO_ON=1;
            }

            if(TEMPO_ON==1 && timer_alert!=0){
             beep();
            }

            if (TEMPO_ON==1 && timer_alert==0)
            {
               alarm_active=1;
            }   
         }
      }
      
   }
}