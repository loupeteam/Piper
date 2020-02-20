/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: ServoProg
 * File: PiperModuleInterface.c
 * Author: dfblackburn
 * Created: April 01, 2016
 *******************************************************************/

#include <bur/plctypes.h>
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include <string.h>

void PiperModuleInterface() {
	
	// Give this module a name so it is easier to debug
	strcpy(ModuleInterface.ModuleName, "Name");

	// Add a module to the Piper
	Module.ModuleInterface = &ModuleInterface;
	Module.Piper = &gMachine;
	Piper_Module_Fub(&Module);

	// Handle any machine states that this module needs to respond to
	switch (ModuleInterface.PiperState) {
		
		//case MACH_ST_BOOTING:
		//case MACH_ST_STOPPED:
		//case MACH_ST_RESETTING:
		//case MACH_ST_IDLE:
		//case MACH_ST_STARTING:
		//case MACH_ST_EXECUTE:
		//case MACH_ST_COMPLETING:
		//case MACH_ST_COMPLETE:
		//case MACH_ST_HOLDING:
		//case MACH_ST_HELD:
		//case MACH_ST_UNHOLDING:
		//case MACH_ST_SUSPENDING:
		//case MACH_ST_SUSPENDED:
		//case MACH_ST_UNSUSPENDING:			
		//case MACH_ST_STOPPING:
		//case MACH_ST_ABORTING:
		//case MACH_ST_ABORTED:
		//case MACH_ST_CLEARING:
									
		case MACH_ST_BYPASSED: break;
									
		default: ModuleInterface.ModuleResponse = ModuleInterface.PiperState;
		
	} // switch(PiperState)
		
} // PiperModuleInterface()
