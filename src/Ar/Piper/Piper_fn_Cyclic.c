/*
* File: Piper_fn_Cyclic.c
* Copyright (c) 2023 Loupe
* https://loupe.team
* 
* This file is part of the Piper Library, licensed under the MIT License.
*/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

	#include "Piper.h"

#ifdef __cplusplus
	};
#endif

#include <string.h>

/* Master Cyclic function */
plcbit Piper_fn_Cyclic(struct Piper_typ* Piper)
{
	
	if( Piper == 0 ){
		return 1;
	}	
	
	//Check piper logger name	
	if( strcmp(Piper->IN.CFG.LoggerName, "") == 0 )	{
	strcpy( Piper->IN.CFG.LoggerName, PIPER_DEFAULT_LOGGERNAME);
	}

	int currentPipe = 0;
	if( Piper->IN.CMD.BypassAll ){
		while ( currentPipe <= MAI_PIPER_MODULES && Piper->Internal.ModuleList[currentPipe] != 0 ){
			//Get the pipe at current index
			((Module_Interface_typ *)(Piper->Internal.ModuleList[currentPipe]))->ModuleBypass = 1;
			currentPipe++;
		}
	}
	//Check responses from Pipers
	Piper_checkResponses(Piper);
	Piper_handleResponseState(Piper);

	//////////////////
	//Implement PackML
	//////////////////
	Piper_PackML(Piper);
				
	//Set commands to pipes
	Piper_setCommand(Piper);	
	
	return 0;
	
}
