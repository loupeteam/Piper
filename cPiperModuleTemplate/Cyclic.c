/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: cPiperModuleTemplate
 * File: cPiperModuleTemplateCyclic.c
 * Author: dfblackburn
 * Created: April 06, 2016
 ********************************************************************
 * Implementation of program cPiperModuleTemplate
 ********************************************************************/

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// Function prototype for piper interface
void PiperModuleInterface();

void _CYCLIC ProgramCyclic(void)
{
	
	// Call PiperModuleInterface to interface with the rest of the machine
	PiperModuleInterface();
	
	//Put your code here

}
