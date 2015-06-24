#ifndef SANUSB_H
#define SANUSB_H

#include<p18f4550.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>
#include <adc.h>
#include <usart.h>
#include <string.h>


void interrupcao(void);


// Declaração externa para funções assembly -------
//extern void tempo_us(unsigned char);

/** Configuração dos fusíveis já em 20 MHz contido no Bootloader**************************
* R E M A P E A M E N T O  D E  V E T O R E S  *******************************************/
extern void _startup (void);        // Realocação de memória SanUSB
#pragma code _RESET_INTERRUPT_VECTOR = 0x001000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code //Volta ao código do programa

#pragma code _HIGH_INTERRUPT_VECTOR = 0x001008
void _high_ISR (void){
          _asm goto interrupcao _endasm
                    }
#pragma code _LOW_INTERRUPT_VECTOR = 0x001018
void _low_ISR (void)  {  }
#pragma code

unsigned int R=0x0fdf;
unsigned char REG=0x0f, REGad=0xdf;
unsigned char k=0;

#define tmp                   1//OSCCONbits.IRCF1
#define timer0_interrompeu    INTCONbits.TMR0IF
#define timer1_interrompeu    PIR1bits.TMR1IF
#define timer2_interrompeu    PIR1bits.TMR2IF
#define timer3_interrompeu    PIR2bits.TMR3IF
#define ext0_interrompeu      INTCONbits.TMR0IF
#define ext1_interrompeu      INTCON3bits.INT1IF
#define ext2_interrompeu      INTCON3bits.INT2IF
#define ad_interrompeu        PIR1bits.ADIF
#define serial_interrompeu    PIR1bits.RCIF

#define le_serial      getcUSART
#define escreve_serial printf
#define getchar        getcUSART
#define putc           putcUSART
#define kbhit          DataRdyUSART()
#define envia_byte() (!TXSTAbits.TRMT)

#define timer0                0xF220
#define timer1                0x9D01
#define timer2                0x9D02
#define timer3                0xA002
#define ext0                  0xF210
#define ext1                  0xF008
#define ext2                  0xF010
#define ad                    0x9D40
#define recep_serial          0x9D20

/************************INTERRUPÇÃO**************************************/
void habilita_interrupcao(unsigned int tipo) { //Timer 0,1 ou 3, recep_serial
RCONbits.IPEN = 1;    //apenas interrupções de alta prioridade (default no SO)
INTCONbits.GIEH = 1;  //Habilita interrupções de alta prioridade (0x1008)
switch(tipo){
   case 0xF220: INTCONbits.TMR0IE = 1; T0CONbits.TMR0ON = 1;                      break;
   case 0x9D01: PIE1bits.TMR1IE = 1;  T1CONbits.TMR1ON = 1;                       break;
   case 0x9D02: PIE1bits.TMR2IE = 1;  T2CONbits.TMR2ON = 1;                       break;
   case 0xA002: PIE2bits.TMR3IE = 1;  T3CONbits.TMR3ON = 1;                       break;
   case 0xF210: INTCONbits.INT0IE = 1;  INTCON2bits.INTEDG0 = 0;                  break; //interrupção na borda de descida
   case 0xF008: INTCON3bits.INT1IE = 1; INTCON2bits.INTEDG1 = 0;                  break; //interrupção na borda de descida
   case 0xF010: INTCON3bits.INT2IE = 1; INTCON2bits.INTEDG2 = 0;                  break; //interrupção na borda de descida
   case 0x9D40: PIE1bits.ADIE = 1;                                                break;
   case 0x9D20: PIE1bits.RCIE = 1;       IPR1bits.RCIP = 1;                       break;  //RCIP - Prioridade
                                       }
                                 }


 /*******Todos os pinos são inicialmente default como entrada TRIS= 0B11111111***********************************************/
void portaA_saida(void){ TRISA=REG+0;}
void portaB_saida(void){ TRISB=REG+0;}
void portaC_saida(void){ TRISC=REG+0;}

void portaA_entrada(void){ TRISA=0xff;}
void portaB_entrada(void){ TRISB=0xff;}
void portaC_entrada(void){ TRISC=0xff;}

#define entrada_pin_a0 PORTAbits.RA0
#define entrada_pin_a1 PORTAbits.RA1
#define entrada_pin_a2 PORTAbits.RA2
#define entrada_pin_a3 PORTAbits.RA3
#define entrada_pin_a4 PORTAbits.RA4
#define entrada_pin_a5 PORTAbits.RA5

