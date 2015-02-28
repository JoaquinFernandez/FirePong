	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#ifndef __DAC_H__
	#define __DAC_H__

    	#define QSPI_QMR_INIT 0x8000		// Valor de inicio del registro QMR del QSPI
   	#define QDLYR_SPE_MASK 0x8000		// Máscara para activar la Tx del DAC y el ADC
   	#define QIR_SPIF_MASK 0x0001		// Máscara para leer el flag de fin de Tx
  	#define MASCARA_DATO 0xFFF          // Máscara para escribir el dato en en el QSPI
   	#define MASCARA_QDR 0x4D00          // Máscara para escribit en el QDR
  	#define MASCARA_INT 0x8000          // Máscara para desactivar interr QSPI
  	#define MASCARA_PUERTOA 0x00800000  // Máscara para puerto A como Puerto IO y QSPI_CS1
  	#define MASCARA_RETARDO 0x0000      // Máscara para retardos inicial y final por defecto, QSPI deshabilitado
  	#define MASCARA_SPIF 0xD00D		    // Máscara para SPIF sin interrupciones y borrar SPIF
    
   	//--------------------------------------------------------------
   	//     RUTINAS DE CONFIGURACIÓN Y MANEJO DEL DAC Y DEL ADC
   	//--------------------------------------------------------------
  
    	// MACRO: QSPI_setBaudRate(baudios) - Fija la velocidad de Tx del QSPI
    	#define QSPI_setBaudRate(baudios) 	mbar_writeShort(MCFSIM_QMR, QSPI_QMR_INIT | MCF_CLK/(2*baudios))

    	// MACRO: QSPI_setENDQP - Hace que ENDQP apunte al último comando de COMMAND_RAM a transmitir
    	#define QSPI_setENDQP(numComandos)	mbar_writeShort(MCFSIM_QWR, 0x1000 | ((numComandos - 1) << 8))

    	// MACRO: QSPI_activaTx - Inicia la Tx del QSPI
    	#define QSPI_activaTx 	mbar_writeShort(MCFSIM_QDLYR, mbar_readShort(MCFSIM_QDLYR)|QDLYR_SPE_MASK)

    	// MACRO: QSPI_rstSPIF - Borra el flag de fin de Tx del QSPI
    	#define QSPI_rstSPIF 	mbar_writeShort(MCFSIM_QIR, mbar_readShort(MCFSIM_QIR)|QIR_SPIF_MASK)

    	// MACRO: QSPI_finTx - Devuelve '1' cuando ha terminado la transmisión del QSPI
    	#define QSPI_finTx 	(mbar_readShort(MCFSIM_QIR) & QIR_SPIF_MASK)

	/*******************************************/
	/*                 Funciones               */
	/*******************************************/

	//Manda un dato al DAC
	void DAC_dato(int dato);
	//Inicializa el DAC
	void DAC_ADC_init();

	#endif
