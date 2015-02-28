	/****************************************************************************
	*
	*	PongFire
	*
	*	Autores:
	*           Juan José Carracedo Justo
	*           Joaquín Fernández Moreno
	*
	****************************************************************************/
	#include "puerto.h"

	static UWORD puertoS;

	//-------------------------------------------------------------
	// void set_puertoS_filas (UBYTE valor)
	//
	// Descripción:
	//   Escribe en el byte mas significativo del puerto de salida
	//   el valor indicado
	//
	//-------------------------------------------------------------
	void set_puertoS_filas (UBYTE valor)
	{
	  UWORD* pchar;
	  puertoS &= MASCARA_FILAS;
	  puertoS |= (UWORD) (valor << 8);  
	  pchar = (UWORD*)BASE_PUERTO_S;
	  (*pchar) = puertoS;
	}



	//-------------------------------------------------------------
	// set_puertoS_columnas (UBYTE valor)
	//
	// Descripción:
	//   Escribe en el byte menos significativo del puerto de salida,
	//   solo el valor de los 4 bits mas significativos
	//
	//-------------------------------------------------------------

	void set_puertoS_columnas (UBYTE valor)
	{
	  UWORD* pchar;
	  puertoS &= MASCARA_COLUMNAS;
	  puertoS |= (UWORD) (valor << 4);  
	  pchar = (UWORD*) BASE_PUERTO_S;
	  (*pchar) = puertoS;
	}

	//-------------------------------------------------------------
	// set_puertoS_teclado (UBYTE valor)
	//
	// Descripción:
	//   Escribe en el byte menos significativo del puerto de salida,
	//   solo el valor de los 4 bits menos significativos
	//
	//-------------------------------------------------------------

	void set_puertoS_teclado (UBYTE valor)
	{
	  UWORD* pchar;
	  puertoS &= MASCARA_TECLADO;
	  puertoS |= (UWORD) valor;  
	  pchar = (UWORD*) BASE_PUERTO_S;
	  (*pchar) = puertoS;
	}

	//------------------------------------------
	// UWORD lee16_puertoE (void)
	//
	// Descripción:
	//   Lee los 16 bits del puerto de entrada
	//
	//------------------------------------------
	UWORD lee16_puertoE (void)
	{
	  return *((UWORD*) PUERTO_E_ALTO);
	}

	//-------------------------------------------
	// UBYTE lee_puertoE (void)
	//
	// Descripción:
	//   Lee el byte menos significativo del
	//   puerto de entrada
	//
	//-------------------------------------------
	UBYTE lee_puertoE (void)
	{
	  return  *((UBYTE*) PUERTO_E_BAJO);
	}