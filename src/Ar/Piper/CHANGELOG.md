# Change log

0.1.9 - Add Piper_getBusyModules to display several busy modules at once
      - Prevent abort commands while in BOOTING and BOOTED

0.1.8 - Update dependencies

0.1.7 - Add Boot cycles to CFG
		Fix substate incrementing before configured boot cycles

0.1.6 - Migrate from AsString to AsBrStr

0.01.5 - Added Bypass All commands
0.01.4 - 	Move SubState reset from handleResponseState() to PiperStateChange(). 
			Add Module.ModuleIsBypassed and MACH_ST_BYPASSED.
			
0.01.2 - 20140918 - Added ability to do all transfer types without corrupting piper data.

0.01.1 - 20140626 - Fixed logger spamming if a subsystem responded with ERROR in aborting

0.01.0 - 20140207 - Fixed an issue that could cause a substate request to not be reported to logger.

0.00.9 - 20140130 - Module response only reset on state change.
				  - Handle aborting better.
				  - Set substate to 65535 when main state is finished

0.00.8 - 20140130 - Fixed some issues with aborting and substates.

0.00.7 - 20131223 - Modified logging to use LogThat library, changed IN.CFG.LoggerID to IN.CFG.LoggerName, bug fix that cleared Piper.IN.CFG

0.00.6 - 20131125 - If module is added after booting state it will post a WARNING.

0.00.5 - 20131125 - Added Module Status.
0.00.4 - 20131121 - Changed logger ascii data to ease readability in App logger

0.00.3 - 20131115 - Changed to ModuleSubStateResponse.
					Fixed an issue with ModuleBypass not resetting ModuleSubStateRequest

0.00.2 - 20131108 - Added ModuleBypass