	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#ifndef __PUERTO_H__
	#define __PUERTO_H__

	/*******************************************/
	/*  Direcciones de memoria de los puertos  */
	/*******************************************/

	#define BASE_PUERTO_S              0x40000000 /* Direccion del puerto S (Byte alto)*/
	#define PUERTO_E_ALTO              0x50000002 /* Direccion del puerto E (Byte alto)*/
	#define PUERTO_E_BAJO              0x50000003 /* Direccion del puerto E (Byte bajo)*/

	/*******************************************/
	/*                Máscaras                 */
	/*******************************************/

	#define MASCARA_FILAS                   0x00FF /* Máscara para insertar columnas */
	#define MASCARA_COLUMNAS                0xFF0F /* Máscara para insertar columnas */
	#define MASCARA_TECLADO                 0xFFF0 /* Máscara para insertar teclado */

	/*******************************************/
	/*                 Funciones               */
	/*******************************************/

	//Pone el valor de los 8bits mas significativos del byte mas significativo del puerto de salida
	void set_puertoS_filas (UBYTE valor);

	//Pone el valor de los 4 bits mas significativos del byte menos significativo puerto de salida
	void set_puertoS_columnas (UBYTE valor);

	//Pone el valor de los 4 bits menos significativos del byte menos significativo puerto de salida
	void set_puertoS_teclado (UBYTE valor);

	//Lee el valor de los 16 bits del puerto de entrada
	UWORD lee16_puertoE (void);

	//Lee el valor de los 8 bits menos significativos del puerto de entrada
	UBYTE lee_puertoE (void);

	#endif
