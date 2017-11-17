//============= MBCORP
//=== Funciones para Leer el ultrasonico srf04 
//=== con la placa de entrenamiento 
//=== Matias Leonardo Baez


/*
//ejemplo: srf04 con leds
unsigned int d;

//Configuracion de Puertos como entradas o salidas
void setup(void)
{
	srf04Begin();
}

//Bucle infinito
void loop(void)
{
	d = srf04GetDistance();

	if(d<=10)
	{
		RA0=1;
		RA1=0;
		RA2=0;
	}
	else
	{
		if(d<=30)
		{
			RA1=1;
			RA0=0;
			RA2=0;
		}
		else
		{
			RA2=1;
			RA1=0;
			RA0=0;
		}
	}
}

*/

/* 
//ejemplo 2:Comunicacion serial srf04
unsigned int d;
//Configuracion de Puertos como entradas o salidas
void setup(void)
{
	serial_begin();
	putch('*'); //Envio un caracter por serial
	srf04Begin();
}

//Bucle infinito
void loop(void)
{
	d = srf04GetDistance();
	printf("[%d]\r\n",d);
	
}
*/

#ifndef	_SRF04_H
#define	_SRF04_H

//Inicializa el sensor srf04
extern void srf04Begin(void);
//Retorna la distancia leida por el srf04
extern unsigned int srf04GetDistance(void);

#endif
