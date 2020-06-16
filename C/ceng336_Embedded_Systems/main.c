//Group 50
//Kadir Burak TOKMAK e2036200
//Emrah KOSEN e1942317
//Furkan INALCIK e2171643
//THE3 tested on board, board test video link: https://drive.google.com/open?id=1PT0b-zG5SGsf0nIPd4SsqoiKPkgznr1C
#pragma config OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF



#include <xc.h>
#include "breakpoints.h"


int val;

int seven_flag;
int is_blink; // in blink, if light or dim
int ADC_update;// flag for seven segment to update new adc value
int counter_tmr0;
int counter_tmr1; //100 times
int gameOver;  //guess correct or 5 seconds time up
int can_guess; //rb4_handled
int init_flag; //restart flag
int rb4_counter; //counting pressed
int rb4_release; // counting released
int adc_counter; //adc sample timer


int seven_segment_lookup_table[]={
    0b00111111,                     // 7-Segment = 0
    0b00000110,                     // 7-Segment = 1
    0b01011011,                     // 7-Segment = 2
    0b01001111,                     // 7-Segment = 3
    0b01100110,                     // 7-Segment = 4
    0b01101101,                     // 7-Segment = 5
    0b01111101,                     // 7-Segment = 6
    0b00000111,                     // 7-Segment = 7
    0b01111111,                     // 7-Segment = 8
    0b01100111,                     // 7-Segment = 9
    0b01000000,                     // 7-Segment = -
};



void init(void)
{
  TRISB=0;
  PORTB = 0; // Clear PORTB
  LATB = 0; // Clear LATB
  val=0;
  is_blink = 0;
  counter_tmr0 = 0;
  counter_tmr1 = 0;
  gameOver = 0;
  ADC_update = 0;
  can_guess = 0;
  init_flag = 0;
  adc_counter=0;
  rb4_counter=0;
  rb4_release = 0;
  adc_value=0;
  seven_flag=0;
  INTCON = 0;   // Clear INTCON and disable all interrupts

  INTCON = 0x28; // 
  RCONbits.IPEN = 0; // Disable priorities on interrupts

  PORTC = 0;
  LATC = 0;
  TRISC = 0b00000000;
  PORTD = 0;
  LATD = 0;
  TRISD = 0b00000000;

  PORTE = 0;
  LATE = 0;
  TRISE = 0b00000000;
  TRISH4=1;
  ADCON0 = 0x30; // Select channel 12 -- 00110000
  ADCON1 = 0x00; // set all channels as analog and select voltage references
  ADCON2 = 0x82;

  ADCON0bits.ADON = 1;  // Enable A/D Converter
  PIR1bits.ADIF = 0;  // Clear A/D Converter Interrupt Flag bit
  PIE1bits.ADIE = 1;  // Enable A/D Converter Interrupt



  PORTB = 0; // Clear PORTB
  LATB = 0; // Clear LATB
  TRISB=0;
  TRISB4=1;
  INTCONbits.RBIE=1;
  INTCONbits.RBIF=0;
  INTCON2bits.RBPU = 1;// disable pull-ups
  INTCONbits.INT0IE=1;
  INTCONbits.INT0IF=0;

  TRISH = 0xF0; // Set PORTH<3:0> 7 segment display output 11110000
  TRISJ = 0;  // Configure PORTJ as output since we will use it to show seven segment display.
  LATJ = 0;   // Clear LATJ
  LATH = 0;   // Clear LATH


  TMR0L = 61;//with 256 prescaler 5ms every interrupt




  PIE1bits.TMR1IE = 1; // Enable TMR1
  PIR1bits.TMR1IF = 0; // Clear TMR1 interrupt flag
  T1CON = 0xB0; // Configure TMR1 as 16 bit and set a prescaler value 1:8 -- 10110000
  TMR1 = 3036; // for 50ms for every interrupt
  T0CON = 0x47; // 01000111 -- Configure TMR0. Used 8 bit mode and 1:256 prescaler




  T0CONbits.TMR0ON=1; //tmr0 is on
  T1CONbits.TMR1ON=1; //tmr1 is on
  T1CONbits.RD16=1; //16bit mode r/w
  T1CONbits.T1CKPS0=1; // 8 prescaler
  T1CONbits.T1CKPS1=1; // 8 prescaler
  PIE1bits.TMR1IE = 1; //TMR1 Overflow Interrupt is Enabled

  GIE = 1; // INTCON Becomes 10101000 (0xA8) -- Enable GIE-TIMER0-RB interrupts.
  init_complete();
}





int Map_Intervals(void) // assign val from table
{
  if(adc_value >= 0 && adc_value <= 102 ) 
    return 0;
  else if(adc_value >= 103 && adc_value <= 204 )
    return 1;
  else if(adc_value >= 205 && adc_value <= 306 )
    return 2;
  else if(adc_value >= 307 && adc_value <= 408 )
    return 3;
  else if(adc_value >= 409 && adc_value <= 510 )
    return 4;
  else if(adc_value >= 511 && adc_value <= 612 )
      return 5;
  else if(adc_value >= 613 && adc_value <= 714 )
    return 6;
  else if(adc_value >= 715 && adc_value <= 816 )
    return 7;
  else if(adc_value >= 817 && adc_value <= 918 )
    return 8;
  else if(adc_value >= 819 && adc_value <= 1023 )
    return 9;
  else
      return -1;
}









