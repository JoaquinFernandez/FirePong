//------------------------------------------------------------------------------
// m5272adc-dac.c
//
//   Funciones de configuraci�n y control de los conversores ADC/DAC de la
//   plataforma de desarrollo ENT2004CF
//
// Autor: Javier Guill�n �lvarez
//------------------------------------------------------------------------------

#include "m5272.h"
#include "m5272lib.c"

//------------------------------------------------------------------  
//                      CONFIGURACI�N DEL QSPI
//------------------------------------------------------------------  

//------------------------------------------------------------------
// void DAC_ADC_init()
//
// Descripci�n:
//    Inicializa el QSPI para el uso del DAC y del ADC.
//
// Autor: Javier Guill�n �lvarez
//------------------------------------------------------------------
void DAC_ADC_init()
{  
  mbar_writeShort(MCFSIM_ICR4, MASCARA_INT); 	// Desactivar interr QSPI
  mbar_writeLong(MCFSIM_PACNT, MASCARA_PUERTOA); 	// Puerto A como Puerto IO y QSPI_CS1
  
  mbar_writeShort(MCFSIM_QDLYR, MASCARA_RETARDO);	// Retardos inicial y final por defecto, QSPI deshabilitado
  mbar_writeShort(MCFSIM_QIR, MASCARA_SPIF);		// Sin interrupciones y borrar SPIF

  mbar_writeShort(MCFSIM_QMR,QSPI_QMR_INIT);	// Maestro,16bits,CPOL = 0,CPHA = 0,BAUD sin definir 
 
}

//------------------------------------------------------------------  
//                      FUNCIONES DEL DAC
//------------------------------------------------------------------  

#define DAC_BAUD_RATE 10000000				// Baudios de Tx serie del DAC (M�ximo 10000000)

void DAC_escribeTxRAM(int dato){
  mbar_writeShort(MCFSIM_QAR, QSPI_TX_RAM_START); 	// Puntero datos para transmitir
  mbar_writeShort(MCFSIM_QDR, dato << 1); 		// Escribe el dato  en TX RAM

  // El formato de los 16 bits a transmitir al DAC es:
  //  --- --- --- ----- ----- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---
  // | 0 | 0 | 0 | D11 | D10 | D9 | D8 | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | 0 |
  //  --- --- --- ----- ----- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---
  // donde Dx es el bit x del dato que se convertir�
}

void DAC_escribeCommandRAM(){
  mbar_writeShort(MCFSIM_QAR, QSPI_COMMAND_RAM_START); 	// Puntero commands
  mbar_writeShort(MCFSIM_QDR, MASCARA_QDR); 			// Comando Tx, CS1 no continua >8 bits SIN retardos 
}

//---------------------------------------------------------
// void DAC_dato(int dato)
//
// Descripci�n: 
//    Env�a un dato al DAC para su conversi�n.
//
// Autor: Javier Guill�n �lvarez
//---------------------------------------------------------
void DAC_dato(int dato)
{
  static UBYTE primeraVez=1;

  if(!primeraVez){
    while(!QSPI_finTx){}	 	// Espera hasta fin de Tx (SPIF)
  }else{
    primeraVez = 0;
  } 
  
  QSPI_rstSPIF;				// Reset flag de fin de Tx

  QSPI_setBaudRate(DAC_BAUD_RATE);	// Master,16bits,DAC_QMR_BAUD Hz,CPOL=0,CPHA=0	
  
  DAC_escribeTxRAM(dato & MASCARA_DATO);	// Escribe en TX_RAM el dato que convertir� el DAC
  DAC_escribeCommandRAM();		// Escribe en COMMAND_RAM los comandos del QSPI

  QSPI_setENDQP(1);			// Hace que el puntero ENDQP del QSPI apunte al 
					// primer comando de COMMAND_RAM 
  QSPI_activaTx; 			// Activa la Tx 
   
}