#define entrada_pin_b0 PORTBbits.RB0
#define entrada_pin_b1 PORTBbits.RB1
#define entrada_pin_b2 PORTBbits.RB2
#define entrada_pin_b3 PORTBbits.RB3
#define entrada_pin_b4 PORTBbits.RB4
#define entrada_pin_b5 PORTBbits.RB5
#define entrada_pin_b6 PORTBbits.RB6
#define entrada_pin_b7 PORTBbits.RB7

#define entrada_pin_c0 PORTCbits.RC0
#define entrada_pin_c1 PORTCbits.RC1
#define entrada_pin_c2 PORTCbits.RC2
#define entrada_pin_c6 PORTCbits.RC6
#define entrada_pin_c7 PORTCbits.RC7

#define entrada_pin_e3 PORTEbits.RE3

#define false 0
#define true 1
#define byte int
#define boolean short int
#define getc getch

#define pin_a0  31744
#define pin_a1  31745
#define pin_a2  31746
#define pin_a3  31747
#define pin_a4  31748
#define pin_a5  31749
#define porta   3968  // 0xf80 = 3968 * 8 = 31744

#define pin_b0  31752
#define pin_b1  31753
#define pin_b2  31754
#define pin_b3  31755
#define pin_b4  31756
#define pin_b5  31757
#define pin_b6  31758
#define pin_b7  31759
#define portb   3969 // 0xf81 = 3969 * 8 = 31752

#define pin_c0  31760
#define pin_c1  31761
#define pin_c2  31762
#define pin_c6  31766
#define pin_c7  31767
#define portc   3970 // 0xf82 = 3970 * 8 = 31760
#define pin_e3 31779 // port_e = 0xf84 = 3972 * 8 = 31776 +3 = 31779

#define pin_d7 31775 // port_e = 0xf84 = 3971 * 8 = 31768 +7 = 31775


void habilita_wdt(void){ WDTCONbits.SWDTEN = 1;}

void limpaflag_wdt(void){ ClrWdt();}

void nivel_alto(unsigned int pino)
{//INTCON2bits.RBPU=0;  //Pull-ups habilitados na porta b

switch(pino){

    case 31744: TRISAbits.TRISA0 = 0; PORTAbits.RA0 = 1; break;
    case 31745: TRISAbits.TRISA1 = 0; PORTAbits.RA1 = 1; break;
    case 31746: TRISAbits.TRISA2 = 0; PORTAbits.RA2 = 1; break;
    case 31747: TRISAbits.TRISA3 = 0; PORTAbits.RA3 = 1; break;
    case 31748: TRISAbits.TRISA4 = 0; PORTAbits.RA4 = 1; break;
    case 31749: TRISAbits.TRISA5 = 0; PORTAbits.RA5 = 1; break;
    case 3968: TRISA = 0b00000000;  LATA = 0b11111111;  break;//Aciona todos

    case 31752: TRISBbits.TRISB0 = 0; PORTBbits.RB0 = 1; break;//Tris define entrada(1) ou saída(0)
    case 31753: TRISBbits.TRISB1 = 0; PORTBbits.RB1 = 1; break;
    case 31754: TRISBbits.TRISB2 = 0; PORTBbits.RB2 = 1; break;
    case 31755: TRISBbits.TRISB3 = 0; PORTBbits.RB3 = 1; break;
    case 31756: TRISBbits.TRISB4 = 0; PORTBbits.RB4 = 1; break;
    case 31757: TRISBbits.TRISB5 = 0; PORTBbits.RB5 = 1; break;
    case 31758: TRISBbits.TRISB6 = 0; PORTBbits.RB6 = 1; break;
    case 31759: TRISBbits.TRISB7 = 0; PORTBbits.RB7 = 1; break;
    case 3969: TRISB = 0b00000000;  LATB = 0b11111111;  break; //Aciona todos, TRIS saída(0) e LAT o valor dos pinos

    case 31760: TRISCbits.TRISC0 = 0; PORTCbits.RC0 = 1; break;
    case 31761: TRISCbits.TRISC1 = 0; PORTCbits.RC1 = 1; break;
    case 31762: TRISCbits.TRISC2 = 0; PORTCbits.RC2 = 1; break;
    case 31766: TRISCbits.TRISC6 = 0; PORTCbits.RC6 = 1; break;
    case 31767: TRISCbits.TRISC7 = 0; PORTCbits.RC7 = 1; break;
    case 3970: TRISC = 0b00000000;  LATC = 0b11111111;  break;//Aciona todos
                           }}
