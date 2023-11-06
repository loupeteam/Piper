/********************************************************************
* File: Cyclic.c
* Copyright (c) 2023 Loupe
* https://loupe.team
* 
* This file is part of cPiperModuleTemplate, licensed under the MIT License.
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
