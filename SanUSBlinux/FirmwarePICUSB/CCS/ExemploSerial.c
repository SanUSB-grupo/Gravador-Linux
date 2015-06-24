//**********************************************************************************
#include "SanUSB.h"//Programa para testar o modem bluetooth, gravado via USB,
//com com terminal serial no PC (Zuchi) ou android (BlueTerm)
//Verificar o baud rate do modem, se 9600 ou 19200bps e configurar abaixo
#use rs232(baud=19200, xmit=pin_c6, rcv=pin_c7)

short int pisca=0;
char comando;

#INT_RDA
void recepcao_serial()// Interrupcao serial
{
comando=getc();
switch (comando) //teste da comunicacao serial no Terminal
      {
   case 'L' : {pisca=0; output_high(pin_B7);printf (" Ligado\r\n");} //Recebe A e Transmite byte B para teste
   break;
   case 'D' : { pisca=0; output_low(pin_B7);printf (" Desligado\r\n");} //Recebe B e Transmite byte A para teste
   break;
   case 'P': { pisca=1;output_high(pin_B7);printf (" pisca-pisca\r\n");} //Recebe B e Transmite byte A para teste
   break;
      }
}

void main()
{
   enable_interrupts(GLOBAL); // Possibilita todas interrupcoes
   enable_interrupts(INT_RDA); // Interrupcao da serial

   output_toggle(pin_B7);// pisca Led
   delay_ms (500);

   while(1)
   {
   if (!input(pin_e3)){reset_cpu();} //se pressionar o botão no pino 1, reseta e entra em estado de gravação

   while (pisca==1){
   output_toggle(pin_B7);delay_ms (300); }//pisca rápido

     output_toggle(pin_B7);delay_ms (2000);
     printf("sanusb\r\n"); //envia de forma sem fio a palavra para o PC ou Android
     //printf ("AT+BAUD5");// não pode ter 0x1A

   }}
