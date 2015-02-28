	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#ifndef __CALCULOS_H__
	#define __CALCULOS_H__

	/*******************************************/
	/*                Máscaras                 */
	/*******************************************/

    #define MASCARA1 0x01
	#define MASCARA_FILA 0x02
	#define MASCARA_COL_SGN 0x04
	#define MASCARA_FILA_SGN 0x01

	/*******************************************/
	/*                 Funciones               */
	/*******************************************/

	//Vacia completamente el tablero (todo a 0's)
	void clear_Tablero(void);
	//Posiciona la raqueta1 en el nuevo lugar que se ha determinado
	void recalcularRaqueta1(void);
	//Posiciona la raqueta2 en el nuevo lugar que se ha determinado
	void recalcularRaqueta2(void);
	//Da paso al comienzo del juego
	void principio(void);
	//Actualiza la posicion de la pelota
	void actualizarPelota (void);

	#endif
