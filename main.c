//============= MBCORP
//=== PICC simil Arduino
//=== Matias Leonardo Baez


#include <stdio.h>
#include <pic.h>
#include "delay.h"	//Retardos
#include "serial.h"	//Comunicacion Serial
#include "pap.h"	//Control PAP placa de entrenamiento
#include "hc595.h" //Control de buffers hc595
#include "srf04.h" //Deteccion con ultrasonico srf04
#include "funciones.h"	//Funciones como arduino

__CONFIG( XT & WDTDIS & UNPROTECT & PWRTEN );

unsigned int d;

//Configuracion de Puertos como entradas o salidas
void setup(void)
{
	papBegin();
	papStop();
}

//Bucle infinito
void loop(void)
{
	papMoveManual(PAP1_L);
	delay(200);
}



////===============NO TOCAR lo que sigue!!!!!!!!!

void main(void){
	
	TRISA = 0b00000000;
	TRISB = 0b00000000;

	setup();

	PORTA = 0b00000000;
	PORTB = 0b00000000;

//	INTCON=0;	// purpose of disabling the interrupts.

	while(1){
		loop();
	}
}
