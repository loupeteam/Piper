/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: Piper_PackML.c
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
#include "string.h"

#ifdef __cplusplus
	};
#endif

// Sets the substate given the current internal response status
plcbit Piper_setSubstate(struct Piper_typ* Piper) {
	if (Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_NEXT_STEP) {
		Piper->OUT.SubState = Piper->Internal.NextSubState;
	}
	else if (Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE) {
		Piper->OUT.SubState = IDLE_SUBSTATE;
	}
	
	return 0;
}
