#include "SanUSB.h"

void main(){

   while (TRUE)
   {
   output_high(pin_B0); // Verde
   delay_ms(500);
   if (!input(pin_e3)){reset_cpu();} //se pressionar o bot�o no pino 1, reseta e entra em estado de grava��o

   output_low(pin_B0);
   output_high(pin_B6); //Amarelo
   delay_ms(500);
   if (!input(pin_e3)){reset_cpu();} 

   output_low(pin_B6); //Vermelho
   output_high(pin_B7);
   delay_ms(500);
   output_low(pin_B7);
   if (!input(pin_e3)){reset_cpu();} 
   }
}
