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

/* Master Cyclic function */
plcbit Piper_fn_Cyclic(struct Piper_typ* Piper, BOOL isRemote)
{
	
	if( Piper == 0 ){
		return 1;
	}	
	
	//Check piper logger name	
	if( strcmp(Piper->IN.CFG.LoggerName, "") == 0 )	{
	strcpy( Piper->IN.CFG.LoggerName, PIPER_DEFAULT_LOGGERNAME);
	}

	int currentPipe = 0;
	if( Piper->IN.CMD.BypassAll ){
		while ( currentPipe <= MAI_PIPER_MODULES && Piper->Internal.ModuleList[currentPipe] != 0 ){
			//Get the pipe at current index
			((Module_Interface_typ *)(Piper->Internal.ModuleList[currentPipe]))->ModuleBypass = 1;
			currentPipe++;
		}
	}
	BOOL bootAtDifferentTimes = (Piper->OUT.State == MACH_ST_NOT_READY || Piper->OUT.State == MACH_ST_BOOTING) != (Piper->IO.iMainInterface.PiperState == MACH_ST_NOT_READY || Piper->IO.iMainInterface.PiperState == MACH_ST_BOOTING)
	//If we're remote, act as a remote unless we booted first OR main booted first
	//If both boot at the same time, bootAtDifferentTimes will become True on the cycle that main leaves booting
	//Remote will leave booting during that cycle where it's acting as a main, so it should be fine, just weird.
	if (isRemote && !bootAtDifferentTimes){
		
		//Send state and substate from main Piper to local modules
		Piper_getState_remote(Piper);
		Piper_setCommand(Piper);
		
		//Send responses from local modules to main Piper
		Piper_checkResponses(Piper);
		Piper_handleResponseState_remote(Piper);
		
		//Machine CMDs get reset (conditionally) in handleResponseState_remote
		
	} else {
		
		//Check responses from Pipers
		Piper_checkResponses(Piper);
		Piper_handleResponseState(Piper);
		
		//////////////////
		//Implement PackML
		//////////////////
		Piper_PackML(Piper);
		
		//Set commands to pipes
		Piper_setCommand(Piper);
	
		//Reset unseen Machine CMDs
		memset( &(Piper->IN.CMD), 0, sizeof(Piper->IN.CMD) );
	}
	
	return 0;
	
}
