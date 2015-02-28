	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#include "pintar.h"
	#include "pongLib.h"

	//------------------------------------------
	// inline void pintaRaqueta(void)
	//
	// Descripción:
	//   Ocupa en el tablero las posiciones de la
	//   raqueta
	//
	//------------------------------------------
	inline void pintaRaqueta(void) {
		 int i;
		 char raqini = tablero.raqueta1.pos_Ini;
		 int raqCol = tablero.raqueta1.col;
		 char raqlargo = tablero.raqueta1.largo + raqini;
		 for( i = raqini; i < raqlargo; i++) {
			  tablero.tablero[i][raqCol] = encendido;
		 }
		 if (menu.nroJugador == 2) {
			   raqini = tablero.raqueta2.pos_Ini;
			   raqCol = tablero.raqueta2.col;
			   raqlargo = tablero.raqueta2.largo + raqini;
			   for( i = raqini; i < raqlargo; i++) {
					tablero.tablero[i][raqCol] = encendido;
			   }
		 }    
	}

	//------------------------------------------
	// inline void pintaPelota(void)
	//
	// Descripción:
	//   Ocupa en el tablero las posiciones de la 
	//   pelota
	//
	//------------------------------------------
	inline void pintaPelota(void) {
		   int posFila = tablero.pelota.fila;
		   int posCol = tablero.pelota.col;
		   tablero.tablero[posFila][posCol] = encendido;
	}

	//------------------------------------------
	// inline void pintar(void)
	//
	// Descripción:
	//   Función de llamada
	//
	//------------------------------------------
	inline void pintar(void) {
		   clear_Tablero();
		   pintaRaqueta();
		   pintaPelota();
	}
