# Info
Library is provided by Loupe  
https://loupe.team  
info@loupe.team  
1-800-240-7042  

# Description
This repo provides packages that allow the implementation of the piper state machine.

### Program Package
This program package will install the MachineControl B&R package that will contain the MachineHMI program and the MachineProg for a Automation Studio project and all its dependencies.  
The MachineHMICyclic program handles the interface between the HMI machine struct and the gMachine struct.
The MachineProgCyclic program calls the main piper function block that handles the piper substate between machine modules.
There are two example programs PiperModuleTemplate and cPiperModuleTemplate that can be copied into new programs to implement new piper substates. 

### Library Package
Piper is used to control the state of a machine allowing machines to be built in subsystems in a modular way. Piper-based systems divide the functions of a machine into modules, each with their own task. Each module’s behavior is defined using a common set of machine states per the PackML standard.

# Installation
To install using the Loupe Package Manager (LPM), in an initialized Automation Studio project directory run `lpm install piperprog`. Note that this will also pull in the library package as a dependency.  
If you only want to install the library package, run `lpm install piper`.   
For more information about LPM, see https://loupeteam.github.io/LoupeDocs/tools/lpm.html

# Documentation
For more documentation and examples, see https://loupeteam.github.io/LoupeDocs/libraries/piper.html (or you can run `lpm docs piper`)

# Licensing

This project is licensed under the [MIT License](LICENSE).
