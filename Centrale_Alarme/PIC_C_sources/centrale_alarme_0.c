#include "C:\Users\33695\Documents\git\pic_c_alarme\Centrale_Alarme\PIC_C_sources\centrale_alarme_0.h"
// numpad config
   // columns
   int KeypadInput=0;
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
   int32 timeDelay=30;//retard avant armement
   int32 timeTempo=20;//temporisation au declenchement  en secondes des zones differees
   int32 timeDeclench=180;//duree maximum de declenchement (limite à 180)
   int32 nbrRearm;//Nombre de rearmements automatiques autorises après un declenchement 
//timers
   int32 timer_alarm = 0;
   int32 timer_last_alarm = 0;
   int32 timer_activation = 0;
   int32 timer_change_code = 0;
   int dix=0,sec=55,min=1; // time units
   int T1=0,T2=0,T3=0; // timers
   int timer,enableTimer;
//other
   int alarm_active = 0;

/**--------------------------------FUNCTIONS---------------------------------**/  

/**-----------------------------------MODIFICATION PARAM---------------------**/

void ARM(){alarm_active=1;}
void DISARM(){alarm_active=0;}


//raz reglages alarme
void reset(){printf("[ALARME REMISE A ZERO] \n\r");codeArm=33;codeDisarm=1664;timeDelay=30;timeTempo=20;timeDeclench=180;nbrRearm=2;}
void changeArm(int newArm){codeArm=newArm;printf("[NOUVEAU CODE ARMEMENT: %lu ]\n\r",codeArm);}
void changeDisarm(int newDisarm){codeDisarm=newDisarm;printf("[NOUVEAU CODE DESARMEMENT: %lu ]\n\r",codeDisarm);}
void changeDelay(int newTimeDelay){timeDelay=newTimeDelay;printf("[NOUVEAU DELAI ZONE DIFFEREE: %lu ]\n\r",timeDelay);}
void changeTempor(int newTempo){timeTempo=newTempo;printf("[NOUVEAU TEMPORIS DECLENCH: %lu ]\n\r",timeTempo);}
void changeDeclench(int newDeclench){timeDeclench=newDeclench;printf("[NOUVEAU TEMPS MAX DECLENCH: %lu ]\n\r",timeDeclench);}
void changeRearm(int newRearm){nbrRearm=newRearm;printf("[NOUVEAU NBR MAX DESARMEMENT: %lu ]\n\r",nbrRearm);}

void keypadInputRead()
{
   if(keypadInput==990000){reset();} // RaZ
   if(keypadInput>=1000 && keypadInput<1100){changeArm(keypadInput-1000);} // chg code arm
   if(keypadInput==110000 && keypadInput<120000){changeDisarm(keypadInput-110000);} // chg code desarmement
   if(keypadInput>=2000 && keypadInput<2100){changeDelay(keypadInput-2000);}// retard zone diff
   if(keypadInput>=2100 && keypadInput<2200){changeTempor(keypadInput-2100);}//temporisation
   if(keypadInput>=30000 && keypadInput<30180){changeDeclench(keypadInput-30000);} //duree declenc
   if(keypadInput>=3100 && keypadInput<3200){changeRearm(keypadInput-30000);} //nbr rearm auto
   if(keypadInput==codeArm){ARM();}
   keypadInput=0;
}




/**-----------------------------------SONNERIES-----------------------------**/

void beep(){
   buzzer_on;
   delay_ms(500);
   buzzer_off;
   delay_ms(500);
}


void trigger_alarm(int time, int cooldown)
{
   timer_alarm = time; //the alarm rings for Xs
   timer_last_alarm = cooldown; //the alarm can't be trigered during the x next seconds
   while(!timer_alarm && alarm_active && timer_last_alarm==0)
   {
      buzzer_on;
   }
   buzzer_off;

   

}

void beeper(int time, int cooldown)
{

}




/**-----------------------------------DETECTEURS-----------------------------**/

int detect_im(){
   int result=false;
   if (c_im1){result=true;output_high(pin_c1);}else{output_low(pin_c1);}
   if (c_im2){result=true;output_high(pin_c2);}else{output_low(pin_c2);}
   if (c_im3){result=true;output_high(pin_c5);}else{output_low(pin_c5);}
   if (c_im4){result=true;output_high(pin_c4);}else{output_low(pin_c4);}
   return result;
}

int detect_ret(){
   int result=0;
   if (c_ret1){result=1;output_high(pin_e0);}else{output_low(pin_e0);}
   if (c_ret2){result=1;output_high(pin_e1);}else{output_low(pin_e1);}
   return result;
}









// prototypage
/**
   void keypadInputRead();
   void reset();
   void changeArm(int newArm);
   void changeDisarm(int newDisarm);
   void changeDelay(int newTimeDelay);
   void changeTempor(int newTempo);
   void changeDeclench(int newDeclench);
   void changeRearm(int newRearm);
   void ARM();
   void DISARM();

   int detect_im();
   int sensor_ret();

**/


/**--------------------------------INTERRUPTS-------------------------------**/  


#int_TIMER1
void  TIMER1_isr(void) //each .1 seconds
{
   /**
   set_timer1(3036);
   dix++;
   if(dix==10){sec++;dix=0;T1++;T2--;T3++;}
   if(sec==60){min++;sec=0;}
   if(timer_alarm!=0 && dix==10){timer_alarm--;printf("#! \r\n");}   
   if(timer_last_alarm!=0){timer_last_alarm--;}
   if(timer_activation!=0){timer_activation--;}
   if(timer_change_code!=0){timer_change_code--;}
   **/

   if(enableTimer==1){
      set_timer1(3036);
      dix++;
      if(dix>=10){
         dix=0;
         sec++;
      }
      
      if(sec>=60){
         sec=0;
         min++;
      }
   }
}

#int_EXT
void  EXT_isr(void) 
{
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
   if(l4){printf("#");keypadInputRead();}
   // reset columns
   c1h;c2h;c3h;
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
   T1=100; // en sec
   T2=3600; // en sec

   c1h;c2h;c3h;
   int pass=0;
    while (true)
   {
      
   
     // printf("timer_alarm:%lu \n\r",timer_alarm);
      /**
      printf("timer_alarm:%lu last:%lu \n\r",timer_alarm,timer_last_alarm);
      if(alarm_active){
         output_high(pin_c0);

         if(detect_im() && !timer_last_alarm)
         {
            printf("Intrusion detectee");
            trigger_alarm(10,5);
         }
         
         if(detect_ret()==1)
         {
            if(!timer_activation) //alarm is not active yet
            {
               // utiliser beep() pour avertir de la temporisation
               
                  
            }
            else if(!timer_last_alarm) //alarm is active
            {
               trigger_alarm(180,300);///A CHANGER POUR TEST
            }
         }
      }
      else
      {
         output_low(pin_c0);
      }
      **/
   }
}
