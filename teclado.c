	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#include "m5272.h"
	#include "puerto.h"
	#include "teclado.h"
	#include "pongLib.h"
	//------------------------------------------------------
	// char teclado(void)
	//
	// Descripción:
	//   Explora el teclado matricial y devuelve la tecla 
	//   pulsada
	//
	//------------------------------------------------------
	char teclado(void)
	{
		char NUM_COLS = 4; // Número de columnas en el teclado matricial
		char EXCIT  = 1; // Excitación de salida bit 0
		BYTE fila, columna;
		static UBYTE fila_mask;
		static char teclas[4][4] = 
		   {{"123C"},
			{"456D"},
			{"789E"},
			{"A0BF"}};
		// Bucle de exploración del teclado
		while(estado){

			// Excitamos una columna
			for(columna = NUM_COLS - 1; columna >= 0; columna--){
				set_puertoS_teclado(EXCIT << columna);		// Se envía la excitación de columna
				retardo(1050);				// Esperamos respuesta de optoacopladores
				// Exploramos las filas en busca de respuesta
				for(fila = NUM_COLS - 1; fila >= 0; fila--){
					fila_mask = EXCIT << fila;		// Máscara para leer el bit de la fila actual
					if(lee_puertoE() & fila_mask){		// Si encuentra tecla pulsada,
						while(lee_puertoE() & fila_mask){}	//   Esperamos a que se suelte
						retardo(1050);	
						return teclas[fila][columna];		//   Devolvemos la tecla pulsada
					}
				}
				// Siguiente columna
			}
			// Exploración finalizada sin encontrar una tecla pulsada
		}
		return 'W'; //Si no necesitamos seguir explorando el teclado, devolvemos cualquier valor
		// Reiniciamos exploración
	}
