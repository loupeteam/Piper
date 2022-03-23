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
	
	// Set Piper variables based on IO
	if( Piper->IO.iMainInterface.PiperState != Piper->OUT.State ){
		PiperStateChange(Piper, Piper->IO.iMainInterface.PiperState);
		// Update output to be consistent with new state
		memcpy(&Piper->IO.oMainInterface, &Piper->IO.iMainInterface, sizeof(Piper->IO.oMainInterface));
	}else if( Piper->IO.iMainInterface.PiperSubState != Piper->OUT.SubState ){
		Piper->OUT.SubState = Piper->IO.iMainInterface.PiperSubState;
		// Update output to be consistent with new substate
		memcpy(&Piper->IO.oMainInterface, &Piper->IO.iMainInterface, sizeof(Piper->IO.oMainInterface));
	}
	
	// Always update certain variables
	memcpy(&Piper->IO.oMainInterface.ModuleName, &Piper->IO.iMainInterface.ModuleName, sizeof(Piper->IO.oMainInterface.ModuleName));
	memcpy(&Piper->IO.oMainInterface.ModuleCommand, &Piper->IO.iMainInterface.ModuleCommand, sizeof(Piper->IO.oMainInterface.ModuleCommand));
	memcpy(&Piper->IO.oMainInterface.ModuleBypass, &Piper->IO.iMainInterface.ModuleBypass, sizeof(Piper->IO.oMainInterface.ModuleBypass));
	memcpy(&Piper->IO.oMainInterface.ModuleIsBypassed, &Piper->IO.iMainInterface.ModuleIsBypassed, sizeof(Piper->IO.oMainInterface.ModuleIsBypassed));
	
	return 0;
	
}
