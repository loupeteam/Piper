// In this example, the network used is powerlink, and there is one main with one remote.

ACTION CommsVerifySize:
	
	// Verify the size of IO variables used in multi-PLC communication.

	SIZEOF_MODULE_MAIN := SIZEOF(gMachine.IO.oMainInterface);
	SIZEOF_MODULE_REMOTE := SIZEOF(gMachine.IO.iMainInterface);
	
	IF SIZEOF(gMachine.IO.oMainInterface) = SIZEOF(oModuleInterface) 
		AND SIZEOF(gMachine.IO.iMainInterface) = SIZEOF(iModuleInterface) THEN
		ioSizeVerfied := TRUE;
	ELSE
		logError('App', 0, 'Piper IO interface does not match buffer size. Comms disabled.', 0);
		//errcolAddError(ADR('MachineProg'), ADR('Piper IO interface does not match buffer size. Comms disabled.'), 0, 0, gErrorCollector);
	END_IF

END_ACTION


ACTION CommsHandleInputs:
	
	// Write the input IO to the appropriate module interface
	
	IF ioSizeVerfied AND iNetworkConnected THEN
		IF Configuration.remotePLC THEN
			brsmemcpy(ADR(gMachine.IO.iMainInterface), ADR(iModuleInterface), SIZEOF_MODULE_REMOTE);
		ELSE
			brsmemcpy(ADR(remoteModuleInterface), ADR(iModuleInterface), SIZEOF_MODULE_REMOTE);
		END_IF
	END_IF

END_ACTION


ACTION CommsHandleOutputs:
	
	// Write the appropriate module interface to the output IO
	
	IF ioSizeVerfied THEN
		IF Configuration.remotePLC THEN
			brsmemcpy(ADR(oModuleInterface), ADR(gMachine.IO.oMainInterface), SIZEOF_MODULE_MAIN);
		ELSE
			brsmemcpy(ADR(oModuleInterface), ADR(remoteModuleInterface), SIZEOF_MODULE_MAIN);
		END_IF
	END_IF

END_ACTION


ACTION CommsHandleNetwork:
	
	// Handle network connects and disconnects
	
	powerLinkConnectedRTrig.CLK := iNetworkConnected;
	powerLinkConnectedRTrig();
	
	powerLinkConnectedFTrig.CLK := iNetworkConnected;
	powerLinkConnectedFTrig();
	
	IF remoteModuleErrorAck THEN
		remoteModuleErrorAck := FALSE;
		remoteModuleError := FALSE;
	END_IF
	
	IF ioSizeVerfied THEN
		IF Configuration.remotePLC THEN
			IF NOT gIsRemote THEN
				IF NOT gMachine.IO.iMainInterface.ModuleIsBypassed THEN
					gIsRemote := TRUE;
				END_IF
			END_IF
			
			// TODO: Handle powerlink disconnects better 
			IF powerLinkConnectedFTrig.Q THEN // TODO: Do we need a debounce for this?
				// IF we loose connection while running, stop
				gIsRemote := FALSE;
				gMachine.IN.CMD.Abort := TRUE;
			END_IF
			
			remoteModuleInterface.ModuleBypass := TRUE; // We want to ingore our selves with we are changed to a remote :)
		ELSE
			
			IF remoteModuleInterface.ModuleName = '' THEN
				remoteModuleInterface.ModuleName := 'Remote PLC';
			END_IF
			
			IF powerLinkConnectedFTrig.Q THEN
				IF NOT remoteModuleInterface.ModuleBypass THEN
					IF gMachine.OUT.State <> MACH_ST_ABORTED THEN
						gMachine.IN.CMD.Abort := TRUE;
					END_IF
					
			
				END_IF
				// TODO: We will need to handle reconnects 
				remoteModuleInterface.ModuleBypass := TRUE; // Disconnect remote from Piper
			END_IF
			
			IF remoteModuleInterface.ModuleBypass THEN
				// TODO: gMachine.IO.oModule is not populated while acting as a main Piper, so remoteModuleInterface.PiperState will not be updated while bypassed. So This will not work until we fix that
				IF iNetworkConnected AND gMachine.OUT.State = MACH_ST_ABORTED AND remoteModuleInterface.PiperState = MACH_ST_ABORTED THEN // remoteModuleInterface only represents the remote until piper is called
					remoteModuleInterface.ModuleBypass := FALSE; // Connect remote to Piper 
				END_IF
				
				IF NOT remoteModuleError THEN
					remoteModuleError := TRUE; // Error latch so we dont spam errors
					logError('App', 0, 'Module disconnected from powerlink', 0);
					//errcolAddError(ADR(remoteModuleInterface.ModuleName), ADR('Module disconnected from powerlink'), 0, ADR(remoteModuleErrorAck), gErrorCollector);
				END_IF
			END_IF
			
			remoteModule.ModuleInterface := ADR(remoteModuleInterface);
			remoteModule.Piper := ADR(gMachine);
			remoteModule();
			
			// Temp fix because Piper remote does not handle boot right now 
			IF gMachine.OUT.State = MACH_ST_BOOTING THEN
				remoteModuleInterface.ModuleResponse := MACH_ST_BOOTING;
			END_IF
		END_IF
	END_IF

END_ACTION
