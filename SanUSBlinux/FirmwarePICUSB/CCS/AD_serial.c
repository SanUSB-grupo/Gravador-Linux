#include "SanUSB.h"
#use rs232(baud=19200, xmit=pin_c6, rcv=pin_c7)

int32 temperatura;

void main() {

setup_adc_ports(AN0);  //Habilita entradas analógicas - A0
setup_adc(ADC_CLOCK_INTERNAL);

while(1){
   if (!input(pin_e3)){reset_cpu();} //se pressionar o botão no pino 1, reseta e entra em estado de gravação
   set_adc_channel(0);
   delay_ms(10);
   temperatura=430*read_adc()/1023; //Vref = 4,3V devido à queda no diodo, então (430*temp)
   printf ("\r\nTemperatura do LM35 = %lu C\r\n",temperatura);

   output_high(pin_b7);
   delay_ms(500);
   output_low(pin_b7);
   delay_ms(500);               }}



