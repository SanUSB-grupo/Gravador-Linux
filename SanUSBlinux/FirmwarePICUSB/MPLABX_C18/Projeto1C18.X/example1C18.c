#include "SanUSB1.h"

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c
void interrupcao(){

                  }

long int i;

void delay (void)
{
 
  for (i = 0; i <10000; i++)
    ;
}

void main (void)
{
clock_int_4MHz();

  portaB_saida();

  while (1)
    {
if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação
      /* Zera a porta B */
      PORTB = 0;

      /* Delay para ver o Led */
      delay ();

      /* Liga os LEDs */
      PORTB = 0xff;

     /* Delay para ver o Led */
      delay ();
    }
}
