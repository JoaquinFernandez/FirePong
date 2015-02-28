	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#ifndef __PONGLIB_H__
	#define __PONGLIB_H__

	/*******************************************/
	/*     Valores de referencia               */
	/*******************************************/

	//Valor que hay que restar a un CHAR para pasarlo a INT
	const char charToInt = 48;
	//Elemento activo
	const char encendido = 1;
	//Elemento no activo
	const char apagado = 0;
	//Primera fila de la matriz de leds
	const char primeraFila = 0;
	//Primera columna de la matriz de leds
	const char primeraCol = 0;
	//Ultima fila de la matriz de leds
	const char ultimaFila = 6;
	//Ultima columna de la matriz de leds
	const char ultimaCol = 9;
	//Columna desde la cual se impacta con la raqueta1
	const char colImpactoRaqueta1 = 1;
	//Columna desde la cual se impacta con la raqueta2
	const char colImpactoRaqueta2 = 8;
	//Numero de filas de la matriz de leds
	const char nroFilas = 7;
	//Numero de columnas de la matriz de leds
	const char nroCol = 10;
	//Objeto del tablero moviendose hacia arriba
	const char avanzaArriba = -1;
	//Objeto del tablero moviendose hacia abajo
	const char avanzaAbajo = 1;
	//Objeto del tablero moviendose hacia la derecha
	const char avanzaDcha = 1;
	//Objeto del tablero moviendose hacia la izquierda
	const char avanzaIzq = -1;
	//Objeto del tablero moviendose recto
	const char avanzaRecto = 0;
	//Estado glogal que indica que el jugador esta comenzando la partida
	const char estadoPrincipio = 3;
	//Estado glogal que indica que el jugador esta en el juego
	const char estadoJugando = 2;
	//Estado glogal que indica que el jugador esta seleccionando las opciones
	const char estadoMenu = 1;
	//Estado glogal que indica que el jugador ha acabado el juego
	const char estadoFinJuego = 0;
	//Posicion de la fila en la que comienza la raqueta por defecto
	const char pIniRaqueta = 2;
	//Opcion para seleccionar que se quiere usar la base decimal
	const char baseDecimal = 10;
	//Indica que se ha perdido una vida
	const char rebotePierde = 1;
	//Indica que la pelota ha rebotado contra la raqueta
	const char reboteRaqueta = 2;
	//Indica que la pelota ha rebotado contra la pared
	const char rebotePared = 3;
	//Posicion inicial de la pelota (columna)
	const char pIniPelotaCol = 5;
	//Posicion inicial de la pelota (fila)
	const char pIniPelotaFila = 3;
	//Nivel del juego facil, se actualiza la posicion de la pelota cada 1000 milisegundos
	const int facil = 1000;
	//Nivel del juego medio, se actualiza la posicion de la pelota cada 750 milisegundos
	const int medio = 750;
	//Nivel del juego dificil, se actualiza la posicion de la pelota cada 500 milisegundos
	const int dificil = 500;
	//Nivel del juego muy dificil, se actualiza la posicion de la pelota cada 250 milisegundos
	const int muyDificil = 250;
	//Representa un segundo en milisegundos
	const int unSegundo = 1000;
	//Representa diez segundos en milisegundos
	const int diezSegundos = 10000;

	/*******************************************/
	/*           Tipos de Variables            */
	/*******************************************/

	//Datos referentes a los dos jugadores
	typedef struct {
			int puntosJugador1;
			int puntosJugador2;
			char vidasJugador1;
			char vidasJugador2;
	} Puntuacion;
	//Datos referentes a la pelota del juego
	typedef struct {
			char fila; //Fila actual de la pelota
			char col; //Columna actual de la pelota
			char fila_Sig; //Dirección que llevará la pelota en las filas
			char col_Sig; //Dirección que llevará la pelota en las columnas

	} Pelota;
	//Datos referentes a la raqueta del juego
	typedef struct {
			char largo;
			char col;
			char pos_Ini; //Fila en la que comienza la raqueta
			char pos_Sig; //Direccion que llevará la raqueta al moverse
	} Raqueta;
	//Datos referentes a la matriz de leds del juego
	typedef struct {
			char tablero[7][10]; //Array de dos dimensiones que representa
			//las posiciones de la matriz de LED's
			Pelota pelota;
			Raqueta raqueta1;
			Raqueta raqueta2;
	} Tablero;
	//Datos seleccionados por el jugador
	typedef struct {
			int dificultad; //Tiempo en milisegundos que tardará la pelota en
			//cambiar de posición
			char nroJugador;
			char largoRaqueta;
	} Menu;

	/*******************************************/
	/*            Variables globales           */
	/*******************************************/
	//Estado global del juego
	char estado;
	//Indica que tipo de rebote se ha producido(Utilizado para el sonido)
	char rebote;
	//Datos que el usuario ha seleccionado para el juego
	Menu menu;
	//Datos referentes a los objetos del juego
	Tablero tablero;
	//Puntuaciones de los jugadores
	Puntuacion puntuacion;
	//Puntos maximos conseguidos en todas las ejecuciones del juego
	int record = 0;
	//Muestra de sonido actual 
	int muestraActual = 0;

	#endif