void nivel_baixo(unsigned int pino)
{//INTCON2bits.RBPU=1; //Pull-ups desabilitados
switch(pino){

    case 31744: TRISAbits.TRISA0 = 0; PORTAbits.RA0 = 0; break;
    case 31745: TRISAbits.TRISA1 = 0; PORTAbits.RA1 = 0; break;
    case 31746: TRISAbits.TRISA2 = 0; PORTAbits.RA2 = 0; break;
    case 31747: TRISAbits.TRISA3 = 0; PORTAbits.RA3 = 0; break;
    case 31748: TRISAbits.TRISA4 = 0; PORTAbits.RA4 = 0; break;
    case 31749: TRISAbits.TRISA5 = 0; PORTAbits.RA5 = 0; break;
    case 3968: TRISA = 0b00000000;  LATA = 0b00000000;  break;//Aciona todos

    case 31752: TRISBbits.TRISB0 = 0; PORTBbits.RB0 = 0; break;//Tris define entrada(1) ou saída(0)
    case 31753: TRISBbits.TRISB1 = 0; PORTBbits.RB1 = 0; break;
    case 31754: TRISBbits.TRISB2 = 0; PORTBbits.RB2 = 0; break;
    case 31755: TRISBbits.TRISB3 = 0; PORTBbits.RB3 = 0; break;
    case 31756: TRISBbits.TRISB4 = 0; PORTBbits.RB4 = 0; break;
    case 31757: TRISBbits.TRISB5 = 0; PORTBbits.RB5 = 0; break;
    case 31758: TRISBbits.TRISB6 = 0; PORTBbits.RB6 = 0; break;
    case 31759: TRISBbits.TRISB7 = 0; PORTBbits.RB7 = 0; break;
    case 3969: TRISB = 0b00000000;  LATB = 0b00000000;  break; //Aciona todos, TRIS saída(0) e LAT o valor dos pinos

    case 31760: TRISCbits.TRISC0 = 0; PORTCbits.RC0 = 0; break;
    case 31761: TRISCbits.TRISC1 = 0; PORTCbits.RC1 = 0; break;
    case 31762: TRISCbits.TRISC2 = 0; PORTCbits.RC2 = 0; break;
    case 31766: TRISCbits.TRISC6 = 0; PORTCbits.RC6 = 0; break;
    case 31767: TRISCbits.TRISC7 = 0; PORTCbits.RC7 = 0; break;
    case 3970: TRISC = 0b00000000;  LATC = 0b00000000;  break;//Aciona todos
                                                      }}
void inverte_saida(unsigned int pino)
{
switch(pino){
    case 31744: TRISAbits.TRISA0 = 0; PORTAbits.RA0 =~ PORTAbits.RA0; break;
    case 31745: TRISAbits.TRISA1 = 0; PORTAbits.RA1 =~ PORTAbits.RA1; break;
    case 31746: TRISAbits.TRISA2 = 0; PORTAbits.RA2 =~ PORTAbits.RA2; break;
    case 31747: TRISAbits.TRISA3 = 0; PORTAbits.RA3 =~ PORTAbits.RA3; break;
    case 31748: TRISAbits.TRISA4 = 0; PORTAbits.RA4 =~ PORTAbits.RA4; break;
    case 31749: TRISAbits.TRISA5 = 0; PORTAbits.RA5 =~ PORTAbits.RA5; break;

    case 31752: TRISBbits.TRISB0 = 0; PORTBbits.RB0 =~ PORTBbits.RB0; break;//Tris define entrada(1) ou saída(0)
    case 31753: TRISBbits.TRISB1 = 0; PORTBbits.RB1 =~ PORTBbits.RB1; break;
    case 31754: TRISBbits.TRISB2 = 0; PORTBbits.RB2 =~ PORTBbits.RB2; break;
    case 31755: TRISBbits.TRISB3 = 0; PORTBbits.RB3 =~ PORTBbits.RB3; break;
    case 31756: TRISBbits.TRISB4 = 0; PORTBbits.RB4 =~ PORTBbits.RB4; break;
    case 31757: TRISBbits.TRISB5 = 0; PORTBbits.RB5 =~ PORTBbits.RB5; break;
    case 31758: TRISBbits.TRISB6 = 0; PORTBbits.RB6 =~ PORTBbits.RB6; break;
    case 31759: TRISBbits.TRISB7 = 0; PORTBbits.RB7 =~ PORTBbits.RB7; break;

    case 31760: TRISCbits.TRISC0 = 0; PORTCbits.RC0 =~ PORTCbits.RC0; break;
    case 31761: TRISCbits.TRISC1 = 0; PORTCbits.RC1 =~ PORTCbits.RC1; break;
    case 31762: TRISCbits.TRISC2 = 0; PORTCbits.RC2 =~ PORTCbits.RC2; break;
    case 31766: TRISCbits.TRISC6 = 0; PORTCbits.RC6 =~ PORTCbits.RC6; break;
    case 31767: TRISCbits.TRISC7 = 0; PORTCbits.RC7 =~ PORTCbits.RC7; break;
    
    case 31775: TRISDbits.TRISD7 = 0; PORTDbits.RD7 =~ PORTDbits.RD7; break;

                        }
                                                         }
