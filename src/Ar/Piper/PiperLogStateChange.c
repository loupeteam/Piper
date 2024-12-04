<<<<<<<< HEAD:src/Ar/Piper/Piper_changeState.c
/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Piper
 * File: PiperLogStateChange.c
 * Author: Josh
 * Created: October 08, 2013
 ********************************************************************
 * Implementation of library Piper
 ********************************************************************/
========
/*
* File: PiperLogStateChange.c
* Copyright (c) 2023 Loupe
* https://loupe.team
* 
* This file is part of the Piper Library, licensed under the MIT License.
*/
>>>>>>>> origin/main:src/Ar/Piper/PiperLogStateChange.c

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

	#include "Piper.h"

#ifdef __cplusplus
	};
#endif

<<<<<<<< HEAD:src/Ar/Piper/Piper_changeState.c
// Performs and logs a state change
plcbit Piper_changeState(struct Piper_typ* Piper, enum MACH_ST_enum State) {
========
/* Logs a state change. */
plcbit PiperStateChange(struct Piper_typ* Piper, enum MACH_ST_enum State)
{
>>>>>>>> origin/main:src/Ar/Piper/PiperLogStateChange.c
	StrExtArgs_typ LogData;
	
	STRING Oldstate[80];
	STRING Newstate[80];	

	//Get the strings to log
<<<<<<<< HEAD:src/Ar/Piper/Piper_changeState.c
	PackMLStateString(Piper->OUT.State, Oldstate);	
	PackMLStateString(State, Newstate);	
========
	PackMLStateString(Piper->OUT.State,Oldstate);	
	PackMLStateString(State,Newstate);	
>>>>>>>> origin/main:src/Ar/Piper/PiperLogStateChange.c

	LogData.s[0] = (UDINT)Oldstate;
	LogData.s[1] = (UDINT)Newstate;
	
	//Log state change
<<<<<<<< HEAD:src/Ar/Piper/Piper_changeState.c
	logInfo(Piper->IN.CFG.LoggerName, 0, "%s -> %s", (UDINT)&LogData);
========
	logInfo(Piper->IN.CFG.LoggerName,0,"%s -> %s",(UDINT)&LogData);
>>>>>>>> origin/main:src/Ar/Piper/PiperLogStateChange.c

	//Change state
	Piper->OUT.State = State;
	Piper->OUT.SubState = 0;
	
	return 0;
}
