                                                                      
{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK AsIOAccRead				(*reads noncyclical register (only inputs); asynchronous execution*)
	VAR_INPUT
		enable	:BOOL;					(*enables execution*)
		pDeviceName	:UDINT;				(*device name given as a pointer*)
		pChannelName	:UDINT;			(*pointer to the channel name*)
	END_VAR
	VAR_OUTPUT
		status	:UINT;					(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
		value	:UDINT;					(*value read*)
	END_VAR
	VAR
		intern	:IOAC_I_TYPE;			(*internal variable*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} {REDUND_UNREPLICABLE} FUNCTION_BLOCK AsIOAccWrite				(*writes noncyclical register (ONLY outputs); asynchronous execution*)
	VAR_INPUT
		enable	:BOOL;					(*enables execution*)
		pDeviceName	:UDINT;				(*device name given as a pointer*)
		pChannelName	:UDINT;			(*pointer to the channel name*)
		value	:UDINT;					(*value to be written*)
	END_VAR
	VAR_OUTPUT
		status	:UINT;					(*execution status: ERR_OK, ERR_FUB_ENABLE_FALSE, ERR_FUB_BUSY, 0xXXXX = see help*)
	END_VAR
	VAR
		intern	:IOAC_I_TYPE;			(*internal variable*)
	END_VAR
END_FUNCTION_BLOCK

