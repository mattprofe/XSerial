//============= MBCORP
//=== Funciones para control de 1 motor pap
//=== con la placa de entrenamiento Driver L293D
//=== Matias Leonardo Baez
// Dependiendo de la placa se debe activar en funciones.h!!
//<<< #define DRIVER_1	//placa entrenamiento
//<<< #define DRIVER_2	//placa doble driver

/* //Ejemplo
#define PXR	200 //pasos por vuelta 360°
#define IZQ 0	//Izquierda
#define DER 1	//Derecha

unsigned char pasos;
unsigned char sentido;

//Configuracion de Puertos como entradas o salidas
void setup(void)
{
	papBegin(); //iniciamos el puerto del pap
	papLedTest(); //activas la depuracion con leds
	papStop(); //apago el motor

	pasos=0; //pasos a 0
	sentido=IZQ; // sentido de giro IZQUIERDO
}

//Bucle infinito
void loop(void)
{
	if (pasos==PXR){ //Si el motor dio una vuelta completa 360°
		pasos=0; //reinicio
		sentido=!sentido; //cambio el sentido de giro
	}
	
	pasos++; //cuento 1 paso

	if (sentido==IZQ) // si el sentido es IZQUIERDO
		papMoveManual(PAP1_L | PAP2_R); // damos un paso a la izquierda
	else // sino el sentido es DERECHO
		papMoveManual(PAP1_R | PAP2_L); //damos un paso a la derecha

	delay(250); //Retardo de 250Ms entre cada paso
}
*/

#ifndef	_PAP_H
#define _PAP_H


//inicia el puerto b donde esta el driver l293d para usar un pap
extern void papBegin(void);
//devuelve el paso que esta ejecutando (0 al 3)
//extern char getStep(void);
//ejecuta paso en motor por protocolo 0b000000PD
extern void papMove(unsigned char pActual);
//detiene el motor o los motores
extern void papStop(void);
//para hacer el movimiento directamente desde el pic
extern void papMoveManual(unsigned char a);
//habilita los leds para ver la secuencia del pap
extern void papLedTest(void);

#endif
