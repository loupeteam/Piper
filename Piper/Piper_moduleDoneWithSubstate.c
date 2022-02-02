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

plcbit Piper_moduleDoneWithSubstate(Module_Interface_typ *interface) {
	return Piper_moduleDoneWithState(interface)
		|| interface->ModuleSubStateRequest > interface->PiperSubState;
}