void __interrupt() myISR(void)
{

  if(INTCONbits.TMR0IF == 1)
  {
    TMR0L = 61;// 256 prescaler 5ms interrupt
    counter_tmr0++;
    INTCONbits.TMR0IF = 0;//clear interrupt flag

    if(counter_tmr0 == 10)
    {
      ADC_update = 1;//Read ADC value to Seven segment flag
      counter_tmr0 = 0;
    }
    if(!gameOver){
      adc_counter++;
      if (adc_counter==10){
          ADCON0bits.GO_DONE = 1; // Start A/D conversion
          adc_counter=0;   //adc conversion every 50ms
      }
    }
    if(PORTBbits.RB4==0 && !gameOver ) //if released check if debounce
    {
      rb4_release++;
      if(rb4_release >= 2)//if 5x2=10ms passed its a real release not debounce
        rb4_counter = 5;//set rb4 counter high so it doesn't trigger rb4_handled.
    }

    if(!gameOver && PORTBbits.RB4==1){
        rb4_counter++;
        if(rb4_counter==2){
            can_guess=1;
            rb4_handled();//rb4 is on for at least 10ms user can guess, rb is handled
        }
    }
  }



  if(PIR1bits.ADIF == 1)
  {
    PIR1bits.ADIF = 0; // Reset flag back to 0
    adc_value = ADRES;   // Save the result in a variable given by breakpoints.h
    adc_complete(); //called when we read the value from ADC 0-1024 VALUE
  }

  if(INTCONbits.RBIF == 1)
  {
  	if(PORTBbits.RB4==1 && !gameOver)
    {
  		INTCONbits.RBIF = 0;
      if(rb4_release >= 2)//if real release reset counter for pressed
        rb4_counter=0;//if entered before 10ms passes resets the counter. This handles Debouncing problem.
  	}

  	else
    {
      rb4_release = 0; //new press, reset release counter 
  		INTCONbits.RBIF = 0;
  	}


  }
  if(PIR1bits.TMR1IF == 1)
  {


    TMR1 = 3036; // for 50ms for every interrupt
    PIR1bits.TMR1IF = 0;// Reset flag,
    if(!gameOver)
    {
      ++counter_tmr1;
      if(counter_tmr1%10==0){
        hs_passed(); //called every 500ms during game
      }
      if(counter_tmr1 == 100)
      {
        gameOver = 1;//5second is up
        INTCONbits.RBIE=0; //disable rb interrupt since gameover state
        counter_tmr1 = 40;//set up timer1 for 2 second blink phase
        is_blink = 1;//first blink state is up handled by seven_segment function
        seven_flag=1;//set up flag for seven segment function
        LATC = 0x00;
        LATD = 0x00;
        LATE = 0x00; // clear hints, times up
        latcde_update_complete();//hints updates time up
        game_over();// game over with time up function
      }

    }
    else
    {
        counter_tmr1=counter_tmr1-1;
      if( counter_tmr1>0 && counter_tmr1%10==0 ){
        is_blink = !is_blink;//change blink state handled by seven_segment function later
        seven_flag=1;
        hs_passed(); //called every 500ms after game over while blinking
      }
      else if(counter_tmr1==0)
      {
        hs_passed();//right before init(restart), last blink ends
        init_flag = 1;//flag for restart of the game
      }
    }

  }


}

void seven_segment(void)
{

  if(gameOver)
  {

    if(is_blink)
    {
      //true special val
	  LATJ= seven_segment_lookup_table[special_number()];//show the correct answer
	  LATH3 = 1;
    }
    else{
      LATJ = 0;//blink empty
      LATH3 = 1;
    }

  }

  else
  {
    LATJ = seven_segment_lookup_table[val];//show the val got from ADC
	  LATH3 = 1;
  }

latjh_update_complete();//calls every time when seven segment function ending
}

int Guess_It()//check if correct guess
{
  if (special_number()==val){
	return 1;
  }
  else{
	return 0;
  }
}

void Give_Hint()
{
  //Up or Down
  if(special_number()>val) //up
  {
    LATC = 0x02;
    LATD = 0x0F;
    LATE = 0x02;

  }
  else //down arrow
  {
    LATC = 0x04;
    LATD = 0x0F;
    LATE = 0x04;

  }

}


void main(void) {
    init();

    while(1)
    {
      if(init_flag){
        restart();//just before program restarts
        init();
	  }

      if(gameOver == 0 && ADC_update == 1)
      {
        ADC_update = 0;
        val = Map_Intervals();//ADC_value updated, convert into 0-9 range
        seven_flag=1;//update seven segment for new 0-9 value
      }

      if(seven_flag==1){
        seven_flag=0;
        seven_segment();//seven segment updated
      }

      if( can_guess && !gameOver) // RB4
      {
        can_guess = 0;
        if(Guess_It() )
        {
          INTCONbits.RBIE=0; //disable rb interrupt
          counter_tmr1 = 41;//set timer1 for 2 second total
          gameOver = 1;//guess was correct gameover state
          //seven_flag=1;
          LATC = 0x00;
          LATD = 0x00;
          LATE = 0x00;
          correct_guess();// guessed corretly gameOver state is set and no longer will read ADC updates beyond this point

        }
        else
        {
          LATC = 0x00;
          LATD = 0x00;
          LATE = 0x00;
          Give_Hint();

        }
        latcde_update_complete();//rb4 pressed guess correct=cleared, guess wrong=hint
      }




    }



    /*init_complete();
    adc_value =5;
    adc_complete();
    rb4_handled();
    latjh_update_complete();
    latcde_update_complete();
    correct_guess();
    hs_passed();
    game_over();
    restart();
    special_number();*/
    return;
}
