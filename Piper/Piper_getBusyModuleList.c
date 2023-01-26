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
plcbit Piper_getBusyModuleList(Piper_typ* Piper, UDINT pModuleArray, UDINT arraySize, UDINT offset)
{	
	Module_Interface_typ * Module;
	Module_Interface_typ * moduleArray = (Module_Interface_typ *) pModuleArray;
	
	int currentPipe = 0;
	int busyModuleIndex = 0;
	
	//Clear Busy Module Array
	memset(moduleArray,0,sizeof(moduleArray[0])*arraySize);

	//Go through all the modules
	while (currentPipe <= MAI_PIPER_MODULES && Piper->Internal.ModuleList[currentPipe] != 0)
	{
		//Get the pipe at current index
		Module = (Module_Interface_typ *)(Piper->Internal.ModuleList[currentPipe]);
		
		//Check if the Pipe should respond in the current step And if any pipe from this step is not done
				if(Module->ModuleSubStateRequest <= Piper->OUT.SubState
					&& !Module->ModuleBypass
					&& Piper->OUT.State != Module->ModuleResponse
					&& busyModuleIndex < arraySize){									
					
					// Copy the entire module to the next available moduleArray index
					memcpy(&moduleArray[busyModuleIndex],Module,sizeof(moduleArray[0]));
					busyModuleIndex+=1;
				}
		
		currentPipe+=1;
	}
		
	return 0;
}
