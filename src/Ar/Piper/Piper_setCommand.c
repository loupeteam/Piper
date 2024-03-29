/*
* File: Piper_setCommand.c
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

/* Sets commands to the subsystems */
plcbit Piper_setCommand(struct Piper_typ* Piper)
{
	
	struct Module_Interface_typ * Module;
	
	int currentPipe = 0;

	while ( currentPipe <= MAI_PIPER_MODULES && Piper->Internal.ModuleList[currentPipe] != 0 )
	{
		//Get the pipe at current index
		Module =	(Module_Interface_typ *)(Piper->Internal.ModuleList[currentPipe]);
		
		if(!Module->ModuleBypass){
			
			// Not bypassed anymore
			Module->ModuleIsBypassed = 0;

			//If we are changing states, 
			//reset the ModuleSubStateRequest and Module response
			if(Module->PiperState!=Piper->OUT.State){
				Module->ModuleSubStateRequest = 0;
				Module->ModuleResponse = 0;
			}

			//Set the current state
			Module->PiperState=		Piper->OUT.State;
			Module->PiperSubState=	Piper->OUT.SubState;

		} else if (!Module->ModuleIsBypassed) {
		
			//Bypass me!
			Module->PiperState = MACH_ST_BYPASSED;
			Module->PiperSubState = 0;
			Module->ModuleIsBypassed = 1;
		
		}
		
		currentPipe+=1;
				
	}
	
	return 0;

}
