                                                                      
{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogInstall				(*installs a (logging) definition; asynchronous execution*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
		pVersion	: {REDUND_UNREPLICABLE} UDINT;			(*pointer to the definition verison, null if actual version should be used*)
		pDefinition	: {REDUND_UNREPLICABLE} UDINT;			(*pointer to the profiler definition structure*)
	END_VAR

	VAR
        i_state		: UINT;				(*internal variable*)
		i_result	: UINT;				(*internal variable*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogDeInstall				(*uninstalls a definition (profiling); asynchronous execution*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
		option		: UDINT;			(*reserved for future use*)
	END_VAR

	VAR
        i_state		: UINT;				(*internal variable*)
		i_result	: UINT;				(*internal variable*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogStateGet				(*returns the current state of the AR profiler; asynchronous execution*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
	END_VAR

	VAR
        i_state		: UINT;				(*internal variable*)
		i_result	: UINT;				(*internal variable*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
		logstate	: USINT;			(*ar profiler state*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogArchCreate			(*archives a data object; asynchronous execution*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
		pDevice		: {REDUND_UNREPLICABLE} UDINT;			(*device name given as a pointer, null for module archives*)
		pName		: {REDUND_UNREPLICABLE} UDINT;			(*pointer to the archive name*)
		option		: UDINT;			(*archive option (module or file archive)*)
	END_VAR

	VAR
        i_state		: UINT;				(*internal variable*)
		i_result	: UINT;				(*internal variable*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogArchDelete			(*deletes an archived data object; asynchronous execution*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
		pName		: {REDUND_UNREPLICABLE} UDINT;			(*pointer to the name of module archive name to delete*)
		option		: UDINT;			(*reserved for future use*)
	END_VAR

	VAR
        i_state		: UINT;				(*internal variable*)
		i_result	: UINT;				(*internal variable*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogArchCopy				(*copy a archived data objects; asynchronous execution*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
		pModuleName	: {REDUND_UNREPLICABLE} UDINT;			(*pointer to the name of the module*)
		pDevice		: {REDUND_UNREPLICABLE} UDINT;			(*pointer to the file device*)
		pFileName	: {REDUND_UNREPLICABLE} UDINT;			(*pointer to the name of the pd-file*)
		option		: UDINT;			(*options*)
	END_VAR

	VAR
        i_state		: UINT;				(*internal variable*)
		i_result	: UINT;				(*internal variable*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogArchInfo				(*collects info of archived data objects; asynchronous execution*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
		pInfo		: {REDUND_UNREPLICABLE} UDINT;			(*pointer to the info structure field*)
		maxEntries	: UDINT;			(*number of info entries provided*)
	END_VAR

	VAR
        i_state		: UINT;				(*internal variable*)
		i_result	: UINT;				(*internal variable*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
		entries		: UDINT;			(*number of found data objects*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogStart					(*starts an installed logging*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, 0xXXXX = see help*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogStop					(*stops logging; asynchronous execution*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
	END_VAR

	VAR
        i_state		: UINT;				(*internal variable*)
		i_result	: UINT;				(*internal variable*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogEvent					(*enters a user log event*)
	VAR_INPUT
		enable		: BOOL;				(*enables execution*)
		objIdent	: UDINT;			(*identifier of the object (0-0xFFFFFFFF)*)
		userEvent	: UDINT;			(*event ident (0-profUSER_EVENT_MAX)*)
		pAddData	: {REDUND_UNREPLICABLE} UDINT;			(*pointer to the additional data*)
		addDataLen	: UDINT;			(*length of additional data*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, 0xXXXX = see help*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK LogIdleShow				(*shows the idle time; asynchronous execution*)
	VAR_INPUT
		enable				: BOOL;		(*enables execution*)
		measurementPeriod	: UDINT;	(*milliseconds in range (100 - 60000)*)
		measurementLevel	: UDINT;	(*priority level in range (1 - 189)*)
	END_VAR

	VAR
        i_state		: UINT;				(*internal variable*)
		i_result	: UINT;				(*internal variable*)
	END_VAR

	VAR_OUTPUT
		status		: UINT;				(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
		totalTime	: UDINT;			(*total time of the measurement in microseconds*)
		idleTime	: UDINT;			(*idle time during the measurement in microseconds*)
		idleRate	: UDINT;			(*idle time during the measurement in percent*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION CpuGetNumberOfCores : UDINT (*get the number of cores of the CPU*)
END_FUNCTION

{REDUND_OK} FUNCTION CpuGetLoadByCore : UDINT (*get the load of one CPU core. Range: 0..100*)
	VAR_INPUT
		core	:UDINT;                     (*the number of the core, starting from 0 *)
	END_VAR
END_FUNCTION

{REDUND_OK} FUNCTION CpuIsCoreReserved : BOOL (*returns true when the core is reserved, and thus can only be used for specific IO tasks*)
	VAR_INPUT
		core	:UDINT;                     (*the number of the core, starting from 0 *)
	END_VAR
END_FUNCTION
