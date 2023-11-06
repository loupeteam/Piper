<?xml version="1.0" encoding="utf-8"?>
<?AutomationStudio FileVersion="4.9"?>
<SwConfiguration CpuAddress="SL1" xmlns="http://br-automation.co.at/AS/SwConfiguration">
  <TaskClass Name="Cyclic#1" />
  <TaskClass Name="Cyclic#2" />
  <TaskClass Name="Cyclic#3" />
  <TaskClass Name="Cyclic#4">
    <Task Name="MachineHMI" Source="MachineControl.MachineHMI.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="MachinePro" Source="MachineControl.MachineProg.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="PiperModul" Source="MachineControl.PiperModuleTemplate.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="cPiperModu" Source="MachineControl.cPiperModuleTemplate.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
  </TaskClass>
  <Libraries>
    <LibraryObject Name="operator" Source="Libraries.operator.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="sys_lib" Source="Libraries.sys_lib.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsBrStr" Source="Libraries.AsBrStr.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="runtime" Source="Libraries.runtime.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="Piper" Source="Libraries.Loupe.Piper.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
  </Libraries>
</SwConfiguration>