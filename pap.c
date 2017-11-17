//============= MBCORP
//=== Funciones para control de 1 motor pap
//=== con la placa de entrenamiento Driver L293D
//=== Matias Leonardo Baez

#include <pic.h>
#include "funciones.h"
#include "pap.h"

unsigned char ld;
unsigned char pAnterior; // secuencia en la que se encuentra
unsigned char mxCiclo;

//para no usar un vector de secuncia se creo esta funcion
unsigned char convPasoSecuencia(unsigned char a)
{
	unsigned char sec;

	switch(a)
	{				//secuencia en binario
		case 1: sec = 0b00000011 << 4; break;	//0b00010000
		case 2: sec = 0b00000110<<4; break;	//0b00100000
		case 3: sec = 0b00001100<<4; break;	//0b01000000
		case 4: sec = 0b00001001<<4; break;	//0b10000000
		
	}

	return	sec;
}

//inicia el control de un motor pap por el puertoB conectado a RB7-6-5-4
void papBegin(void)
{
	//si se va usar la placa de entrenamiento
	#ifdef	DRIVER_1
		TRISB &= 0b00001111; //Salida Rb7-4
	#else//sino se usa la placa de doble driver
		TRISB = 0b00000000; //Todo el puerto B como salida
	#endif

	ld=0; //leds apagados
	pAnterior=0b00000000; //
	mxCiclo=0b00010001;
}

//si se usa la placa de entrenamiento esta funcion existe sino se autoborra
#ifdef DRIVER_1
//con esta funcion no perdemos el estado de los primeros 4 bits del puerto b
char buff_pap(void){
	unsigned char temp;

	temp = PORTB << 4; //desplazo 4 posiciones hacia adelante
	temp = temp >> 4; //desplazo 4 posiciones hacia atras 
	/* Con lo anterior borro el estado de los bits del motor */
	/* Sin perder el estado de los primeros 4 bits           */

	return temp;
}

#endif


//Devuelve el Paso actual dentro la secuencia
char getStepM1(void)
{
	unsigned char m2C;

	m2C = mxCiclo >> 4;

	return m2C;
}

#ifndef DRIVER_1
//Devuelve el Paso en el que esta el motor2
char getStepM2(void)
{
	unsigned char m1C;

	m1C = (mxCiclo << 4);
	m1C = m1C >> 4;
	
	return m1C;
}
#endif

//0b00001111
//      PDPD   Paso Direccion
//      M2M1   Motor2 Motor1
void papMove(unsigned char pActual)
{
	unsigned char m2Ciclo = getStepM1();
	#ifndef DRIVER_1
	unsigned char m1Ciclo = getStepM2();
	#endif
	

	//Motor1
	//si paso de estar en 0 a estar en 1
	if (!!bit_test(pActual,1)==1 && !!bit_test(pAnterior,1)==0)
	{
		if (!!bit_test(pActual,0)==1)
		{
			if (m2Ciclo==4)
				m2Ciclo=1;
			else
				m2Ciclo++;
		}
		else
		{
			if (m2Ciclo==1)
				m2Ciclo=4;
			else
				m2Ciclo--;
		}
	}

	#ifndef	DRIVER_1	//si no estamos usando la placa de entrenamiento entonces entra aqui
	//Motor2
	//si paso de estar en 0 a estar en 1
	if (!!bit_test(pActual,3)==1 && !!bit_test(pAnterior,3)==0)
	{
		if (!!bit_test(pActual,2)==1) //verifico la direccion
		{
			if (m1Ciclo==4)
				m1Ciclo=1;
			else
				m1Ciclo++;
		}
		else
		{
			if (m1Ciclo==1)
				m1Ciclo=4;
			else
				m1Ciclo--;
		}
	}
	#endif


	#ifdef	DRIVER_1	//si estamos usando la placa de entrenamiento
		PORTB = convPasoSecuencia(m2Ciclo) | buff_pap();//genero el Paso
		
		if (ld==1) //si se activo los leds
			PORTA = convPasoSecuencia(m2Ciclo) >> 4;

		mxCiclo = ( m2Ciclo << 4);
	#else	//si estamos usando la placa de doble driver
		PORTB = convPasoSecuencia(m2Ciclo) | (convPasoSecuencia(m1Ciclo)>>4); //envio al motor
		mxCiclo = m1Ciclo | ( m2Ciclo << 4);
	#endif

	pAnterior = pActual; //lo actual ahora es lo anterior

	
}



void papStop(void){
	PORTB = 0b00000000;//sM[4];
	pAnterior=0b00000000; //
	mxCiclo=0b00010001;
}

void papMoveManual(unsigned char a){
	papMove(a);
	papMove(0b00000000);
}

//hace que los leds se enciendan para testear la secuencia del pap
void papLedTest(void)
{
	ld = 1;
}
