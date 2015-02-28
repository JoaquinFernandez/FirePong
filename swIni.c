	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan Jos� Carracedo Justo
	*           Joaqu�n Fern�ndez Moreno
	*
	****************************************************************************/
	#include "swIni.h"
	#include "pongLib.h"
	#include "calculos.h"
	//------------------------------------------------------
	// void swIni(void)
	//
	// Descripci�n:
	//   Resetea el valor de todas las variables
	//   utilizadas durante el juego
	//
	//------------------------------------------------------
	void swIni(void) {
		estado = estadoMenu;
		puntuacion.puntosJugador1 = 0;
		puntuacion.puntosJugador2 = 0;
		rebote = 0;
		clear_Tablero();
	}

