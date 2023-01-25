(********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: Piper.typ
 * Author: Josh
 * Created: October 02, 2013
 ********************************************************************
 * Data types of library Piper
 ********************************************************************)

TYPE
	Piper_typ : 	STRUCT 
		IN : Piper_IN_typ;
		OUT : Piper_OUT_typ;
		Internal : Piper_Internal_typ;
	END_STRUCT;
	Piper_IN_typ : 	STRUCT 
		CMD : Piper_IN_CMD_typ;
		CFG : Piper_IN_CFG_typ;
	END_STRUCT;
	Piper_IN_CFG_typ : 	STRUCT 
		BootCycles : UINT := PIPER_DEFAULT_BOOTING_CYCLES;
		LoggerName : STRING[LOG_STRLEN_LOGGERNAME];
	END_STRUCT;
	Piper_IN_CMD_typ : 	STRUCT 
		Reset : BOOL;
		Start : BOOL;
		Stop : BOOL;
		Hold : BOOL;
		Unhold : BOOL;
		Suspend : BOOL;
		Unsuspend : BOOL;
		Abort : BOOL;
		Clear : BOOL;
		BypassAll : BOOL;
		AcknowledgeError : BOOL;
	END_STRUCT;
	Piper_OUT_typ : 	STRUCT 
		Error : UINT;
		ErrorString : STRING[80];
		State : MACH_ST_enum; (*The current PackML state of system*)
		SubState : DINT; (*The current step within the PackML state*)
		BusyModule : UDINT; (*The first module that is busy*)
		ErrorModule : UDINT; (*The first module that has an error*)
		SubStateRequestModule : UDINT; (*The module that requested the next step*)
	END_STRUCT;
	Piper_Internal_typ : 	STRUCT 
		NextSubState : DINT; (*The next step that should be executed when the current step is complete*)
		ResponseStatus : PIPER_RESPONSE_ST; (*The state of the response of the current step*)
		ModuleList : ARRAY[0..MAI_PIPER_MODULES]OF UDINT; (*The pipes that are attached to this manager*)
		ModuleNames : ARRAY[0..MAI_PIPER_MODULES]OF STRING[80]; (*Names of the modules to ensure uniqueness after download*)
		NumberModules : DINT;
		BootCycles : UINT;
	END_STRUCT;
	Module_Interface_typ : 	STRUCT 
		ModuleName : STRING[80];
		ModuleStatus : STRING[80];
		PiperState : MACH_ST_enum;
		PiperSubState : DINT;
		ModuleResponse : MACH_ST_enum;
		ModuleSubStateRequest : DINT;
		ModuleBypass : BOOL;
		ModuleIsBypassed : BOOL;
	END_STRUCT;
	Piper_Module_Internal_typ : 	STRUCT 
		Added : BOOL;
		ModuleIndex : UDINT;
	END_STRUCT;
	PIPER_RESPONSE_ST : 
		(
		PIPER_RESPONSE_ST_NONE,
		PIPER_RESPONSE_ST_ERROR,
		PIPER_RESPONSE_ST_STEP_DONE,
		PIPER_RESPONSE_ST_NEXT_STEP,
		PIPER_RESPONSE_ST_STATE_DONE,
		PIPER_RESPONSE_ST_BUSY
		);
	MACH_ST_enum : 
		(
		MACH_ST_NOT_READY := 0, (*0*)
		MACH_ST_BOOTING := 1, (*1*)
		MACH_ST_BOOTED,
		MACH_ST_ERROR,
		MACH_ST_CLEARING,
		MACH_ST_STOPPED, (*5*)
		MACH_ST_STARTING,
		MACH_ST_IDLE,
		MACH_ST_SUSPENDED,
		MACH_ST_EXECUTE,
		MACH_ST_STOPPING, (*10*)
		MACH_ST_ABORTING,
		MACH_ST_ABORTED,
		MACH_ST_HOLDING,
		MACH_ST_HELD,
		MACH_ST_UNHOLDING, (*15*)
		MACH_ST_SUSPENDING,
		MACH_ST_UNSUSPENDING,
		MACH_ST_RESETTING,
		MACH_ST_COMPLETING,
		MACH_ST_COMPLETE, (*20*)
		MACH_ST_BYPASSED,
		MACH_ST_ (*22*)
		);
END_TYPE
