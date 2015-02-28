	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#include "seleccionJuego.h"
	#include "m5272lib.h"
	#include "teclado.h"
	#include "pongLib.h"

	//------------------------------------------------------
	// void seleccionJuego(void)
	//
	// Descripción:
	//  Inicializa el menú del juego dando al usuario la
	//  posibilidad de elegir los parametros del juego
	//
	//------------------------------------------------------
	void seleccionJuego(void) {     
		char tecla;
		char valorSel = 0;
		output("************************************************************ \n");
		output("                        PongFire                             \n");
		output("************************************************************ \n \n");
		output("Elija el número de jugadores : (1) 1 Jugador (2) 2 Jugadores \n");
		
		while (tecla != '1' && tecla != '2') {
			 
			tecla = teclado(); //El estado actual
			if (tecla == '1' || tecla == '2') {
				valorSel = tecla - charToInt;
				output("Modo ");
				outNum(baseDecimal, valorSel, 0);
				output(" jugador(es) \n");
				menu.nroJugador = valorSel;
			}
			else
				output("Tecla incorrecta, seleccione el número de jugadores \n");
		}
		tecla = 0; //Reiniciamos el valor de tecla para que no haya conflictos
		output("Elija el nivel de dificultad del juego : \n      (1) Fácil \n      (4) Medio \n      (7) Difícil \n");
		
		while (tecla != '1' && tecla != '4' && tecla != '7') {
			 
			tecla = teclado(); ////El estado actual
			switch(tecla) {
				case '1':
					 output("Nivel de dificultad seleccionado: Fácil \n");
					 menu.dificultad = facil;
					 break;
				case '4':
					 output("Nivel de dificultad seleccionado: Medio \n");
					 menu.dificultad = medio;
					 break;
				case '7':
					 output("Nivel de dificultad seleccionado: Difícil \n");
					 menu.dificultad = dificil;
					 break;
				default:
				output("Nivel de dificultad incorrecto");
			}
		}
		tecla = 0; //Reiniciamos el valor de tecla para que no haya conflictos
		output("Elija la longitud de las raquetas : \n      (2) 2 posiciones \n      (3) 3 posiciones \n      (4) 4 posiciones \n      (5) 5 posiciones \n");
		
		while (tecla != '2' && tecla != '3' && tecla != '4' && tecla != '5') {
			tecla = teclado(); //El estado actual
			if (tecla == '2' || tecla == '3' || tecla == '4' || tecla == '5') {
				valorSel = tecla - charToInt;
				output("La longitud de la raqueta sera ");
				outNum(baseDecimal, valorSel, 0);
				output(" \n");
				menu.largoRaqueta = valorSel;
			}
			else
				output("Tecla incorrecta, seleccione la longitud de la raqueta \n");
		}
		tecla = 0; //Reiniciamos el valor de tecla para que no haya conflictos
		output("Elija el número de vidas : \n      (1) 1 vida \n      (2) 2 vidas \n      (3) 3 vidas \n      (4) 4 vidas \n      (5) 5 vidas \n");
		
		while (tecla != '1' && tecla != '2' && tecla != '3' && tecla != '4' && tecla != '5') {

			tecla = teclado(); //El estado actual
			if (tecla == '1' || tecla == '2' || tecla == '3' || tecla == '4' || tecla == '5') {
				valorSel = tecla - charToInt;
				output("El numero de vidas sera  ");
				outNum(baseDecimal, valorSel, 0);
				output(" \n");
				puntuacion.vidasJugador1 = valorSel;
				puntuacion.vidasJugador2 = valorSel;
			}
			else
				output("Tecla incorrecta, seleccione el numero de vidas \n");
		}
		tecla = 0; //Reiniciamos el valor de tecla para que no haya conflictos
		output(" Pulse A para comenzar la partida... \n");
		while (tecla != 'A') {
	 
			tecla = teclado(); //El estado actual

			if (tecla != 'A') {

				output("Tecla no válida. Por favor pulse A para jugar... \n");
			}
		}
	}
