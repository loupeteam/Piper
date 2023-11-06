(********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Program: MachineProg
 * File: MachineProgCyclic.st
 * Author: David Blackburn
 * Created: November 10, 2011
 ********************************************************************
 * Implementation of program MachineProg
 ********************************************************************)


(********************************************************************)
(*																	*)
(* This program provides a framework for top level machine control.	*)
(*	This program should accept top level commands (Start, 			*)
(*	Stop, etc.)	and interact with lower level control objects, 		*)
(*	issuing	commands and checking status information.				*)
(*																	*)
(* The state machine and commands are PackML compliant.				*)
(*																	*)
(********************************************************************)

PROGRAM _INIT


END_PROGRAM

PROGRAM _CYCLIC


	//Piper controls the main machine state
	Piper_fn_Cyclic( gMachine );


	
	//Handle anything that needs to happen at the machine level for a given state
	CASE gMachine.OUT.State OF
		
		MACH_ST_BOOTING:
			StateString:= 'Booting';
			TON_0.IN:=	1;
		
		MACH_ST_BOOTED:
			StateString:= 'Booted';
			IF TON_0.IN THEN
				TON_0.IN:=	0;
				IF BootTime = 0 THEN
					BootTime:= TON_0.ET;
				END_IF				
				BootTime:= 	(TON_0.ET+(BootTime*9))/10;
			END_IF
		MACH_ST_NOT_READY :StateString:= 'MACH_ST_NOT_READY';
		MACH_ST_ERROR	  :StateString:= 'MACH_ST_ERROR	;  ';
		MACH_ST_CLEARING  :StateString:= 'MACH_ST_CLEARING ';
		MACH_ST_STOPPED	  :StateString:= 'MACH_ST_STOPPED  ';
		MACH_ST_STARTING  :StateString:= 'MACH_ST_STARTING ';
		MACH_ST_IDLE	  :StateString:= 'MACH_ST_IDLE     ';
		MACH_ST_SUSPENDED :StateString:= 'MACH_ST_SUSPENDED';
		MACH_ST_EXECUTE	  :StateString:= 'MACH_ST_EXECUTE  ';
		MACH_ST_STOPPING  :StateString:= 'MACH_ST_STOPPING ';
		MACH_ST_ABORTING  :StateString:= 'MACH_ST_ABORTING ';
		MACH_ST_ABORTED	  :StateString:= 'MACH_ST_ABORTED  ';
		MACH_ST_HOLDING	  :StateString:= 'MACH_ST_HOLDING  ';
		MACH_ST_HELD	  :StateString:= 'MACH_ST_HELD     ';
		MACH_ST_UNHOLDING :StateString:= 'MACH_ST_UNHOLDING';
		MACH_ST_SUSPENDING:StateString:= 'MACH_ST_SUSPENDING';
		MACH_ST_UNSUSPENDING:StateString:= 'MACH_ST_UNSUSPENDING';
		MACH_ST_RESETTING :StateString:= 'MACH_ST_RESETTING';
		MACH_ST_COMPLETING:StateString:= 'MACH_ST_COMPLETING';
		MACH_ST_COMPLETE  :StateString:= 'MACH_ST_COMPLETE ';
		MACH_ST_BYPASSED  :StateString:= 'MACH_ST_BYPASSED ';
		MACH_ST_		  :StateString:= 'MACH_ST_	       ';
	END_CASE	

	CASE gMachine.OUT.State OF		
		MACH_ST_STARTING,
		MACH_ST_EXECUTE,
		MACH_ST_HELD,
		MACH_ST_UNHOLDING,
		MACH_ST_SUSPENDING,
		MACH_ST_UNSUSPENDING,
		MACH_ST_HOLDING,
		MACH_ST_COMPLETING,
		MACH_ST_COMPLETE:
			//Mode change not allowed			
			gRequestedMode:=gActiveMode;
		ELSE
			gActiveMode:=gRequestedMode;
	END_CASE	
	
	TON_0.PT:=T#1d;	
	TON_0();	
	
	
	
	//**************************************************************************//
	//Display the first module the Piper is waiting on							//
	//**************************************************************************//
	IF gMachine.OUT.BusyModule = 0 THEN
		StatusModule.ModuleName:=	'Ready';
		Module ACCESS ADR(StatusModule);
	ELSE
		Module ACCESS gMachine.OUT.BusyModule;	
		StatusModule:= Module;
	END_IF;
	
	
	
	
END_PROGRAM
