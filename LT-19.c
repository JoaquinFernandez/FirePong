	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan Jos� Carracedo Justo
	*           Joaqu�n Fern�ndez Moreno
	*
	****************************************************************************/
	#include "hwIni.c"
	#include "juego.c"
	#include "seleccionJuego.c"
	#include "pintar.c"
	#include "calculos.c"
	#include "swIni.c"
	#include "rutTimer0.c"
	#include "rutTimer1.c"
	#include "m5272lib.c"
	#include "teclado.c"
	#include "puerto.c"
	#include "DAC.c"
	#include "audio.h"
	#include "pongLib.h"

	//------------------------------------------
	// void bucleMain(void)
	//
	// Descripci�n:
	//   Bucle principal de la aplicacion
	//
	//------------------------------------------
	void bucleMain(void) {
		 swIni(); //Reinicia el valor de las variables usadas durante el juego
		 seleccionJuego(); //Interacciona con el usuario para saber los parametros del juego
		 sti();					// Habilitamos interrupciones
		 juego(); //Interacciona con el usuario para saber que desea hacer
		 finJuego(); //Muestra los resultados del juego al usuario
		 cli(); //Inhabilitamos las interrupciones
	}

	//------------------------------------------
	// void __init(void)
	//
	// Descripci�n:
	//   Funcion que se ejecuta al inicio del
	//   programa, y que solo se har� una vez
	//
	//------------------------------------------
	void __init(void) {
		hwIni(); //Configura el valor de inicializacion de las rutinas
	}

	//---------------------------------------------------------
	// Definici�n de rutinas de atenci�n a la interrupci�n
	// Es necesario definirlas aunque est�n vac�as
	void rutina_int1(void){}
	void rutina_int2(void){}
	void rutina_int3(void){}
	void rutina_int4(void){}
	void rutina_tout2(void){}
	void rutina_tout3(void){}
