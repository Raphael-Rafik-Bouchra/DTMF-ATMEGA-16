/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : DTMF_LCD
Version : 
Date    : 5/17/2022
Author  : 
Company : 
Comments: 


Chip type               : ATmega16A
Program type            : Application
AVR Core Clock frequency: 11.059200 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16a.h>
#include <delay.h>
// Alphanumeric LCD functions
#include <alcd.h>
#include <string.h>

// Declare your global variables here
int keydetect = 0;
int i = 0;
char* password = "1234";
int password_len = 4;
char* current_password = "";
char* new_password = "";
char current_char = '';
int prog_mode = 0;

//Declaring Functions
char get_char();
int check_password();

interrupt[EXT_INT0] void ext_int0_isr(void){

  keydetect = 1;
  delay_ms(250);  
}

interrupt[EXT_INT1] void ext_int1_isr(void){
  //Start Timer  
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10); 

}

interrupt[EXT_INT2] void ext_int2_isr(void){
delay_ms(200);
  //Stop Timer
  TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10); 
    //Reset Timer
  TCNT1H=0xAB;
  TCNT1L=0xA0;
  ICR1H=0x00;
  ICR1L=0x00;
  OCR1AH=0x54;
  OCR1AL=0x5F;
  OCR1BH=0x00;
  OCR1BL=0x00;
  
//Checking New Password
         if(strlen(new_password) > 0){ 
            strcpy(password,new_password);
            password_len = strlen(new_password);
            new_password = strcpy(new_password,"");
         }

  //Reset programming Mode 
  lcd_clear();
  lcd_gotoxy(0,0); 
  delay_ms(10);
  lcd_puts("Enter Password:");
  delay_ms(250); 
  prog_mode = 0;
  i=0;    

}


interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
// Place your code here
    prog_mode = 1; 
    lcd_clear();
    delay_ms(10); 
    i=0;
    lcd_gotoxy(0,1); 
    lcd_puts(password);
    delay_ms(10);
}



void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 2
// EN - PORTA Bit 1
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 16
lcd_init(16);


GICR |= (1<<INT1) | (1<<INT0) | (1<<INT2);
MCUCR = (1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00);
MCUCSR = (0<<ISC2);
GIFR = (1<<INTF1) | (1<<INTF0) | (1<<INTF2);



// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 10.800 kHz
// Mode: CTC top=OCR1A
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Rising Edge
// Timer Period: 2 s
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0xAB;
TCNT1L=0xA0;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x54;
OCR1AL=0x5F;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);



#asm("sei");

          lcd_gotoxy(0,0); 
          delay_ms(10);
          lcd_puts("Enter Password:");
          delay_ms(10);

while (1)
      {
      // Place your code here
      if(prog_mode == 0){    
          if (i > 15){ 
            lcd_clear();
            i = 0; 
            }
           
          if(keydetect){ 
             keydetect = 0;
             current_char = get_char();
             delay_ms(10);
             lcd_gotoxy(i,1);  
             delay_ms(10);
             lcd_putchar(current_char);
             delay_ms(10);
             i++;
             current_password = strncat(current_password,&current_char,1);
          
          }   
           
          if(strlen(current_password) == password_len){
            if(check_password()){
                 lcd_clear();
                 lcd_gotoxy(0,0);
                 delay_ms(10);  
          
                 lcd_puts("Correct Password");
                 delay_ms(2000);
                 lcd_clear();
            }else{ 
                 lcd_clear();
                 lcd_gotoxy(0,0);
                 delay_ms(10);  
          
                 lcd_puts("Wrong Password");
                 delay_ms(2000);
                 lcd_clear(); 
            }
            i=0;
            strcpy(current_password,"");  
            lcd_gotoxy(0,0); 
          delay_ms(10);
          lcd_puts("Enter Password:");
          delay_ms(10); 
          }
       }
      else{ 
       //Programming Mode  
       lcd_gotoxy(0,0); 
      delay_ms(10);
          lcd_puts("New Password:");
          delay_ms(10);
           
          if (i > 15){ 
            lcd_clear();
            i = 0; 
            }
           
          if(keydetect){   
             keydetect = 0;
             current_char = get_char(); 
             lcd_gotoxy(i,1);  
             delay_ms(10);
             lcd_putchar(current_char);
             delay_ms(10);
             i++;
             new_password = strncat(new_password,&current_char,1);
          
          }
         
      } 
    }
}

char get_char()
{

     switch (PINC & 0x0F)
			{   
				case (0x01): 
                return '1';
				
				case (0x02):
				return '2';;
				
				case (0x03):
				return '3';;
				
				case (0x04):
				return '4';
				
				case (0x05):
				return '5';
				
				case (0x06):
				return '6';
				
				case (0x07):
				return '7';
				
				case (0x08):
				return '8';

				case (0x09):
				return '9';
				
				case (0x0A):
				return '0';
				
				case (0x0B):
				return '*';
				
				case (0x0C):
				return '#';

				default:
				break;
			}      
    
}

int check_password()
{
            if(strcmp(current_password,password) == 0)   
            {  
                 return 1; 
                 
            }else{ 
                 return 0;
            }  
}

