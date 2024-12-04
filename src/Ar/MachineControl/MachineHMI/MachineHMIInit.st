(*
* File: MachineHMIInit.st
* Copyright (c) 2023 Loupe
* https://loupe.team
* 
* This file is part of MachineHMI, licensed under the MIT License.
*)

PROGRAM _INIT
	
	//Hide Main page state model
	HMIMachineState.MachineStateLayer.StatusDP:=	1;

END_PROGRAM
