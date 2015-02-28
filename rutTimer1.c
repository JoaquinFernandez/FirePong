	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#include "rutTimer1.h"
	#include "audio.h"
	#include "DAC.h"

	//------------------------------------------------------
	// void rutina_tout1(void)
	//
	// Descripción:
	//   Función de atención a la interrupción para TMR1
	//
	//------------------------------------------------------
	void rutina_tout1(void) {
		 mbar_writeShort(MCFSIM_TER1,BORRA_REF);//Marca la interrupcion como no pendiente
		 if (rebote) {
					if (rebote == rebotePared) {
					   if (muestraActual < totalMuestrasPared) {
						  DAC_dato(muestraPared[muestraActual]);
						  muestraActual++;
					   }
					   else {
						  muestraActual = 0;
						  rebote = 0;
					   }
					}
					else if (rebote == reboteRaqueta) {
					   if (muestraActual < totalMuestrasRaqueta) {
						  DAC_dato(muestraRaqueta[muestraActual]);
						  muestraActual++;
					   }
					   else {
						  muestraActual = 0;
						  rebote = 0;
					   } 
					}
					else if (rebote == rebotePierde) {
					   if (muestraActual < totalMuestrasPierde) {
						  DAC_dato(muestraPierde[muestraActual]);
						  muestraActual++;
					   }
					   else {
						  muestraActual = 0;
						  rebote = 0;
					   }
					}
					if (muestraActual < totalMuestrasPared) {
						  DAC_dato(muestraPared[muestraActual]);
						  muestraActual++;
					   }
					   else {
						  muestraActual = 0;
						  rebote = 0;
					   }
		 }
		 else if (estado == estadoJugando) {
			  DAC_dato(muestraJugando[muestraActual]);
			  muestraActual++;
			  if (muestraActual == totalMuestrasJugando) 
				 muestraActual = 0;
		 }
		 else if (estado == estadoPrincipio) {
			  DAC_dato(muestraPrincipio[muestraActual]);
			  muestraActual++;
			  if (muestraActual == totalMuestrasPrincipio) 
				 muestraActual = 0;
		 }
		 else if (estado == estadoFinJuego) {
			  DAC_dato(muestraFinJuego[muestraActual]);
			  muestraActual++;
			  if (muestraActual == totalMuestrasFinJuego) 
				 muestraActual = 0;
		 }
	}
