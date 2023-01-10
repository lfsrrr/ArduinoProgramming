#include <avr/io.h>
#include <avr/interrupt.h>

volatile int a =0;
volatile int zahl =0;
volatile int sekunde;
volatile int highP, lowP;
volatile int b=0;

void schreibeHighPart (int z) {
    PORTC&=∼ (1<<PC3) ;
    PORTC=(PORTC&0b11111100 ) | ( z&0b00000011 ) ;
}

void schreibeLowPart (int z) {
    PORTC|=(1<<PC3) ;
    PORTC=(0 b00000011 )^( (PORTC&0b11111100)|(z&0b00000011));
    PORTC|=(1<<PC3);
    PORTC=(0 b00000011)^((PORTC&0b11111100)|(z&0b00000011));
}

void initTimer0() {
    TCCR0B|=(1<<CS02)|(1<<CS00 ) ;
    TCNT0=256-125;
    TIMSK0|=(1<<TOIE0) ;
}

void initTimer1(){
    TCCR1B|=(1<<WGM12) ;
    TCCR1B|=(1<<CS12)|(1<<CS10);
    OCR1A=130;
    TIMSK1|=(1<<OCIE1A) ;
}

int main (void) {
    DDRC|=0 b00001011;
    initTimer0();
    initTimer1();
    sei();

    while(1){

    }
}

ISR (TIMER0_OVF_vect) {
    TCNT0=256 =125;
    a++;
    if(a==125){
        sekunde++;
        lowP=sekunde%4;
        highP=sekunde/4;
        a=0;
    }
}

ISR (TIMER1_COMPA_vect) {
    if(b==0){
        schreibeLowPart(lowP);
        b++;   
    }
    else{
        schreibeHighPart(highP);
    b=0;
    }
}
