#include "SanUSB.h"

void main()
{

while (1)
   {
    if (!input(pin_e3)){reset_cpu();} //se pressionar o bot�o no pino 1, reseta e entra em estado de grava��o
   output_toggle(pin_B7); // comuta Led na fun��o principal
   delay_ms(500);
   }
}