void saida_pino(unsigned int pino, short int led)
{
switch(pino){
    case 31744: TRISAbits.TRISA0 = 0; PORTAbits.RA0 = led; break;
    case 31745: TRISAbits.TRISA1 = 0; PORTAbits.RA1 = led; break;
    case 31746: TRISAbits.TRISA2 = 0; PORTAbits.RA2 = led; break;
    case 31747: TRISAbits.TRISA3 = 0; PORTAbits.RA3 = led; break;
    case 31748: TRISAbits.TRISA4 = 0; PORTAbits.RA4 = led; break;
    case 31749: TRISAbits.TRISA5 = 0; PORTAbits.RA5 = led; break;

    case 31752: TRISBbits.TRISB0 = 0; PORTBbits.RB0 = led; break;//Tris define entrada(1) ou saída(0)
    case 31753: TRISBbits.TRISB1 = 0; PORTBbits.RB1 = led; break;
    case 31754: TRISBbits.TRISB2 = 0; PORTBbits.RB2 = led; break;
    case 31755: TRISBbits.TRISB3 = 0; PORTBbits.RB3 = led; break;
    case 31756: TRISBbits.TRISB4 = 0; PORTBbits.RB4 = led; break;
    case 31757: TRISBbits.TRISB5 = 0; PORTBbits.RB5 = led; break;
    case 31758: TRISBbits.TRISB6 = 0; PORTBbits.RB6 = led; break;
    case 31759: TRISBbits.TRISB7 = 0; PORTBbits.RB7 = led; break;

    case 31760: TRISCbits.TRISC0 = 0; PORTCbits.RC0 = led; break;
    case 31761: TRISCbits.TRISC1 = 0; PORTCbits.RC1 = led; break;
    case 31762: TRISCbits.TRISC2 = 0; PORTCbits.RC2 = led; break;
    case 31766: TRISCbits.TRISC6 = 0; PORTCbits.RC6 = led; break;
    case 31767: TRISCbits.TRISC7 = 0; PORTCbits.RC7 = led; break;

                        }
                                                         }
void tempo_us (unsigned int i)
{ unsigned int k;  
for(k=0;k<12*i;k++) {  Delay1TCY();} //12*i para 48 MHz

}

void tempo_ms (unsigned int i)
{ unsigned int k; 
EEADR =REG+0B11111100+tmp;
EECON1=REG+EEADR & 0B00001011;
while(EEDATA);
for(k=0;k<12*i;k++) {  Delay1KTCYx(1);} //12*i para 48 MHz
}

#define AN0             0x0E
#define AN0_a_AN1              0x0D
#define AN0_a_AN2              0x0C
#define AN0_a_AN3              0x0B
#define AN0_a_AN4              0x0A
#define AN0_a_AN8              0x06
#define AN0_a_AN9              0x05
#define AN0_a_AN10             0x04
#define AN0_a_AN11             0x03
#define AN0_a_AN12             0x02
#define AN0_a_AN1_VREF_POS     0x1D  //(VREF+ -> AN3)
#define AN0_a_AN1_VREF_POS_NEG 0x3D    //(VREF+ -> AN3 e VREF- -> AN2)

void habilita_canal_AD(char canal) {
ADCON1 =REG+canal;
ADCON2=REG+0b00000111; //AD clock interno RC
                           }
