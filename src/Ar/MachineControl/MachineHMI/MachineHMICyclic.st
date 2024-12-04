(*
* File: MachineHMICyclic.st
* Copyright (c) 2023 Loupe
* https://loupe.team
* 
* This file is part of MachineHMI, licensed under the MIT License.
*)


PROGRAM _CYCLIC

HMIMachineCMD.Abort.StatusDP.0:= 	1;
HMIMachineCMD.Clear.StatusDP.0:= 	1;
HMIMachineCMD.Hold.StatusDP.0:= 	1;
HMIMachineCMD.Reset.StatusDP.0:= 	1;
HMIMachineCMD.Start.StatusDP.0:= 	1;
HMIMachineCMD.Stop.StatusDP.0:= 	1;
HMIMachineCMD.Suspend.StatusDP.0:= 	1;
HMIMachineCMD.Unhold.StatusDP.0:= 	1;
HMIMachineCMD.Unsuspend.StatusDP.0:= 1;

HMIMachineState.Aborted.ColorDP:=		0;
HMIMachineState.Aborting.ColorDP:=		0;
HMIMachineState.Clearing.ColorDP:=		0;
HMIMachineState.Complete.ColorDP:=		0;
HMIMachineState.Completing.ColorDP:=	0;
HMIMachineState.Execute.ColorDP:=		0;
HMIMachineState.Held.ColorDP:=			0;
HMIMachineState.Holding.ColorDP:=		0;
HMIMachineState.Idle.ColorDP:=			0;
HMIMachineState.Resetting.ColorDP:=		0;
HMIMachineState.Starting.ColorDP:=		0;
HMIMachineState.Stopped.ColorDP:=		0;
HMIMachineState.Stopping.ColorDP:=		0;
HMIMachineState.Suspended.ColorDP:=		0;
HMIMachineState.Suspending.ColorDP:=	0;
HMIMachineState.UnHolding.ColorDP:=		0;
HMIMachineState.UnSuspending.ColorDP:=	0;


		
(********************************************)
(* Main state machine						*)
(********************************************)


CASE gMachine.OUT.State OF
	

(************************************************************)
(* STOP states												*)
(************************************************************)

	MACH_ST_STOPPING:

		(****************************)
		(* Check for machine CMDs	*)
		(****************************)

		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Stopping.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN
		
			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		
	MACH_ST_STOPPED:
				
		(****************************)
		(* Wait for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Stopped.ColorDP:=	1;
		
		IF( HMIMachineCMD.Abort.CMD = 1)THEN
			
			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Reset.StatusDP.0:= 0;

		IF( HMIMachineCMD.Reset.CMD = 1)THEN
			
			gMachine.IN.CMD.Reset:=1;
		
		END_IF
		
		
(************************************************************)
(* IDLE states												*)
(************************************************************)

	MACH_ST_RESETTING:	
		
		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Resetting.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN
			
			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN
		
			gMachine.IN.CMD.Stop:=1;
		
		END_IF
		

	MACH_ST_IDLE:	
		
		
		(****************************)
		(* Wait for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Idle.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN
		
			gMachine.IN.CMD.Stop:=1;
		
		END_IF
		
		HMIMachineCMD.Start.StatusDP.0:= 0;

		IF( HMIMachineCMD.Start.CMD = 1)THEN

			gMachine.IN.CMD.Start:=1;
		
		END_IF
		

(************************************************************)
(* EXECUTE states											*)
(************************************************************)

	MACH_ST_STARTING:
	
		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Starting.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
		
		
	MACH_ST_EXECUTE:
	
		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Execute.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
			
		HMIMachineCMD.Hold.StatusDP.0:= 0;

		IF( HMIMachineCMD.Hold.CMD = 1)THEN

			gMachine.IN.CMD.Hold:=1;
		
		END_IF
			
		HMIMachineCMD.Suspend.StatusDP.0:= 0;

		IF( HMIMachineCMD.Suspend.CMD = 1)THEN

			gMachine.IN.CMD.Suspend:=1;
		
		END_IF


	MACH_ST_COMPLETING:
	
		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Completing.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
	
		
	MACH_ST_COMPLETE:
			
		
		(****************************)
		(* Wait for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Complete.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
			
		HMIMachineCMD.Reset.StatusDP.0:= 0;

		IF( HMIMachineCMD.Reset.CMD = 1)THEN

			gMachine.IN.CMD.Reset:=1;
		
		END_IF


(************************************************************)
(* HOLD states												*)
(************************************************************)

	MACH_ST_HOLDING:

		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Holding.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
	
	
	MACH_ST_HELD:
		
		
		(****************************)
		(* Wait for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Held.ColorDP:=	1;
		
		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
			
		HMIMachineCMD.Unhold.StatusDP.0:= 0;

		IF( HMIMachineCMD.Unhold.CMD = 1)THEN

			gMachine.IN.CMD.Unhold:=1;
		
		END_IF
	
	
	MACH_ST_UNHOLDING:

		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.UnHolding.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
	
	
(************************************************************)
(* SUSPEND states											*)
(************************************************************)

	MACH_ST_SUSPENDING:
			
		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Suspending.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
	
	
	MACH_ST_SUSPENDED:
		
		
		(****************************)
		(* Wait for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Suspended.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
		
		HMIMachineCMD.Unsuspend.StatusDP.0:= 0;

		IF( HMIMachineCMD.Unsuspend.CMD = 1)THEN

			gMachine.IN.CMD.Unsuspend:=1;
		
		END_IF
	
	
	MACH_ST_UNSUSPENDING:
			
		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.UnSuspending.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
		
		HMIMachineCMD.Stop.StatusDP.0:= 0;

		IF( HMIMachineCMD.Stop.CMD = 1)THEN

			gMachine.IN.CMD.Stop:=1;
		
		END_IF
	
		
(************************************************************)
(* ABORT states												*)
(************************************************************)

	MACH_ST_ABORTING:
			
		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		HMIMachineState.Aborting.ColorDP:=	1;
		(* No CMDs possible in MACH_ST_ABORTING *)
		
		
	MACH_ST_ABORTED:
	
		
		(****************************)
		(* Wait for Machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Clear.StatusDP.0:= 0;
		HMIMachineState.Aborted.ColorDP:=	1;
		
		IF( HMIMachineCMD.Clear.CMD = 1)THEN

			gMachine.IN.CMD.Clear:=1;
		
		END_IF			


	MACH_ST_CLEARING:

		(****************************)
		(* Check for machine CMDs	*)
		(****************************)
		
		HMIMachineCMD.Abort.StatusDP.0:= 0;
		HMIMachineState.Clearing.ColorDP:=	1;

		IF( HMIMachineCMD.Abort.CMD = 1)THEN

			gMachine.IN.CMD.Abort:=1;
		
		END_IF
	
	
END_CASE

	
HMIMachineCMD.Abort.CMD:=0;
HMIMachineCMD.Clear.CMD:=0;
HMIMachineCMD.Hold.CMD:=0;
HMIMachineCMD.Reset.CMD:=0;
HMIMachineCMD.Start.CMD:=0;
HMIMachineCMD.Stop.CMD:=0;
HMIMachineCMD.Suspend.CMD:=0;
HMIMachineCMD.Unhold.CMD:=0;
HMIMachineCMD.Unsuspend.CMD:=0;
END_PROGRAM
