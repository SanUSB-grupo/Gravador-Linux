///////////////////http://br.groups.yahoo.com/group/GrupoSanUSB/////////////////
#include <18F4550.h> //This library 18F4550.h is valid for the whole family USB PIC18Fx5xx

#device ADC=10
#fuses HSPLL,PLL5, USBDIV,CPUDIV1,VREGEN,NOWDT,NOPROTECT,NOLVP,NODEBUG
#byte OSCCON=0XFD3
#use delay(clock=48000000)// USB standard frequency (cpu and timers 12 MIPS = 4/48MHz)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)

//SanUSB program memory allocation
#define CODE_START 0x1000
#build(reset=CODE_START, interrupt=CODE_START+0x08)
#org 0, CODE_START-1 {}

void clock_int_4MHz(void)//Se for utilizado habilitar o #use delay(clock=4000000) e desabilitar //delay(clock=48000000)
{
 OSCCON=0B01100110; //with dual clock -> cpu and timers  #use delay(clock=4000000)
 //while(read_eeprom(0xfd));
//#use delay(clock=4000000) // internal Oscillator Clock of 4MHz
                           }
