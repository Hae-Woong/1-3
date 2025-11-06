# VECS_1_3_HIL

## Table of Contents

- [Introduction](#introduction)
- [Dependencies](#dependencies)
- [Repository Layout](#repository-layout)
- [Trigger the pipeline](#trigger-the-pipeline)
- [View the pipeline](#view-the-pipeline)
- [Future Improvements](#Future-Improvements)
- [Re-using the demo](Re-using-the-demo:-Hardware-and-Local-Setup)

## Introduction

In an ever growing and more complex world, CI / CD solutions are key to develop and provide fast and reliable software solutions. By combining the work of the whole team in one repository and automatically test the changes, CI / CD provides fast testing and change feedback.
This repository should give you a peek into the capabilities of vector tools in a CI context. Starting with the changes of C-Code for an ECU, triggering the whole compilation and testing of both the virtual ECU and real ECU, including instrumentation of application code on lvl3 vECU.
Leading to test-reports, showing you if your changes broke some tests or functionality of your ECU.

In this demo repository, you can take action, by editing the C Files under [/ECU/BFC/Appl/](/ECU/BFC/Appl/) to trigger the attached CI pipeline and see the Vector Tools in action.
Afterwards you can observe the test-results and see, if your changes broke some tests.

## Dependencies

- internet connection

## Repository Layout

- [environment-make](/environment-make/) contains all files to run CANoe4SWSE and CANoeSE. Most importantly the `venvironment.yaml` file, which describes the CANoe4SW SE & CANoe SE setup.
- [ECU](/ECU/BFC/Appl) contains the source code for the real and virtual ECU, which gets tested in this demo pipeline.
- [FBL](/ECU/BFC/FBL) contains the binary files to flash the bootloader on the target hardware. These files are only needed if the CI pipeline shall run on a different Tricore tc397 HW, which is not connected to the current github runners. 
- [tests](/tests/) contains the tests executed by CANoe4SWSE and CANoeSE.

## Trigger the pipeline
Important: Create a separate branch if you want to trigger the pipeline. Do not work on the main branch(Contact vsgoma to get write access)

Use the git command-line tool. For this option, follow the instructions [here](/doc/trigger-with-git.md)

## View the pipeline

To see the pipeline working and CANoe and vCAST test reports, navigate to the "Actions" tab.
After each pipeline run, the CANoe and vCAST test reports will be uploaded as an artifact which can be downloaded to the user PC.


## Future Improvements
- At the moment, the BSW SIP is downloaded on the runner PC through a Vector Portal Link. This will be replaced with Jfrog Artifactory.
- Bazel will be added for faster build time for real target.
- VectorCAST/QA will be added to real target HW.


## Re-using the demo: Hardware and Local Setup
If you prepare to re-use the demo locally, follow these steps:
1) Install the following tools on your local machines:
   - CANoe4SW SE 18 SP3 or newer 
   - CANoe SE 18 SP3 or newer
   - vVIRTUALtarget 8 SP3 or newer
   - VectorCAST/QA 2024
   - DaVinci Developer Classic 4.11 SP3 or newer
   - vFlash 10
   - Hexview (Needed for HIL) Contact vsgoma for link.
   - Squore 24.0.4.2 (Optional)
2) Ensure you have licenses for all Vector tools listed above, a license for the DaVinci Configurator tool and tasking compiler license. In this demo TriCorev6.2r1 compiler was used.
3) Fetch the BSW SIP from: https:\\portal.vector.com\shared\36d0729e-2c75-401b-b9bf-107f6459b57f\BSW.zip
4) Order the HW from: https://www.ehitex.de/en/evaluation-boards/infineon/2675/kit-a2g-tc397xa-trb
5) Setup a VT system with VT2516A,VT2004A and VT7001A
6) Three portpins cables need to be connected to the hardware from the VT system: PortPin P33.11 is used for DIO, AN7 is for ADC, and the third cable should be connected to GND.
7) The BSW configuration is configured to use CAN0 on target HW. Connect CAN_HIGH and CAN_LOW to CAN0.
8) Flash the bootloader once with debugger. The binaries can be found in ./ECU/BFC/FBL.
9) Flash the application software manually with debugger, this step is only necessary first time. The application binary can be found in /ECU/BFC/FBL/BFC_Binaries.
10) Perform HW reset and remove debugger
11) Make sure that path to the vflash project is correct in ExecuteFlashing.bat file. vFlash does not support at the moment relative paths.
12) Create new Github Runners
13) Commit the changes made in ExecuteFlashing.bat to the GIT repository
14) Run it!