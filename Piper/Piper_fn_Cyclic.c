/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: Piper_fn_Cyclic.c
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

#include <string.h>

// Master Cyclic function
plcbit Piper_fn_Cyclic(struct Piper_typ* Piper, BOOL IsRemote) {
	
	if (Piper == 0) {
		return 1;
	}
	
	// Check piper logger name
	if (strcmp(Piper->IN.CFG.LoggerName, "") == 0) {
		strcpy(Piper->IN.CFG.LoggerName, PIPER_DEFAULT_LOGGERNAME);
	}
	
	int currentPipe = 0;
	if (Piper->IN.CMD.BypassAll) {
		while ((currentPipe <= MAI_PIPER_MODULES) && (Piper->Internal.ModuleList[currentPipe] != 0)) {
			// Get the pipe at current index
			((Module_Interface_typ *)(Piper->Internal.ModuleList[currentPipe]))->ModuleBypass = 1;
			currentPipe++;
		}
	}
	BOOL bootAtDifferentTimes = (Piper->OUT.State == MACH_ST_NOT_READY || Piper->OUT.State == MACH_ST_BOOTING) != (Piper->IO.iMainInterface.PiperState == MACH_ST_NOT_READY || Piper->IO.iMainInterface.PiperState == MACH_ST_BOOTING);
	// If we're remote, act as a remote unless we booted first OR main booted first
	// If both boot at the same time, bootAtDifferentTimes will become True on the cycle that main leaves booting
	// Remote will leave booting during that cycle where it's acting as a main, so it should be fine, just weird.
	BOOL actAsRemote = IsRemote && !bootAtDifferentTimes;
	
	// Check responses from Pipers
	Piper_checkResponses(Piper);
	Piper_handleResponseState(Piper);
	
	// Update current state
	if (actAsRemote) {
		// Get state and substate from main Piper
		Piper_getState_remote(Piper);
	}
	else {
		// Set substate and state based on internal status
		Piper_setSubstate(Piper);
		Piper_PackML(Piper);
	}
	
	// Set commands to pipes
	Piper_setCommand(Piper);
	
	// Reset Machine CMDs
	if (actAsRemote) {
		if (Piper->IO.iMainInterface.ModuleCommand.Reset) {
			Piper->IN.CMD.Reset = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.Start) {
			Piper->IN.CMD.Start = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.Stop) {
			Piper->IN.CMD.Stop = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.Hold) {
			Piper->IN.CMD.Hold = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.Unhold) {
			Piper->IN.CMD.Unhold = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.Suspend) {
			Piper->IN.CMD.Suspend = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.Unsuspend) {
			Piper->IN.CMD.Unsuspend = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.Abort) {
			Piper->IN.CMD.Abort = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.Clear) {
			Piper->IN.CMD.Clear = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.BypassAll) {
			Piper->IN.CMD.BypassAll = 0;
		}
		if (Piper->IO.iMainInterface.ModuleCommand.AcknowledgeError) {
			Piper->IN.CMD.AcknowledgeError = 0;
		}
	}
	else {
		memset(&Piper->IN.CMD, 0, sizeof(Piper->IN.CMD));
	}
	
	return 0;
	
}
