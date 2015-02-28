	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#include "teclado.h"
	#include "seleccionJuego.h"
	#include "calculos.h"
	#include "juego.h"
	#include "rutTimer0.h"
	#include "pongLib.h"

	//------------------------------------------------------
	// void juego(void)
	//
	// Descripción:
	//  Inicializa el juego y permite al usuario interactuar
	//  con el juego
	//
	//------------------------------------------------------
	void juego(void) {
		principio();
		while (estado) {
			char tecla;
			tecla = teclado();
			switch(tecla) {
				case 'A':
					 return;
				case '1':
					tablero.raqueta1.pos_Sig = avanzaArriba;
					break;
				case '4':
					tablero.raqueta1.pos_Sig = avanzaAbajo;
					break;
				default:
					break;
			}
			recalcularRaqueta1();
			if (menu.nroJugador == 2) {
				switch(tecla) {
						case 'C':
							tablero.raqueta2.pos_Sig = avanzaArriba;
							break;
						case 'D':
							tablero.raqueta2.pos_Sig = avanzaAbajo;
							break;
						default:
							break;
				}
				recalcularRaqueta2();
			}
		}
		clear_Tablero();
	}

	//------------------------------------------------------
	// void finJuego(void)
	//
	// Descripción:
	//  Finaliza el juego y presenta los resultados
	//
	//------------------------------------------------------
	void finJuego(void) {
		int puntos1 = puntuacion.puntosJugador1;
		output("************************************************************ \n");
		output("                       Resultados                            \n");
		output("************************************************************ \n \n");
		if (menu.nroJugador == 2) {
             		if (puntuacion.vidasJugador1 == 0 || puntuacion.vidasJugador2 == 0) {
			    int puntos2 = puntuacion.puntosJugador2;
			    output("¡Felicidades ");
			    if (puntuacion.vidasJugador1 == 0)
				    output("Jugador 2 ");
		            else if (puntuacion.vidasJugador2 == 0)
				    output("Jugador 1 ");
			    output("ha vencido! \n");
			    output("Puntuacion del Jugador 1 :");
			    outNum(baseDecimal, puntos1, 0);
			    output(" puntos \n");
			    output("\n Puntuacion del Jugador 2 :");
			    outNum(baseDecimal, puntos2, 0);
			    output(" puntos \n");
			    if (puntos1 > record) {
				   record = puntos1;
				   output("¡Felicidades Jugador 1, ha batido el record! \n");
		            }
			    else if (puntos2 > record) {
				   record = puntos2;
				   output("¡Felicidades Jugador 2, ha batido el record! \n");
			    }
			    else {
				   output("El record esta en: ");
				   outNum(baseDecimal, record, 0);
				   output(" puntos \n");
			    }
             	       }
             	       else
                  		output ("La partida finalizo prematuramente \n");    
	     }
	     else if (puntuacion.vidasJugador1 == 0) {
			 output("Su puntuación ha sido: ");
			 outNum(baseDecimal, puntos1, 0);
			 output(" puntos \n");
			 if (puntos1 > record) {
				record = puntos1;
				output("¡Felicidades ha batido el record! \n");
			 }
	     }
	     else
		     output ("La partida finalizo prematuramente \n");
		     parar(diezSegundos);
	}
