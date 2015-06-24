
#include "SanUSB1.h"//Display de 7seg conta de 0 a 9

unsigned char set_seg[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; 
int i;

void interrupcao(){}

void main(){
    clock_int_4MHz();
    TRISB = 0b00000000;
    nivel_baixo(pin_c0);

    while(1){
        for(i = 0; i<10; i++){
          //  if(i %2 != 0){ //Apenas números ímpares
                PORTB = set_seg[i];
                tempo_ms(500);
          //  }
        }
    }
}
