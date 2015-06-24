#include "SanUSB1.h"

#pragma interrupt interrupcao 
void interrupcao(){}

void main(){
clock_int_4MHz();
taxa_serial(19200);

while(1)
{
if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação

    if(PIR1bits.RCIF)         //Flag que indica byte na USART - Serial_avaliable()
                        {
            PIR1bits.RCIF = 0;   //reset flag
                                   switch(RCREG)// byte recebido 
                                            {
                                            case 'L': nivel_alto(pin_b7); 
                                             break;//Chega L acende o led

                                             case 'D' : nivel_baixo(pin_b7);
                                             break;//Chega D apaga o led

                                             }

                           }
  }
}
