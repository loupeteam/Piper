/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: Piper_getBusyModuleList.c
 * Author: Liam
 * Created: January 24, 2023
 ********************************************************************
 * Implementation of library Piper
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "Piper.h"

#ifdef __cplusplus
	};
#endif

/* Reads pipes with a busy status */
UINT Piper_getBusyModules(Piper_typ* Piper, UDINT pModuleArray, UINT numModules, UINT offset)
{	
	Module_Interface_typ * Module;
	Module_Interface_typ * moduleArray = (Module_Interface_typ *) pModuleArray;
	
	UINT moduleIndex = 0;
	UINT numBusyModules = 0;
	
	//Clear Busy Module Array
	memset(moduleArray,0,sizeof(moduleArray[0])*numModules);

	//Go through all the modules
	while ( moduleIndex <= MAI_PIPER_MODULES && Piper->Internal.ModuleList[moduleIndex] != 0)
	{
		//Get the pipe at current index
		Module = (Module_Interface_typ *)(Piper->Internal.ModuleList[moduleIndex]);
		
		//Check if the Pipe should respond in the current step And if any pipe from this step is not done
		if(!Module->ModuleBypass
		&& Piper->OUT.State != Module->ModuleResponse){
			
			
			if (numBusyModules >= offset
				&& numBusyModules - offset < numModules){
				// Copy the entire module to the next available moduleArray index
				memcpy(&moduleArray[numBusyModules-offset],Module,sizeof(moduleArray[0]));
			}
			
			numBusyModules+=1;
		}
		
		moduleIndex+=1;
	}
		
	return numBusyModules;
}
