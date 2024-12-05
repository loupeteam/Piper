/*
* File: Piper_checkResponses.c
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
#include "string.h"

#ifdef __cplusplus
	};
#endif

// Reads the status of Pipes
plcbit Piper_checkResponses(struct Piper_typ* Piper) {	
	struct Module_Interface_typ * Module;
	StrExtArgs_typ LogData;
	
	int currentPipe = 0;
	
	Piper->OUT.BusyModule = 0;
	Piper->OUT.ErrorModule = 0;
	Piper->OUT.SubStateRequestModule = 0;
	Piper->Internal.NextSubState = 0;
	
	// Initialize to finished. Will get reset if not
	Piper->Internal.ResponseStatus = PIPER_RESPONSE_ST_STEP_DONE;
	
	
	// Handle special booting case. We stay in booting for a minimum number of cycles.
	if (Piper->OUT.State == MACH_ST_BOOTING) {
		Piper->Internal.BootCycles += 1;
		
		// Hold Piper in BOOTING and substate 0 for configured boot cycles
		if (Piper->Internal.BootCycles < Piper->IN.CFG.BootCycles) {
			Piper->Internal.ResponseStatus = PIPER_RESPONSE_ST_BUSY;
		}
	}
	
	// Go through all the modules and check status
	while ((currentPipe <= MAI_PIPER_MODULES) && (Piper->Internal.ModuleList[currentPipe] != 0)) {
		// Get the pipe at current index
		Module = (Module_Interface_typ *)(Piper->Internal.ModuleList[currentPipe]);
		
		// Check if the Pipe should respond in the current step
		if ((Module->ModuleSubStateRequest <= Piper->OUT.SubState) && !Module->ModuleBypass) {
			
			// If any pipe from this step is not done remain here by setting busy
			if (Piper->OUT.State != Module->ModuleResponse) {
				
				// Set response status so that Piper doesn't change state
				Piper->Internal.ResponseStatus = PIPER_RESPONSE_ST_BUSY;
				
				// If there is no busy module yet, grab the first one
				if (Piper->OUT.BusyModule == 0) {
					Piper->OUT.BusyModule = (UDINT)Module;
				}
			}
		}
		
		// Figure out if there is a next step that we will need to go to
		else if ((Module->ModuleSubStateRequest > Piper->OUT.SubState) && !Module->ModuleBypass) {
			
			// If we haven't found a response step that is greater than our current step, grab the current pipes response step
			if (Piper->Internal.NextSubState <= Piper->OUT.SubState) {
				Piper->Internal.NextSubState = Module->ModuleSubStateRequest;
				Piper->OUT.SubStateRequestModule = (UDINT)Module;
			}
			
			// If we currently have a response step that is greater than our current step, use the lower one.
			else if (Piper->Internal.NextSubState > Module->ModuleSubStateRequest) {
				Piper->Internal.NextSubState = Module->ModuleSubStateRequest;
				Piper->OUT.SubStateRequestModule = (UDINT)Module;
			}
		}
		
		// Check if there are any commands sent by this module
		if (Module->ModuleCommand.Abort) {
			Piper->IN.CMD.Abort = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested an abort by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.AcknowledgeError) {
			Piper->IN.CMD.AcknowledgeError = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested an acknowledge error by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.BypassAll) {
			Piper->IN.CMD.BypassAll = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested a bypass all by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.Clear) {
			Piper->IN.CMD.Clear = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested a clear by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.Hold) {
			Piper->IN.CMD.Hold = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested a hold by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.Reset) {
			Piper->IN.CMD.Reset = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested a reset by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.Start) {
			Piper->IN.CMD.Start = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested a start by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.Stop) {
			Piper->IN.CMD.Stop = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested a stop by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.Suspend) {
			Piper->IN.CMD.Suspend = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested a suspend by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.Unhold) {
			Piper->IN.CMD.Unhold = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested an unhold by interface command", (UDINT)&LogData);
		}
		
		if (Module->ModuleCommand.Unsuspend) {
			Piper->IN.CMD.Unsuspend = 1;
			LogData.s[0] = (UDINT)&(Module->ModuleName);
			logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested an unsuspend by interface command", (UDINT)&LogData);
		}
		
		// Reset module CMDs
		memset(&Module->ModuleCommand, 0, sizeof(Module->ModuleCommand));
		
		currentPipe++;
	}
	
	currentPipe = 0;
	
	// Check if any module has an error
	while (currentPipe <= MAI_PIPER_MODULES && Piper->Internal.ModuleList[currentPipe] != 0) {
		// Get the pipe at current index
		Module = (Module_Interface_typ *)(Piper->Internal.ModuleList[currentPipe]);
		
		// If there is an error, set the status and log
		if (Module->ModuleResponse == MACH_ST_ERROR && !Module->ModuleBypass) {
			// Reset the response to something to other the Error
//	 		Module->ModuleResponse = MACH_ST_UNDEFINED; (NOT SURE IF I NEED THIS)
			
			// If there is no error module yet, grab the first one
			if (Piper->OUT.ErrorModule == 0) {
				Piper->OUT.ErrorModule = (UDINT)Module;
			}
			// Set response status so we know what to do
			Piper->Internal.ResponseStatus = PIPER_RESPONSE_ST_ERROR;
			
		}
		currentPipe++;
	}
	
	return 0;
}