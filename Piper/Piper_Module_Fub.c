/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: Pipe_fn_cyclic.c
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

/* Implements the interface to a pipe */
void Piper_Module_Fub(struct Piper_Module_Fub* inst)
{
	BRSE_ARL_Arguments_typ LogData;
	plcstring ModuleName[80];
	USINT TaskGroup;
	USINT ModuleIndex;
	
	if( inst->Piper == 0 || inst->ModuleInterface == 0 ){
		return;		
	}
	
	//If the module has not been added, check if the memory was reinited, and fix it, or add a new module
	if( !inst->internal.Added ){

		//Get the full module name with the task it is contained in
		ST_name(0,ModuleName,& TaskGroup);		
		strcat(ModuleName,":");		
		strcat(ModuleName,inst->ModuleInterface->ModuleName);
				
		//Check all the added modules, and see if this module has already been added.
		//If it has, lets just updated that entry
		for( ModuleIndex=0;ModuleIndex<=MAI_PIPER_MODULES; ModuleIndex++ )
		{
			if(inst->Piper->Internal.ModuleList[ModuleIndex] == 0  ){
				break;			
			}
			if( strcmp(inst->Piper->Internal.ModuleNames[ModuleIndex] , ModuleName) == 0 ){
				//Get information from module to log it
				inst->internal.ModuleIndex= ModuleIndex;

				//update the module information
				strcpy(inst->Piper->Internal.ModuleNames[inst->internal.ModuleIndex],ModuleName);
				inst->Piper->Internal.ModuleList[inst->internal.ModuleIndex] = (UDINT)inst->ModuleInterface;
				inst->internal.Added=				1;

				//Log what we did
				LogData.s[0] = (UDINT)&inst->ModuleInterface->ModuleName;	
				LogData.i[0] = inst->internal.ModuleIndex;				
				logWarning(inst->Piper->IN.CFG.LoggerName,0,"Module was reinitialized at index %i: %s",(UDINT)&LogData);

				return;
			}			
		}

		//This is an all new module, added for the first time.

		//Get a new slot
		inst->internal.ModuleIndex= inst->Piper->Internal.NumberModules;
		inst->Piper->Internal.NumberModules+=	1;	

		//update the module information
		strcpy(inst->Piper->Internal.ModuleNames[inst->internal.ModuleIndex],ModuleName);
		inst->Piper->Internal.ModuleList[inst->internal.ModuleIndex] = (UDINT)inst->ModuleInterface;
		inst->internal.Added=				1;

		//Log what we did
		LogData.s[0] = (UDINT)&inst->ModuleInterface->ModuleName;	
		LogData.i[0] = inst->internal.ModuleIndex;				
		if( inst->Piper->OUT.State > MACH_ST_BOOTING ){
			logWarning(inst->Piper->IN.CFG.LoggerName,0,"New module added after BOOTING at index %i: %s",(UDINT)&LogData);			
		}else{
			logInfo(inst->Piper->IN.CFG.LoggerName,0,"New module added at index %i: %s",(UDINT)&LogData);		
		}

	}
	//Detect if this module is still in the index that it thought it was. If this module is not in the slot that it thinks it was,
	//that means that this memory moved. 	
	else if(inst->Piper->Internal.ModuleList[inst->internal.ModuleIndex] != (UDINT)inst->ModuleInterface){

		//Get the full module name with the task it is contained in
		ST_name(0,ModuleName,& TaskGroup);		
		strcat(ModuleName,":");		
		strcat(ModuleName,inst->ModuleInterface->ModuleName);

		//update the module information
		strcpy(inst->Piper->Internal.ModuleNames[inst->internal.ModuleIndex],ModuleName);
		inst->Piper->Internal.ModuleList[inst->internal.ModuleIndex] = (UDINT)inst->ModuleInterface;
		inst->internal.Added=				1;

		//Log what we did
		LogData.s[0] = (UDINT)&inst->ModuleInterface->ModuleName;	
		LogData.i[0] = inst->internal.ModuleIndex;				
		logWarning(inst->Piper->IN.CFG.LoggerName,0,"Module memory was moved at index %i: %s",(UDINT)&LogData);
	
	}

}
