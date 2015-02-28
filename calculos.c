	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#include "calculos.h"
	#include "rutTimer0.h"
	#include "pongLib.h"
	#include "m5272.h"
	#include "puerto.h"
  	#include "audio.h"
	
	//------------------------------------------------------
	// void clear_Tablero(void)
	//
	// Descripción:
	//  Pone a 0's el tablero de juego (todos los leds apagados)
	//
	//------------------------------------------------------
	void clear_Tablero(void) {
		int i;
		int j;
		for (i = primeraFila; i < nroFilas; i++) {
			for (j = primeraCol; j < nroCol; j++) {
				tablero.tablero[i][j] = apagado;
			}
		}
	}

	//------------------------------------------------------
	// void raqueta (void)
	//
	// Descripción:
	//  Posiciona las raquetas en el tablero de juego 
	//
	//------------------------------------------------------
	void raqueta (void) {
		 //Crea las raquetas para el tablero, teniendo en cuenta que sea para 1 jugador o 2 jugadores
		tablero.raqueta1.col = primeraCol;
		tablero.raqueta1.largo = menu.largoRaqueta;
		tablero.raqueta1.pos_Ini = pIniRaqueta;
		if (menu.nroJugador == 2) {
		   tablero.raqueta2.col = ultimaCol;
		   tablero.raqueta2.largo = menu.largoRaqueta;
		   tablero.raqueta2.pos_Ini = pIniRaqueta;
		}
	}

	//------------------------------------------------------
	// void recalcularRaqueta1(void)
	//
	// Descripción:
	//  Calcula la nueva posicion de la raqueta 1
	//
	//------------------------------------------------------
	void recalcularRaqueta1(void) {
		 char* pIni = &tablero.raqueta1.pos_Ini;
		 char* pSig = &tablero.raqueta1.pos_Sig;
		 char raqLargo = tablero.raqueta1.largo;
		 if ((*pIni == primeraFila && *pSig == avanzaArriba) || ((*pIni + raqLargo - 1) == ultimaFila && *pSig == avanzaAbajo)) {
			  //Si la raqueta esta en los limites, no se mueve
		 }
		 else if (tablero.pelota.col == primeraCol && (tablero.pelota.fila == (*pIni + *pSig) || tablero.pelota.fila == (*pIni + *pSig + raqLargo))) {
			  //Para que la raqueta no se superponga a la pelota si ya se ha perdido el rebote
		 } 
		 else {
			  //Si no hay ningún impedimento, la raqueta se mueve
			  *pIni += *pSig;
		 }
		 //En cualquier caso, para que no se acumulen movimientos, la siguiente posicion de la raqueta se reinicia
		 *pSig = 0;
	}

	//------------------------------------------------------
	// void recalcularRaqueta2(void)
	//
	// Descripción:
	//  Calcula la nueva posicion de la raqueta 2
	//
	//------------------------------------------------------
	void recalcularRaqueta2(void) {
		 char* pIni = &tablero.raqueta2.pos_Ini;
		 char* pSig = &tablero.raqueta2.pos_Sig;
		 char raqLargo = tablero.raqueta2.largo;
		 if ((*pIni == primeraFila && *pSig == avanzaArriba) || ((*pIni + raqLargo - 1) == ultimaFila && *pSig == avanzaAbajo)) {
			  //Si la raqueta esta en los limites, no se mueve
		 }
		 else if (tablero.pelota.col == ultimaCol && (tablero.pelota.fila == (*pIni + *pSig) || tablero.pelota.fila == (*pIni + *pSig + raqLargo))) {
			  //Para que la raqueta no se superponga a la pelota si ya se ha perdido el rebote
		 } 
		 else {
			  //Si no hay ningún impedimento, la raqueta se mueve
			  *pIni += *pSig;
		 }
		 //En cualquier caso, para que no se acumulen movimientos, la siguiente posicion de la raqueta se reinicia
		 *pSig = 0;
	}

	//------------------------------------------------------
	// void pelota (void)
	//
	// Descripción:
	//  Posiciona una pelota en el tablero y le da una
	//  direccion inicial aleatoria
	//
	//------------------------------------------------------
	void pelota (void) {
		char movLat = avanzaDcha; // a 1 porque no puede quedar por defecto sin moverse
		char movVer = avanzaRecto;
        UBYTE valorTCN = mbar_readShort(MCFSIM_TCN0); //Lee el contenido del registro TCN del TIMER0
		BYTE fila = (valorTCN & MASCARA_FILA) >> 1; //Para dejar el valor en el ultimo bit
		BYTE colSigno = (MASCARA_COL_SGN & valorTCN) >> 2; //Para tener el signo de la columna
		BYTE filaSigno = (MASCARA_FILA_SGN & valorTCN); //Para tener el signo de la fila
		if (colSigno == MASCARA1) // Si hay signo entonces se mueve a izquierdas
			movLat = avanzaIzq;
		if (fila == MASCARA1) { //Comprobamos si tiene que ir arriba o abajo
			if ( filaSigno == MASCARA1)
				movVer = avanzaArriba;
			else
				movVer = avanzaAbajo;
		}
		//Si no, tiene que ir recto, que es su valor por defecto
		tablero.pelota.col_Sig = movLat; 
		tablero.pelota.fila_Sig = movVer; 
		//Posicion inicial de la pelota en el tablero
		tablero.pelota.col = pIniPelotaCol;
		tablero.pelota.fila = pIniPelotaFila;
	}

	//------------------------------------------------------
	// void actualizarPelota (void)
	//
	// Descripción:
	//  Actualiza la posicion de la pelota teniendo en cuenta
	//  los posibles rebotes e impactos que puedan darse
	//
	//------------------------------------------------------
	void actualizarPelota (void) {
		 char* pFila = &tablero.pelota.fila;
		 char* pCol = &tablero.pelota.col;
		 char* pFilaS = &tablero.pelota.fila_Sig;
		 char* pColS = &tablero.pelota.col_Sig;
		 
		 if ((*pFila == primeraFila && *pFilaS == avanzaArriba) || (*pFila == ultimaFila && *pFilaS == avanzaAbajo)) {
				//Si estamos en la primera fila y vamos hacia arriba o en la ultima y hacia abajo, 
				//conmutamos el valor de la fila siguiente para que rebote
			    	muestraActual = 0; //Para sacar un sonido hay que reiniciar el valor de la ultima muestra
				rebote = rebotePared; //Definimos el tipo de rebote para saber que sonido usar
				*pFilaS = -(*pFilaS);
		 }
		 if (*pCol ==  colImpactoRaqueta1 && *pColS == avanzaIzq) {
				   //Aritmetica de rebotes
				   char pIni = tablero.raqueta1.pos_Ini;
				   char largo = tablero.raqueta1.largo + pIni - 1;
				   char filaImpacto = *pFila + *pFilaS;
				   if (filaImpacto == pIni) {
						//Si impacta en el extremo superior de la raqueta, el rebote es diagonal hacia arriba al tablero
						 *pColS = avanzaDcha;
						 *pFilaS = avanzaArriba;
						 muestraActual = 0;
						 rebote = reboteRaqueta;
						 puntuacion.puntosJugador1++;
				   }
				   else if (filaImpacto == largo) {
						//Si impacta en el extremo inferior de la raqueta, el rebote es diagonal hacia abajo al tablero
						 *pColS = avanzaDcha;
						 *pFilaS = avanzaAbajo;
						 muestraActual = 0;
						 rebote = reboteRaqueta;
						 puntuacion.puntosJugador1++;
				   }
				   else if ((filaImpacto > pIni) && ((filaImpacto) < largo)) {
						 //Si impacta en cualquier posicion de en medio de la raqueta, el rebote es paralelo al tablero
						 *pColS = avanzaDcha;
						 *pFilaS = avanzaRecto;
						 muestraActual = 0;
						 rebote = reboteRaqueta;
						 puntuacion.puntosJugador1++;
				   }
		 }
		 if (*pCol == primeraCol && *pColS == avanzaIzq) {
				   //Si estamos en la primera columna y la pelota va hacia la izquierda
				   //el jugador uno pierde una vida      
				   puntuacion.vidasJugador1--;
				   muestraActual = 0;
				   rebote = rebotePierde;
				   if (puntuacion.vidasJugador1 == 0) {
					   muestraActual = 0;
					  estado = estadoFinJuego;
				   }
				   else pelota();
		 }
		 if (*pCol == colImpactoRaqueta2 && *pColS == avanzaDcha && menu.nroJugador == 2) {
				   //Aritmetica de rebotes
				   char pIni = tablero.raqueta2.pos_Ini;
				   char largo = tablero.raqueta2.largo + pIni - 1;
				   char filaImpacto = *pFila + *pFilaS;
				   if (filaImpacto == pIni) {
						//Si impacta en el extremo superior de la raqueta, el rebote es diagonal hacia arriba al tablero
						 *pColS = avanzaIzq;
						 *pFilaS = avanzaArriba;
						 muestraActual = 0;
						 rebote = reboteRaqueta;
						 puntuacion.puntosJugador2++;
				   }
				   else if (filaImpacto == largo) {
						//Si impacta en el extremo inferior de la raqueta, el rebote es diagonal hacia abajo al tablero
						 *pColS = avanzaIzq;
						 *pFilaS = avanzaAbajo;
						 muestraActual = 0;
						 rebote = reboteRaqueta;
						 puntuacion.puntosJugador2++;
				   }
				   else if (((filaImpacto) > pIni) && ((filaImpacto) < largo)) {
						 //Si impacta en cualquier posicion de en medio de la raqueta, el rebote es paralelo al tablero
						 *pColS = avanzaIzq;
						 *pFilaS = avanzaRecto;
						 muestraActual = 0;
						 rebote = reboteRaqueta;
						 puntuacion.puntosJugador2++;
				   }
		 }
		 if (*pCol == ultimaCol && *pColS == avanzaDcha && menu.nroJugador == 2) {
				   //La pelota llega al final y se quita una vida al jugador 2 (modo 2 jugadores)
				   puntuacion.vidasJugador2--;
				   muestraActual = 0;
				   rebote = rebotePierde;
				   if (puntuacion.vidasJugador2== 0) {
					   muestraActual = 0;
					  estado = estadoFinJuego;
				   }
				   else pelota();
		 }
		 else if (*pCol == ultimaCol && *pColS == avanzaDcha) {
				   //La pelota llega al final y rebota (modo 1 jugador)
				   muestraActual = 0;
				   rebote = rebotePared;
				   *pColS = -(*pColS); //Rebote
		 }
		 if ((*pFila == primeraFila && *pFilaS == avanzaArriba) || (*pFila == ultimaFila && *pFilaS == avanzaAbajo)) {
			        muestraActual = 0;
				rebote = rebotePared;
				*pFilaS = -(*pFilaS); //Toca sacar un sonido
		 }
		 *pFila += *pFilaS;
		 *pCol += *pColS;
	}

	//------------------------------------------------------
	// void principio(void)
	//
	// Descripción:
	//  Limpia el tablero, saca un 3,2,1 por la matriz de leds
	//  e inicializa el juego
	//
	//------------------------------------------------------
	void principio(void) {
		muestraActual = 0;
		estado = estadoPrincipio;
		//Dejamos el juego a la espera un segundo
		parar(unSegundo);
		//Sacamos un 3 por el display de LEDS
		tablero.tablero[1][3] = encendido;
		tablero.tablero[1][4] = encendido;
		tablero.tablero[1][5] = encendido;
		tablero.tablero[2][5] = encendido;
		tablero.tablero[3][4] = encendido;
		tablero.tablero[3][5] = encendido;
		tablero.tablero[4][5] = encendido;
		tablero.tablero[5][3] = encendido;
		tablero.tablero[5][4] = encendido;
		tablero.tablero[5][5] = encendido;
		//Dejamos un segundo
		parar(unSegundo);
		//Limpiamos el tablero
		clear_Tablero();

		//Sacamos un 2 por el display de LEDS
		tablero.tablero[1][3] = encendido;
		tablero.tablero[1][4] = encendido;
		tablero.tablero[1][5] = encendido;
		tablero.tablero[2][5] = encendido;
		tablero.tablero[3][3] = encendido;
		tablero.tablero[3][4] = encendido;
		tablero.tablero[3][5] = encendido;
		tablero.tablero[4][3] = encendido;
		tablero.tablero[5][3] = encendido;
		tablero.tablero[5][4] = encendido;
		tablero.tablero[5][5] = encendido;
		//Dejamos un segundo
		parar(unSegundo);
		//Limpiamos el tablero
		clear_Tablero();

		
		tablero.tablero[1][5] = encendido;
		tablero.tablero[2][4] = encendido;
		tablero.tablero[2][5] = encendido;
		tablero.tablero[3][5] = encendido;
		tablero.tablero[4][5] = encendido;
		tablero.tablero[5][5] = encendido;
		//Dejamos un segundo
		parar(unSegundo);
		//Limpiamos el tablero
		clear_Tablero();

		tablero.tablero[1][0] = encendido;
		tablero.tablero[1][1] = encendido;
		tablero.tablero[1][2] = encendido;
		tablero.tablero[1][3] = encendido;
		tablero.tablero[2][0] = encendido;
		tablero.tablero[3][0] = encendido;
		tablero.tablero[4][0] = encendido;
		tablero.tablero[5][0] = encendido;
		tablero.tablero[5][1] = encendido;
		tablero.tablero[5][2] = encendido;
		tablero.tablero[5][3] = encendido;
		tablero.tablero[4][3] = encendido;
		tablero.tablero[3][3] = encendido;
		tablero.tablero[3][2] = encendido;
		tablero.tablero[1][5] = encendido;
		tablero.tablero[1][6] = encendido;
		tablero.tablero[1][7] = encendido;
		tablero.tablero[2][5] = encendido;
		tablero.tablero[2][7] = encendido;
		tablero.tablero[3][5] = encendido;
		tablero.tablero[3][7] = encendido;
		tablero.tablero[4][5] = encendido;
		tablero.tablero[4][7] = encendido;
		tablero.tablero[5][5] = encendido;
		tablero.tablero[5][6] = encendido;
		tablero.tablero[5][7] = encendido;
		tablero.tablero[1][9] = encendido;
		tablero.tablero[2][9] = encendido;
		tablero.tablero[3][9] = encendido;
		tablero.tablero[5][9] = encendido;
		//Dejamos un segundo
		parar(unSegundo);
		//Limpiamos el tablero
		clear_Tablero();

		//Creamos los elementos de juego
		raqueta();
		pelota();
		muestraActual = 0;
		estado = estadoJugando;
	}
