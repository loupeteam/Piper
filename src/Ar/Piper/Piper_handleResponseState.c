/*
* File: Piper_handleResponseState.c
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

// This function looks at the response state and decides what Step or State to enter next
plcbit Piper_handleResponseState(struct Piper_typ* Piper) {
	
	struct Module_Interface_typ * Module;
	StrExtArgs_typ LogData;
	
	// If we are done with the last step, check if there is another
	switch (Piper->Internal.ResponseStatus)
	{
		case PIPER_RESPONSE_ST_STEP_DONE:
			
			// If the next step is greater than our current step, go to the next step	
			if (Piper->OUT.SubState < Piper->Internal.NextSubState) {
						
				// Grab the next step
				Piper->OUT.SubState = Piper->Internal.NextSubState;
				
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
				Piper->OUT.SubState = IDLE_SUBSTATE;
				Piper->Internal.NextSubState = 0;
			}
			break;
		
		case PIPER_RESPONSE_ST_ERROR:
			
			Piper->IN.CMD.Abort = 1;
			
			// Log the data if we can
			if (Piper->OUT.ErrorModule != 0) {
				Module = (Module_Interface_typ *)Piper->OUT.ErrorModule;
				
				if (Piper->OUT.State != MACH_ST_ABORTING) {
					LogData.s[0] = (UDINT)&Module->ModuleName;
					logInfo(Piper->IN.CFG.LoggerName, 0, "%s requested an abort due to error", (UDINT)&LogData);
				}
			}
			break;
		
		default:
			break;
	}
	
	return 1;
}
