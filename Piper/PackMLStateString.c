/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: PackMLStateString.c
 * Author: Josh
 * Created: October 08, 2013
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


#define CASE(x) case x: strcpy(String,#x);

/* Returns a string for the given PackML state */
plcbit PackMLStateString(enum MACH_ST_enum State, plcstring* String)
{
	switch(State){		
		CASE(MACH_ST_) break;
		CASE(MACH_ST_ABORTED) break;
		CASE(MACH_ST_ABORTING) break;
		CASE(MACH_ST_BOOTED) break;
		CASE(MACH_ST_BOOTING) break;
		CASE(MACH_ST_CLEARING) break;
		CASE(MACH_ST_COMPLETE) break;
		CASE(MACH_ST_COMPLETING) break;
		CASE(MACH_ST_ERROR) break;
		CASE(MACH_ST_EXECUTE) break;
		CASE(MACH_ST_HELD) break;
		CASE(MACH_ST_HOLDING) break;
		CASE(MACH_ST_IDLE) break;
		CASE(MACH_ST_RESETTING) break;
		CASE(MACH_ST_STARTING) break;
		CASE(MACH_ST_STOPPED) break;
		CASE(MACH_ST_STOPPING) break;
		CASE(MACH_ST_SUSPENDED) break;
		CASE(MACH_ST_SUSPENDING) break;
		CASE(MACH_ST_NOT_READY) break;
		CASE(MACH_ST_UNHOLDING) break;
		CASE(MACH_ST_UNSUSPENDING) break;
		default:
			brsitoa(State,(UDINT)String);
			break;
	}
	return 0;
}
