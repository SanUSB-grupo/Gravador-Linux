/**********************************************************************************
 Android Bluetooth Car: http://www.youtube.com/watch?v=Fx8RqRlm-bs
 PINOS B6 E B5 - RODA ESQUERDA / B4 E B3 - RODA DIREITA
O aplicativo Robo_Bluetooth vai enviar apenas um caractere que representará 
a tecla pressionada, onde:
0 = nenhuma tecla pressionada;
1 = tecla UP pressionada;
2 = tecla DOWN pressionada;
3 = tecla LEFT pressionada;
4 = tecla RIGHT pressionada;
5 = tecla frente carro pressionada;
6 = tecla trazeira carro pressionada;
A = tecla buzina pressionada;
**********************************************************************************/

#include "SanUSB.h"//Programa para testar o modem bluetooth
//Verificar o baud rate do modem, se 9600 ou 19200bps e configurar abaixo
#use rs232(baud=19200, xmit=pin_c6, rcv=pin_c7)

short int pisca=0;
char comando;
//para iluminação
int cont=0;
int cont1=0;

#INT_RDA
void recepcao_serial()// Interrupcao serial
{
comando=getc();

//FRENTE
if (comando=='1') //teste da comunicacao serial no Terminal
{
//roda esquerda
output_high(pin_b5);
output_low(pin_b6);
//roda direita
output_low(pin_b3);
output_high(pin_b4);
}

//RÉ
if (comando=='2') //teste da comunicacao serial no Terminal
{
//roda esquerda
output_low(pin_b5);
output_high(pin_b6);
//roda direita
output_high(pin_b3);
output_low(pin_b4);
}

//DIREITA
if (comando=='4') //teste da comunicacao serial no Terminal
{
//roda esquerda
output_high(pin_b5);
output_low(pin_b6);
//roda direita
output_high(pin_b3);
output_low(pin_b4);
}

//ESQUERDA
if (comando=='3') //teste da comunicacao serial no Terminal
{
//roda esquerda
output_low(pin_b5);
output_high(pin_b6);
//roda direita
output_low(pin_b3);
output_high(pin_b4);
}

if (comando=='0') //teste da comunicacao serial no Terminal
{
//para roda esquerda
output_low(pin_b6);
output_low(pin_b5);
//para roda direita
output_low(pin_b3);
output_low(pin_b4);
} 

///*******controle iluminação e buzina**************************////////////
// pode ser feita o ligar e desligar da lampada com a variavel toggle
//output_toggle(pin_B7);
//lampada Farol
if (comando=='5') //botao carro frente
{
cont++;
if (cont==1)
{
output_high(pin_a5);
output_high(pin_a4);
}
else
{
cont=0;
output_low(pin_a5);
output_low(pin_a4);
}
}

//lampada traseira
if (comando=='6')// botao carro traz
{
cont1++;
if (cont1==1)
output_high(pin_a3);

else
{
cont1=0;
output_low(pin_a3);
}
}

//Buzina
if (comando=='A')// botão buzina
output_high(pin_a2);

else
output_low(pin_a2);
}

void main()
{
enable_interrupts(GLOBAL); // Possibilita todas interrupcoes
enable_interrupts(INT_RDA); // Interrupcao da serial

output_toggle(pin_B7);// pisca Led
delay_ms (500);

while(1)
{
   if (!input(pin_e3))
   {
      reset_cpu();
   } //se pressionar o botão no pino 1 sem retirar o cabo, reseta e entra em estado de gravação
   
while (pisca==1)
{
output_toggle(pin_B7);
delay_ms(300);
}//pisca rápido
}
}
