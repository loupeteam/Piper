/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: Piper_handleResponseState.c
 * Author: Josh
 * Created: October 03, 2013
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

// This function looks at the response state and decides what Step or State to request next
plcbit Piper_handleResponseState_remote(struct Piper_typ* Piper) {
	
	struct Module_Interface_typ * Module;
	StrExtArgs_typ LogData;
	
	// If we are done with the last step, check if there is another
	switch (Piper->Internal.ResponseStatus) {
		case PIPER_RESPONSE_ST_STEP_DONE:
			
			// If the next step is greater than our current step, request the next step
			if (Piper->OUT.SubState < Piper->Internal.NextSubState) {
				
				// Grab the next step
				Piper->IO.oMainInterface.ModuleSubStateRequest = Piper->Internal.NextSubState;
				
				// Next step is decided in checkResponses
				Piper->Internal.NextSubState = 0;
				
				// Set response status
				Piper->Internal.ResponseStatus = PIPER_RESPONSE_ST_NEXT_STEP;
				
				// Log the data if we can
				if (Piper->OUT.SubStateRequestModule != 0) {
					Module = (Module_Interface_typ *)(Piper->OUT.SubStateRequestModule);
					LogData.i[0] = Piper->OUT.SubState;
					LogData.s[0] = (UDINT)&Module->ModuleName;
					logInfo(Piper->IN.CFG.LoggerName, 0, "Substate %i requested by %s", (UDINT)&LogData);
				}
			}
			// If the next step is not greater than our current step, this state is done
			else {
				
				// We are done with this state
				Piper->Internal.ResponseStatus = PIPER_RESPONSE_ST_STATE_DONE;
				Piper->IO.oMainInterface.ModuleResponse = Piper->OUT.State;
				
				Piper->IO.oMainInterface.ModuleSubStateRequest = 0;
				Piper->Internal.NextSubState =	0;
				
			}
			break;
		
		case PIPER_RESPONSE_ST_ERROR:
			Piper->IO.oMainInterface.ModuleResponse = MACH_ST_ERROR;
			break;
		
		case PIPER_RESPONSE_ST_BUSY:
			Piper->IO.oMainInterface.ModuleResponse = 0;
			break;
		
		default:
			break;
	}
	
	// Reset Machine CMDs that have already been seen
	if (Piper->IO.iMainInterface.ModuleCommand.Abort) {
		Piper->IN.CMD.Abort = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.AcknowledgeError) {
		Piper->IN.CMD.AcknowledgeError = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.BypassAll) {
		Piper->IN.CMD.BypassAll = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.Clear) {
		Piper->IN.CMD.Clear = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.Hold) {
		Piper->IN.CMD.Hold = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.Reset) {
		Piper->IN.CMD.Reset = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.Start) {
		Piper->IN.CMD.Start = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.Stop) {
		Piper->IN.CMD.Stop = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.Suspend) {
		Piper->IN.CMD.Suspend = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.Unhold) {
		Piper->IN.CMD.Unhold = 0;
	}
	if (Piper->IO.iMainInterface.ModuleCommand.Unsuspend) {
		Piper->IN.CMD.Unsuspend = 0;
	}
	
	// Propagate unseen commands to main Piper
	memcpy(&Piper->IO.oMainInterface.ModuleCommand, &Piper->IN.CMD, sizeof(Piper->IO.oMainInterface.ModuleCommand));
	
	return 1;
}
