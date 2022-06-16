(********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: Piper.fun
 * Author: Josh
 * Created: October 02, 2013
 ********************************************************************
 * Functions and function blocks of library Piper
 ********************************************************************)

FUNCTION Piper_fn_Cyclic : BOOL (*Master Cyclic function*) (*$GROUP=User*)
	VAR_INPUT
		Piper : Piper_typ;
		IsRemote : BOOL;
	END_VAR
END_FUNCTION

FUNCTION_BLOCK Piper_Module_Fub (*Implements the interface to a pipe*) (*$GROUP=User*)
	VAR_INPUT
		Piper : REFERENCE TO Piper_typ;
		ModuleInterface : REFERENCE TO Module_Interface_typ;
	END_VAR
	VAR
		internal : Piper_Module_Internal_typ;
	END_VAR
END_FUNCTION_BLOCK
(*
Internal Piper Functions
*)

FUNCTION Piper_changeState : BOOL (*Logs a state change.*) (*$GROUP=User*)
	VAR_INPUT
		Piper : Piper_typ;
		State : MACH_ST_enum;
	END_VAR
END_FUNCTION

FUNCTION Piper_checkResponses : BOOL (*Reads the status of Pipes*) (*$GROUP=User*)
	VAR_INPUT
		Piper : Piper_typ;
	END_VAR
END_FUNCTION

FUNCTION Piper_getState_remote : BOOL (*Gets state and substate from main Piper*) (*$GROUP=User*)
	VAR_INPUT
		Piper : Piper_typ;
	END_VAR
END_FUNCTION

FUNCTION Piper_handleResponseState : BOOL (*This function looks at the response state and decides what Step or State to enter next*) (*$GROUP=User*)
	VAR_INPUT
		Piper : Piper_typ;
	END_VAR
END_FUNCTION

FUNCTION Piper_handleResponseState_remote : BOOL (*This function looks at the response state and decides what Step or State to request next*) (*$GROUP=User*)
	VAR_INPUT
		Piper : Piper_typ;
	END_VAR
END_FUNCTION

FUNCTION Piper_PackML : BOOL (*Implements PackML state machine for Piper*) (*$GROUP=User*)
	VAR_INPUT
		Piper : Piper_typ;
	END_VAR
END_FUNCTION

FUNCTION Piper_setCommand : BOOL (*Sets commands to the subsystems*) (*$GROUP=User*)
	VAR_INPUT
		Piper : Piper_typ;
	END_VAR
END_FUNCTION
(*
Internal Helper Functions
*)

FUNCTION PackMLStateString : BOOL (*Returns a string for the given PackML state*) (*$GROUP=User*)
	VAR_INPUT
		State : MACH_ST_enum;
		String : STRING[80];
	END_VAR
END_FUNCTION

FUNCTION PiperModuleDoneWithState : BOOL
	VAR_INPUT
		ModuleInterface : Module_Interface_typ;
	END_VAR
END_FUNCTION

FUNCTION PiperModuleDoneWithSubstate : BOOL
	VAR_INPUT
		ModuleInterface : Module_Interface_typ;
	END_VAR
END_FUNCTION