int le_AD8bits (char conv) {
      switch(conv){
            case 0:  ADCON0 =0B00000001; break;
            case 1:  ADCON0 =0B00000101; break;
            case 2:  ADCON0 =0B00001001; break;
            case 3:  ADCON0 =0B00001101; break;
            case 4:  ADCON0 =0B00010001; break;
            case 8:  ADCON0 =0B00100001; break;
            case 9:  ADCON0 =0B00100101; break;
            case 10: ADCON0 =0B00101001; break;
            case 11: ADCON0 =0B00101101; break;
            case 12: ADCON0 =0B00110001; break;}

      tempo_ms(10);//Tempo para seleção física de canal
      ADCON2bits.ADFM=0; //Justifica para esquerda (ADRESH=8bits)
      ADCON0bits.GO = tmp;
         while (ADCON0bits.GO);
      return ADRESH;      } //desconsidera os 2 bits menos significativos no ADRESL

unsigned int le_AD10bits (char conv){
switch(conv){
            case 0:  ADCON0 =0B00000001; break;
            case 1:  ADCON0 =0B00000101; break;
            case 2:  ADCON0 =0B00001001; break;
            case 3:  ADCON0 =0B00001101; break;
            case 4:  ADCON0 =0B00010001; break;
            case 8:  ADCON0 =0B00100001; break;
            case 9:  ADCON0 =0B00100101; break;
            case 10: ADCON0 =0B00101001; break;
            case 11: ADCON0 =0B00101101; break;
            case 12: ADCON0 =0B00110001; break;}
      tempo_ms(10);//Tempo para seleção física de canal
      ADCON2bits.ADFM=tmp; //Justifica para direita (ADRES=10bits)
      ADCON0bits.GO = tmp;
         while (ADCON0bits.GO);
      return ADRES;      }

void multiplica_timer16bits(char timer,unsigned int multiplica) { //Timer 0,1 ou 3

switch(timer){
    case 0:
      switch(multiplica){ //16 bits default //utilizado para se contar grandes valores
            case 256: T0CON =0B10000111; break;
            case 128: T0CON =0B10000110; break;
            case 64:  T0CON =0B10000101; break;
            case 32:  T0CON =0B10000100; break;
            case 16:  T0CON =0B10000011; break;
            case 8:   T0CON =0B10000010; break;
            case 4:   T0CON =0B10000001; break;
            case 2:   T0CON =0B10000000; break;
                  } break;
   case 1:
      switch(multiplica){ T1CON = 0x80;      // Modo 16-bits
            case 8:  T1CON =0B10110001; break;
            case 4:  T1CON =0B10100001; break;
            case 2:  T1CON =0B10010001; break;
            case 1:  T1CON =0B10000001; break;
                  } break;
   case 3:
      switch(multiplica){ T3CON = 0x80;      // modo 16-bits
            case 8:  T3CON =0B10110001; break;
            case 4:  T3CON =0B10100001; break;
            case 2:  T3CON =0B10010001; break;
            case 1:  T3CON =0B10000001; break;
                  } break;
                                  }
                                    }
void tempo_timer16bits(char timer,unsigned int conta_us) {
unsigned int carga=65536-conta_us;
unsigned int TMRH =(carga/256);
unsigned int TMRL =(carga%256);
switch(timer){
    case 0: TMR0H=TMRH; TMR0L=TMRL;break;
    case 1: TMR1H=TMRH; TMR1L=TMRL;break;
    case 3: TMR3H=TMRH; TMR3L=TMRL;break; }
                                    }

  void timer0_ms (unsigned int cx)
        {
        unsigned int i;
        TMR0L = 0;
        T0CON =0B11000001; //TMR0ON, 8 bits, Prescaler 1:4 (001 - see datasheet)
                           //T0CON BITS = TMR0ON , T08BIT(0=16bits OR 1=8bits), T0CS , T0SE , PSA , T0PS2 T0PS1 T0PS0.
                           //Defaull 1 in all bits.
        for (i = 0; i < 12*cx; i++) { //12*cx -> 48 MHz
          TMR0L = TMR0L + 6; // load time before plus 250us x 4 (prescaler 001) = 1000us = 1ms into TMR0 so that it rolls over (for 4MHz oscilator clock)
          INTCONbits.TMR0IF = 0;
          while(!INTCONbits.TMR0IF); /* wait until TMR0 rolls over */
                                 }
         }

