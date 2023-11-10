/*
* File: Piper_PackML.c
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

/* Implements PackML state machine for Piper */
plcbit Piper_PackML(struct Piper_typ* Piper)
{

	
	switch (Piper->OUT.State)
	{

		case MACH_ST_NOT_READY:
			
			logInfo(Piper->IN.CFG.LoggerName,0,"Boot",0);
			PiperStateChange(Piper,MACH_ST_BOOTING);

			break;
		
		
		case MACH_ST_BOOTING:
			
			/****************************/
			/* Check for State Complete	*/
			/****************************/

			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
				
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);
					
				PiperStateChange(Piper,MACH_ST_BOOTED);
			
			}
			
			break;
		
		case MACH_ST_BOOTED:

			/****************************/
			/* Check for State Complete	*/
			/****************************/
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){

				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);
				
				PiperStateChange(Piper,MACH_ST_STOPPED);
			

		
			}
		
			break;
		
		/************************************************************/
		/* STOP states												*/
		/************************************************************/
		
		case MACH_ST_STOPPING:
				
			/****************************/
			/* Check for State Complete	*/
			/****************************/
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
				
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);
				
				PiperStateChange(Piper,MACH_ST_STOPPED);
				
			}
		
			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  				
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);
			
				PiperStateChange(Piper,MACH_ST_ABORTING);		
		
			}
		
			break;
		
		case MACH_ST_STOPPED:
		
			/****************************/
			/* Wait for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){

				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);
				
				PiperStateChange(Piper,MACH_ST_ABORTING);
				
			}	
			else if( Piper->IN.CMD.Reset ){
  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Reset",0);

				PiperStateChange(Piper,MACH_ST_RESETTING);
				
			}
		
			break;

		/************************************************************/
		/* IDLE states												*/
		/************************************************************/

		case MACH_ST_RESETTING:	
		
			/****************************/
			/* Check for State Complete	*/
			/****************************/
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE )	{
								
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);

				PiperStateChange(Piper,MACH_ST_IDLE);				
			
			}
	
			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){

				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);
			
				PiperStateChange(Piper,MACH_ST_ABORTING);	

			}
			else if( Piper->IN.CMD.Stop ){
  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);
  						
				PiperStateChange(Piper,MACH_ST_STOPPING);			

			}
			break;

		case MACH_ST_IDLE:	

			/****************************/
			/* Wait for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){

				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);
				
				PiperStateChange(Piper,MACH_ST_ABORTING);
				
			}
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);

			}
			else if( Piper->IN.CMD.Start ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Start",0);

				PiperStateChange(Piper,MACH_ST_STARTING);			
			}
						
			break;
		
		/************************************************************/
		/* EXECUTE states											*/
		/************************************************************/

		case MACH_ST_STARTING:
			
			/****************************/
			/* Check for State Complete	*/
			/****************************/
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
								
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);

				PiperStateChange(Piper,MACH_ST_EXECUTE);			

			}

		
			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
			
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);
			
			}
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);			
			
			}
		
			break;
 
		case MACH_ST_EXECUTE:
	
	
			/****************************/
			/* Check for State Complete	*/
			/****************************/
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
								
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);

				PiperStateChange(Piper,MACH_ST_COMPLETING);			

			}
		
			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  		
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);
			
			}
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);

			}
			else if( Piper->IN.CMD.Hold ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Hold",0);
  			
				PiperStateChange(Piper,MACH_ST_HOLDING);

			}
			else if( Piper->IN.CMD.Suspend ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Suspend",0);
  			
				PiperStateChange(Piper,MACH_ST_SUSPENDING);
			
			}	

			break;
		
		case MACH_ST_COMPLETING:
			
			/****************************/
			/* Check for State Complete	*/
			/****************************/
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
									
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);

				PiperStateChange(Piper,MACH_ST_COMPLETE);
			
			}

			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  		
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);	
			

			}
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);
			
			}
	
			break;
			
		case MACH_ST_COMPLETE:
		
			/****************************/
			/* Wait for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  		
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);
				
				
			}
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);
				
			}
			else if( Piper->IN.CMD.Reset ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Reset",0);
  			
				PiperStateChange(Piper,MACH_ST_RESETTING);
			
			}


			/************************************************************/
			/* HOLD states												*/
			/************************************************************/

			break;
			
		case MACH_ST_HOLDING:
			
			/****************************/
			/* Check for State Complete	*/
			/****************************/
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
								
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);

				PiperStateChange(Piper,MACH_ST_HELD);
			
			}

			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  			
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);

			}	
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);
			
			}
	
			break;	
		
		case MACH_ST_HELD:
			
			/****************************/
			/* Wait for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  		
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);
				
			}
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);

			}
			else if( Piper->IN.CMD.Unhold ){
  			  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Unhold",0);
				
				PiperStateChange(Piper,MACH_ST_UNHOLDING);
			
			}
	
			break;
		
		case MACH_ST_UNHOLDING:
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
								
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);
	
				PiperStateChange(Piper,MACH_ST_EXECUTE);
			
			}
		
			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  		
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);		
			
			}		
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);
			
			}
	
	
			/************************************************************/
			/* SUSPEND states											*/
			/************************************************************/
			break;
			
		case MACH_ST_SUSPENDING:
			
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
								
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);

				PiperStateChange(Piper,MACH_ST_SUSPENDED);
			
			}

		
			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  		
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);		
			}		
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);
			
			}
	
			break;	

		case MACH_ST_SUSPENDED:

			/****************************/
			/* Wait for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  		
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);
				
			}
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);
			}
			else if( Piper->IN.CMD.Unsuspend ){
  			  			  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Unsuspend",0);

				PiperStateChange(Piper,MACH_ST_UNSUSPENDING);
			
			}
	
			break;
		
		case MACH_ST_UNSUSPENDING:

			/****************************/
			/* Check for State Complete	*/
			/****************************/
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
									
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);

				PiperStateChange(Piper,MACH_ST_EXECUTE);
			
			}

			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  		
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);
			
			}
			else if( Piper->IN.CMD.Stop ){
  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Stop",0);

				PiperStateChange(Piper,MACH_ST_STOPPING);
			
			}
	
			break;
		
		/************************************************************/
		/* ABORT states												*/
		/************************************************************/

		case MACH_ST_ABORTING:
			
			/****************************/
			/* Check for State Complete	*/
			/****************************/
		
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
					
				logInfo(Piper->IN.CFG.LoggerName,0,"State completed",0);

				PiperStateChange(Piper,MACH_ST_ABORTED);				
			
			}

		
			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			/* No CMDs possible in MACH_ST_ABORTING */
		
			break;

		case MACH_ST_ABORTED:
					
			/****************************/
			/* Wait for Machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Clear ){
  			  			  			  							
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Clear",0);
  			
				PiperStateChange(Piper,MACH_ST_CLEARING);			

			}			

			break;
			
		case MACH_ST_CLEARING:
			
			Piper->IN.CMD.AcknowledgeError=1;
					
			if( Piper->Internal.ResponseStatus == PIPER_RESPONSE_ST_STATE_DONE ){
				
			PiperStateChange(Piper,MACH_ST_STOPPED);			

			}
	
			/****************************/
			/* Check for machine CMDs	*/
			/****************************/
		
			if( Piper->IN.CMD.Abort ){
  		
				logInfo(Piper->IN.CFG.LoggerName,0,"Command Abort",0);

				PiperStateChange(Piper,MACH_ST_ABORTING);			
			
			}
		
			if( Piper->IN.CMD.AcknowledgeError ){
				Piper->IN.CMD.AcknowledgeError=0;
				Piper->OUT.Error=0;		
				memset(Piper->OUT.ErrorString,0,sizeof(Piper->OUT.ErrorString));
			}
			break;
		
		//Remove warnings. These aren't actual states but they are used for communications.
		case MACH_ST_ERROR:				
		case MACH_ST_BYPASSED:				
		case MACH_ST_:
			break;
	}
	/* Reset unseen Machine CMDs */
	memset( &(Piper->IN.CMD), 0, sizeof(Piper->IN.CMD) );
	
	
	return 0;
	
}
