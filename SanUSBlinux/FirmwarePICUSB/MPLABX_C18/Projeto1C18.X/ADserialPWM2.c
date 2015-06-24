/*******************************************************************************
Software: Firmware abaixo compilado com o MPLABX + C18 multiplataforma (https://dl.dropboxusercontent.com/u/101922388/BaixarMPLABX_C18.pdf)
Hardware: Placa SanUSB com um resistor de 1K ligado entre os pinos
O firmware gera o pwm C2(PWM1) em função da variacao do AD A0(AN0) com potenciometro
Mais detalhes em: https://www.youtube.com/watch?v=KbH3yzPHX4UU e http://www.youtube.com/watch?v=lB21b3zA4Ac
******************************************************************************/
#include "SanUSB1.h" //

#pragma interrupt interrupcao
void interrupcao(){}

long int var_p;
long int var_ad;

void main(){
    clock_int_4MHz();
    taxa_serial(19200);

    while(1){
        inverte_saida(pin_b7);
        tempo_ms(500);

        var_ad = le_AD10bits( 0 );//Lê canal  0 da entrada analógica com  resolução de 10 bits (ADRES)

        if( var_ad <= 100 ) var_ad = 0;//filtro para valor de inicio
        var_p = ( 100 * var_ad ) / 1023; //calcula var_p de pwm em função da variacao do AD com potenciometro

        SetaPWM1(10000, var_p); //Led e ponteiras do osciloscopio ligados ao pino de PWM1 e ao Gnd
        SetaPWM2(10000, var_p);
    }
}