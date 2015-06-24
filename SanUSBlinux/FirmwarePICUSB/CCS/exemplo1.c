#include "SanUSB.h"

void main()
{

while (1)
   {
    if (!input(pin_e3)){reset_cpu();} //se pressionar o botão no pino 1, reseta e entra em estado de gravação
   output_toggle(pin_B7); // comuta Led na função principal
   delay_ms(500);
   }
}
