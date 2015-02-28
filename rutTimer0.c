	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#include "rutTimer0.h"
	#include "m5272.h"
	#include "puerto.h"
	#include "pintar.h"
	#include "calculos.h"
	#include "pongLib.h"


	static char sleep = 0;
	static int cont = 0;
	static int contSleep = 0;
	static int colActual = 0;

	//------------------------------------------------------
	// void actualizar(void)
	//
	// Descripción:
	//   Función que refresca la matriz de leds
	//
	//------------------------------------------------------
	void actualizar(int colActual) {
		UBYTE valor = 0;
		int i;
		char a;
		for (i = primeraFila; i < nroFilas;i++) {
		  
			 a = tablero.tablero[i][colActual];
			 a ^= 1; //invierte el valor de la variable a (un 1 pasa a 0 y viceversa)
			 valor += (a << i);
		}
		set_puertoS_filas(valor);
		set_puertoS_columnas( (UBYTE) colActual);
	}

	//------------------------------------------------------
	// void parar(ULONG milisegundos)
	//
	// Descripción:
	//   Función que detiene la ejecucion del programa
	//   principal los milisegundos indicados.
	//
	//------------------------------------------------------
	void parar(ULONG milisegundos) {
		sleep = encendido;
		contSleep = milisegundos;	// Inicializa el contador
		while(contSleep > 0){
		}
		// Espera a que llegua a cero
		sleep = apagado;
		cont = 0;
	}

	//------------------------------------------------------
	// void rutina_tout0(void)
	//
	// Descripción:
	//   Función de atención a la interrupción para TMR0
	//
	//------------------------------------------------------
	void rutina_tout0(void) {
		 mbar_writeShort(MCFSIM_TER0,BORRA_REF);//Marca la interrupcion como no pendiente
		 if (sleep == encendido) {
			 contSleep--;
		 }
		 else {
			cont++;
		 }
		 if (cont%2 == 0) {
			 if (estado == estadoJugando) 
				 pintar();
			 actualizar(colActual);
			 colActual++;
			 if (colActual > ultimaCol) {
				 colActual = primeraCol;
			 }
		 }
		 if (cont == menu.dificultad) {
			 actualizarPelota();
			 //Actualizamos el estado de juego
			 cont = 0;	 //Reiniciamos el contador a 0 para que no se haga
							 //muy grande, aunque provoca que 1 de cada 333 columnas
							 //tarde 4 ms en vez de 3 ms en refrescarse
		 }
	}
