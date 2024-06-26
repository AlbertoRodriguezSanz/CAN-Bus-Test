# CAN Bus Test
PIC firmware for performing a communication test between two PIC18F26K83 microcontrollers through the CAN bus. The goal of this test is to create a loop in which each time a microcontroller receives a message, it blinks the LED for 1s and then sends a message for the other node to receive.

## Setup
A breadboard with two PIC18F26K83 microcontrollers connected through two MCP2561 CAN transceivers is used as a testbench. 

![broadboard_can_bus](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/c7f8d197-aaea-4b66-a1f7-cca86a771ab2)

For this test the PICkit4 in-circuit debugger/programmer will be used to load the firmware into the microcontroller. This needs to be connected to the microcontroller with the following pins.
- MCLR (needs to be connected through two series pull-up resistors (10kΩ and 100-470Ω) to the power supply.
- PGD
- PGC
- VDD
- VSS

The microcontrollers are connected through two MCP2561 CAN transceivers. For such short distances, the use of termination resistors is not required. The two connectors represent the PICKIT4 pins required for programming each of the two microcontrollers. 

![CAN_test_schematic_protoboard](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/4a2341d6-74a8-4b69-b55a-2c5f45167686)

## Device configuration

- Configuration bits (CONFIG1-5H/L registers)
  - Oscillator source at power-up: High frequency internall oscillator with no clock division applied
  - Master Clear and Low Voltage Programming: MCLR and LVP are enabled, making the MCLR pin work for as a master clear for programming.
  - Brown-out Reset: Disabled, device will not reset when voltage drops under a certain threshold.
  - Watchdog Timer: Disabled, the Windowed Watchdog Timer will not be enabled for this test, to check for timing inaccuracies while executing instructions.
- Clock Manager (OSCCON1 and OSCFRQ registers)
  -   Clock Frequency: 16MHz, proceeding from a 64MHz base High-Frequency Oscillator Clock
- Pin Manager:
  -  CAN Transmit (CANTX0) -> RB2 (output)
  -  CAN Receive (CANRX0) -> RB3 (input)
  -  LED pin -> RC2 (output)


## ECAN module configuration

Both microcontrollers implement these module parameters through the Microchip Code Configurator plugin (MCC):
- Clock Settings
  - Clock Source: Use system clock as CAN system clock
  - Clock Frequency: 16MHz
- Bit Rate Settings
  - CAN bus speed: 1Mbps
  - Time Quanta: 8
  - Sync Jumpt Width: 1xTQ
  - Sample Point: 75%
  - Phase Segment 1: 4xTQ
  - Phase Segment 2: 2xTQ
  - Propagation Segment: 1xTQ
- Transmit-Receive Settings
  - Operation Mode: Mode 0 (Legacy)
 
No filters or masks are setup for the CAN bus communications beforehand. Messages' ID are filtered in the `main.c` file as in the previous firmware for the PIC18F2580 microcontroller.
  
## Requirements

Install MPLAB X IDE tool for Windows, Linux or MAC from the following link ([download link](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide#tabs)).

## Operation

Once MPLAB is opened, load the project through *File > Open Project* and then select the file `CAN_bus_x.mc3`, where X denotates the firmware for each of the microcontrollers.
This will open the work environment, where `main.c` is the code file that will be compiled into the PIC. The project properties are accessed through *Production > Set Project Configuration > Customize...*, where the PICkit4 needs to be selected in the *Connected Hardware Tool* menu.
![Screenshot from 2023-09-01 14-19-52](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/248a38f8-ebf5-4f62-97c1-47c6fd496216)

Modify the following options from the default parameters for the PICkit4 programmer from the Option categories dropdown menu.
-Power
  - Power target circuit from PICkit4.
  - Voltage Level: 5V.
- PICkit4 Tool Options
  - Program Speed: Low (Otherwise an error will pop up when trying to load the firmware).

Then, follow the next steps:
* Compile: `Production> Build Main Project`
* Program: `Production> Make and Program Device Main Project`

Example of the generated CAN bus message:

![cangen](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/45609c17-906a-4e81-bd94-eed32a988df3)

- Channel 1 (Yellow): CAN-High (CANH)
- Channel 2 (Green): CAN-Low (CANL)
- Channel 3 (Purple): CAN Transmit (CANTX)
- Channel 4 (Blue): CAN Receive (CANRX)
