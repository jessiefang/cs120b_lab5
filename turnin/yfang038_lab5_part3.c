/*      Author: lab
 *  Partner(s) Name: N/A
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Init, Next, Reset} state;

unsigned char i = 0x00;
unsigned array[8] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F};
void Tick() {
    switch (state) {
        case Start:
                state = Init;
                break;
        case Init:
                if((~PINA & 0x01) == 0x01){
                        state = Next;
                        break;
                }else{
                        state = Init;
                        break;
                }
        case Next:
                for(i = 0; i<8; i++){
                        _delay_ms(250);
                        PORTC = array[i];
                }
                i = 0;
                _delay_ms(1000);
                 for(i = 7; i>=0; i--){
                        _delay_ms(250);
                        PORTC = array[i];
                }
                i = 0;
                PORTC = 0;
                state = Init;
                break;

}
  }
int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    while (1) {
        Tick();
    }
    return 1;
}
