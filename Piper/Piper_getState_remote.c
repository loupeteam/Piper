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

/* Gets state and substate from main Piper */
plcbit Piper_getState_remote(struct Piper_typ* Piper)
{
	if( Piper->MainInterface.PiperState != Piper->OUT.State ){
		PiperStateChange(Piper, Piper->MainInterface.PiperState);
	}else if( Piper->MainInterface.PiperSubState != Piper->OUT.SubState ){
		Piper->OUT.SubState = Piper->MainInterface.PiperSubState;
	}
	
	// Reset unseen Machine CMDs; here, mostly for BypassAll, as others are generally unused
	memset( &(Piper->IN.CMD), 0, sizeof(Piper->IN.CMD) );
	
	return 0;
	
}