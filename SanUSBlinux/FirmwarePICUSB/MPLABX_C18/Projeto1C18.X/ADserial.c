////Resistor de 1K entre os pinos C1 (PWM) e A0(analógico) e um capacitor de 10uF
#include "SanUSB1.h"//  https://www.youtube.com/watch?v=lB21b3zA4Ac

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c
void interrupcao(){

                  }

unsigned long int resultado, Vresult; //16 bits
unsigned char i=0;
const char Tensao[] = "Tensao Result= ";
const char Rn[] = "\r\n";

void main(){
clock_int_4MHz(); //Função necessaria para o dual clock
taxa_serial(19200);
habilita_canal_AD(AN0);

while(1){
for(i = 0 ; i < 100 ; i=i+5) { SetaPWM1(10000, i);SetaPWM2(10000, i); //frequência em Hz

resultado = le_AD10bits(0);//Lê canal  0 da entrada analógica com  resolução de 10 bits (ADRES)

//printf("Valor= %u\r\n", resultado);

Vresult= (resultado * 5000)/1023;

sendsw((char *)Tensao);
sendnum(Vresult);
sendsw((char *)Rn);

inverte_saida(pin_b7);
tempo_ms(500);             }

for(i = 100 ; i > 0 ; i=i-5) { SetaPWM1(1200, i);SetaPWM2(1200, i);

resultado = le_AD10bits(0);//Lê canal  0 da entrada analógica com  resolução de 10 bits (ADRES)

sendsw((char *)Tensao);
sendnum(Vresult);
sendsw((char *)Rn);

inverte_saida(pin_b7);
tempo_ms(500);             }


   }
}
