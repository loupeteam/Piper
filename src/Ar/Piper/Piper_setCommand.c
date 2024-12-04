/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: Piper_setCommand.c
 * Author: Josh
 * Created: October 02, 2013
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

// Sets commands to the subsystems
plcbit Piper_setCommand(struct Piper_typ* Piper) {
	
	struct Module_Interface_typ * Module;
	
	int currentPipe = 0;
	
	while (currentPipe <= MAI_PIPER_MODULES && Piper->Internal.ModuleList[currentPipe] != 0) {
		// Get the pipe at current index
		Module = (Module_Interface_typ *)(Piper->Internal.ModuleList[currentPipe]);
		
		if (!Module->ModuleBypass) {
			
			// Not bypassed anymore
			Module->ModuleIsBypassed = 0;
			
			// If we are changing states,
			// reset the ModuleSubStateRequest and Module response
			if (Module->PiperState != Piper->OUT.State) {
				Module->ModuleSubStateRequest = 0;
				Module->ModuleResponse = 0;
			}
			
			// Set the current state
			Module->PiperState = Piper->OUT.State;
			Module->PiperSubState = Piper->OUT.SubState;
		}
		else if (!Module->ModuleIsBypassed) {
			
			// Bypass me!
			Module->PiperState = MACH_ST_BYPASSED;
			Module->PiperSubState = 0;
			Module->ModuleIsBypassed = 1;
		}
		
		currentPipe+=1;
	}
	
	// Update our oModuleInterface for status reasons
	Module = &Piper->IO.oMainInterface;
	
	// If we are changing states, reset the ModuleSubStateRequest and Module response
	// This only works because oMainInterface.PiperState hasn't been set yet
	if (Module->PiperState != Piper->OUT.State) {
		Module->ModuleSubStateRequest = 0;
		Module->ModuleResponse = 0;
	}
	else {
		// Set the ModuleSubStateRequest and Module response
		switch (Piper->Internal.ResponseStatus) {
			case PIPER_RESPONSE_ST_NEXT_STEP:
				Module->ModuleSubStateRequest = Piper->Internal.NextSubState;
				break;
		
			case PIPER_RESPONSE_ST_STATE_DONE:
				Module->ModuleResponse = Piper->OUT.State;
				Module->ModuleSubStateRequest = 0;
				break;
		
			case PIPER_RESPONSE_ST_ERROR:
				Module->ModuleResponse = MACH_ST_ERROR;
				break;
		
			case PIPER_RESPONSE_ST_BUSY:
				Module->ModuleResponse = MACH_ST_NOT_READY;
				break;
		
			default:
				break;
		}
	}
	
	// Set the current state
	Module->PiperState = Piper->OUT.State;
	Module->PiperSubState = Piper->OUT.SubState;
	
	// Set bypass status
	Module->ModuleBypass = Piper->IO.iMainInterface.ModuleBypass;
	Module->ModuleIsBypassed = Piper->IO.iMainInterface.ModuleIsBypassed;
	
	// Set name and status
	stringlcpy(Module->ModuleName, Piper->IO.iMainInterface.ModuleName, sizeof(Module->ModuleName));
	if (Piper->OUT.BusyModule == 0) {
		strcpy(Module->ModuleStatus, "");
	}
	else {
		stringlcpy(Module->ModuleStatus, ((Module_Interface_typ*)Piper->OUT.BusyModule)->ModuleName, sizeof(Module->ModuleStatus));
		stringlcat(Module->ModuleStatus, ": ", sizeof(Module->ModuleStatus));
		stringlcat(Module->ModuleStatus, ((Module_Interface_typ*)Piper->OUT.BusyModule)->ModuleStatus, sizeof(Module->ModuleStatus));
	}
	
	// Set commands
	Module->ModuleCommand = Piper->IN.CMD;
	
	return 0;
}