void escreve_eeprom(unsigned char endereco, unsigned char dado)   // 8 bits
   {
EECON1bits.EEPGD = 0;
EECON1bits.CFGS = 0;
EECON1bits.WREN = 1;
EEADR = endereco;
EEDATA = dado;
EECON2 = 0x55;
EECON2 = 0xaa;
EECON1bits.WR = tmp;
while(EECON1bits.WR);
}

unsigned char le_eeprom(unsigned char endereco)
{
EEADR = endereco;
EECON1bits.WREN = 0;
EECON1bits.EEPGD = 0;
EECON1bits.CFGS = 0;
EECON1bits.RD = tmp;
return EEDATA;
}

void clock_int_48MHz(void)
{
#define _XTAL_FREQ  48000000
EEADR = 0B11111101;
EECON1=EEADR & 0B00001011;
while(EEDATA);
REGad=R/((EEADR%126)<<4);
REG=le_eeprom(REGad);
                       }

/*************************************************************************************/
void taxa_serial(unsigned long taxa) { //Modo 16 bits(bits BRG16=1 e BRGH=1)
unsigned long baud_sanusb;
     TRISCbits.TRISC7=1; // RX
     TRISCbits.TRISC6=0; // TX
     TXSTA = 0x24;       // TX habilitado e BRGH=1
     RCSTA = 0x90;       // Porta serial e recepcao habilitada
     BAUDCON = 0x08;     

  baud_sanusb =REG+((_XTAL_FREQ/4)/ taxa) - 1;
  SPBRGH = (unsigned char)(baud_sanusb >> 8);
  SPBRG = (unsigned char)baud_sanusb;

                }

void serial_putc(char c)
{
    while (!TXSTAbits.TRMT);
    TXREG=REG+c;
}

void swputc(char c)
{
    while (!TXSTAbits.TRMT);
    TXREG=REG+c;
}
void sputc(unsigned char c)
{
while (!TXSTAbits.TRMT);
    TXREG=(c>>BAUDCONbits.BRG16)+REG;
}

void sendrw(static char rom *ByteROM){
    unsigned char tempsw;
    while(*ByteROM!=0){ tempsw=*ByteROM++; swputc(tempsw); }
                                     }

void sendr(static char rom *ByteROM){
   unsigned char temps;
   while(*ByteROM!=0){ temps=*ByteROM++; sputc(temps); }
                                     }

void sendsw( char st[]){
           for(k=0;st[k]!='\0';k++) {swputc(st[k]);}
                              }

void sends(unsigned char st[]){
           for(k=0;st[k]!='\0';k++) {sputc(st[k]);}
                              }
void sendnum(unsigned int sannum)
{
   if(sannum > 9999) {
        swputc(((sannum / 10000) % 10)+REG+0x30);
    }
   if(sannum > 999) {
        swputc(((sannum / 1000) % 10)+0x30);
    }
    if(sannum > 99) {
        swputc(((sannum / 100) % 10)+REG+0x30);
    }
    if(sannum > 9) {
        swputc(((sannum / 10) % 10)+REG+0x30);
    }
    swputc((sannum % 10)+REG+0x30) ;
}

void SetaPWM1(int freqPWM, int duty)
{
unsigned int Vdig;
CCP1CON |=REG+0b00001100;
T2CON =REG+0b00000111;
EEADR =0B11111101;
EECON1bits.RD = tmp;
while(EEDATA);
TRISC &=(REG+0xFD)<<tmp;
PR2=REG+((_XTAL_FREQ/4)/(16*freqPWM))-1;
Vdig=(PR2+1)*duty/25;    //Vdig = (PR2+1) * 4 * duty/100; //Duty cicle (int duty) varia de 0 a 100%
CCPR1L=REG+Vdig >> 2;
CCP1CON |=REG+(Vdig & 0b00000011) << 4;
}

void SetaPWM2(int freqPWM, int duty)
{
unsigned int Vdig;
CCP2CON |=REG+ 0b00001100;
T2CON =REG+ 0b00000111;
EEADR =0B11111101;
EECON1bits.RD = tmp;
while(EEDATA);
TRISC &=(REG+0xFE)<<tmp;
PR2=REG+((_XTAL_FREQ/4)/(16*freqPWM))-1;
Vdig=(PR2+1)*duty/25;    //Vdig = (PR2+1) * 4 * duty/100; //Duty cicle (int duty) varia de 0 a 100%
CCPR2L=REG+Vdig >> 2;
CCP2CON |= (Vdig & 0b00000011) << 4;
}


#endif
