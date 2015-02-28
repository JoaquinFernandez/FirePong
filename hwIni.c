	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan Jos� Carracedo Justo
	*           Joaqu�n Fern�ndez Moreno
	*
	****************************************************************************/
	#include "m5272lib.h"
	#include "m5272.h"
	#include "hwIni.h"
	#include "DAC.h"

	//------------------------------------------------------
	// inline void rutina_ini_TMR0(void)
	//
	// Descripci�n:
	//   Funci�n por defecto de inicializaci�n del TMR0 (a 1kHz)
	//
	//------------------------------------------------------
	inline void rutina_ini_TMR0(void) {
	  mbar_writeByte(MCFSIM_PIVR,V_BASE);			// Fija comienzo de vectores de interrupci�n en V_BASE.
	  ACCESO_A_MEMORIA_LONG(DIR_VTMR0)= (ULONG)_prep_TOUT0; // Escribimos la direcci�n de la funci�n para TMR0
	  mbar_writeShort(MCFSIM_TMR0, 0x4F3D);		// TMR0: PS=0x50-1 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=1
	  mbar_writeShort(MCFSIM_TCN0, 0x0000);		// Ponemos a 0 el contador del TIMER0
	  mbar_writeShort(MCFSIM_TRR0, CNT_INT0);	// Fijamos la cuenta final del contador
	 cli();
	}
	//------------------------------------------------------
	// inline void rutina_ini_TMR1(void)
	//
	// Descripci�n:
	//   Funci�n por defecto de inicializaci�n del TMR1 (A 8kHz)
	//
	//------------------------------------------------------
	inline void rutina_ini_TMR1(void) {	
	  ACCESO_A_MEMORIA_LONG(DIR_VTMR1)= (ULONG)_prep_TOUT1; // Escribimos la direcci�n de la funci�n para TMR1
	  mbar_writeShort(MCFSIM_TMR1, 0x4F3D);		// TMR1: PS=0x50-1 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=1
	  mbar_writeShort(MCFSIM_TCN1, 0x0000);		// Ponemos a 0 el contador del TIMER1
	  mbar_writeShort(MCFSIM_TRR1, CNT_INT1);	// Fijamos la cuenta final del contador
	  mbar_writeLong(MCFSIM_ICR1, 0x8888CE88);	// Marca la interrupci�n del TIMER1 como no pendiente y de nivel 5 y la de 
	  //TIMER0 como no pendiente y de nivel 4
	 cli();
	}

	//------------------------------------------------------
	// inline void hwIni(void) {
	//
	// Descripci�n:
	//   Funci�n de inicializaci�n de las rutinas del MicroColdfire
	//
	//------------------------------------------------------
	inline void hwIni(void) {
		 DAC_ADC_init(); //Inicializamos el DAC para poder sacar sonidos
		 rutina_ini_TMR0();
		 rutina_ini_TMR1();
	}
