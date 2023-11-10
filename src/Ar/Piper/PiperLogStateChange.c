/*
* File: PiperLogStateChange.c
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

#ifdef __cplusplus
	};
#endif

/* Logs a state change. */
plcbit PiperStateChange(struct Piper_typ* Piper, enum MACH_ST_enum State)
{
	StrExtArgs_typ LogData;
	
	STRING Oldstate[80];
	STRING Newstate[80];	

	//Get the strings to log
	PackMLStateString(Piper->OUT.State,Oldstate);	
	PackMLStateString(State,Newstate);	

	LogData.s[0] = (UDINT)Oldstate;
	LogData.s[1] = (UDINT)Newstate;
	
	//Log state change
	logInfo(Piper->IN.CFG.LoggerName,0,"%s -> %s",(UDINT)&LogData);

	//Change state
	Piper->OUT.State = State;
	Piper->OUT.SubState = 0;
	
	return 0;
}
