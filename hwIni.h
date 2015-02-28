	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#ifndef __HWINI_H__
	#define __HWINI_H__

	/*******************************************/
	/*  Direcciones de memoria de los puertos  */
	/*******************************************/

	#define V_BASE 0x40				  // Dirección de inicio de los vectores de interrupción
	#define DIR_VTMR0 4*(V_BASE+5)			  // Dirección del vector de TMR0
	#define DIR_VTMR1 4*(V_BASE+6)			  // Dirección del vector de TMR1

	/*******************************************/
	/*     Valores de referencia               */
	/*******************************************/

	#define FREC_INT 1000				  // Frec. de interr. TMR0 = 1000 Hz (cada 1ms)
	#define CNT_INT0 MCF_CLK/(FREC_INT*0x50*16)	  // Valor de precarga del temporizador de interrupciones TRR0
	#define BORRA_REF 0x0002			  // Valor de borrado de interr. pendientes de tout1 para TER0

	#define FREC_INT2 8000				  // Frec. de interr. TMR0 = 8000 Hz 
	#define CNT_INT1 MCF_CLK/(FREC_INT2*0x50*16)	  // Valor de precarga del temporizador de interrupciones TRR1


	/*******************************************/
	/*                 Funciones               */
	/*******************************************/

	//Inicializa el valor de las rutinas del MicroColdfire
	inline void hwIni(void);

	#endif
