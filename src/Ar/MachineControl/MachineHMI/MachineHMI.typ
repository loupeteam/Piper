(*
* File: MachineHMI.typ
* Copyright (c) 2023 Loupe
* https://loupe.team
* 
* This file is part of MachineHMI, licensed under the MIT License.
*)

TYPE
	Machine_HMI_CMD_typ : 	STRUCT 
		Reset : HMI_Button_typ;
		Start : HMI_Button_typ;
		Stop : HMI_Button_typ;
		Hold : HMI_Button_typ;
		Unhold : HMI_Button_typ;
		Suspend : HMI_Button_typ;
		Unsuspend : HMI_Button_typ;
		Abort : HMI_Button_typ;
		Clear : HMI_Button_typ;
	END_STRUCT;
	Machine_HMI_State_typ : 	STRUCT 
		MachineStateLayer : HMI_Layer_typ;
		Stopped : HMI_Shape_typ;
		Resetting : HMI_Shape_typ;
		Idle : HMI_Shape_typ;
		Starting : HMI_Shape_typ;
		Execute : HMI_Shape_typ;
		Completing : HMI_Shape_typ;
		Complete : HMI_Shape_typ;
		Suspending : HMI_Shape_typ;
		Suspended : HMI_Shape_typ;
		UnSuspending : HMI_Shape_typ;
		Holding : HMI_Shape_typ;
		Held : HMI_Shape_typ;
		UnHolding : HMI_Shape_typ;
		Aborting : HMI_Shape_typ;
		Aborted : HMI_Shape_typ;
		Clearing : HMI_Shape_typ;
		Stopping : HMI_Shape_typ;
	END_STRUCT;
END_TYPE
