/*
* File: Piper_getState_remote.c
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

// Gets state and substate from main Piper
plcbit Piper_getState_remote(struct Piper_typ* Piper) {
	
	// Set Piper variables based on IO
	if (Piper->IO.iMainInterface.PiperState != Piper->OUT.State) {
		Piper_changeState(Piper, Piper->IO.iMainInterface.PiperState);
	}
	else if (Piper->IO.iMainInterface.PiperSubState != Piper->OUT.SubState) {
		Piper->OUT.SubState = Piper->IO.iMainInterface.PiperSubState;
	}
	
	return 0;
}