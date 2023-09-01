# CAN-Bus-Test
PIC firmware for performing a communication test between two PIC18F26K83 microcontrollers through CAN.

Within this firmware there are two available tests:
- The goal of the first test is to verify that at least one of the microcontrollers listens the messages sent by the other.
- The goal of the second test was to create an application loop in which each time a microcontroller receives a message, it blinks the LED for 1s and sends a message that the other node receives.

## Setup

![broadboard_can_bus_top_viewjpg](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/c0f4a20e-199d-4b0a-b0b2-8a69f7578277)

## Requirements

Install MPLAB X IDE tool for Windows ([download link](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide#tabs)).
If working on Ubuntu or another OS, download VirtualBox and use the virtual machine uploaded [here](https://drive.google.com/open?id=0BxR76I90oKSmQ0xsS0loZVhhRnM) (includes MPLAB IDE v.8.92 and EasySetup on Windows 7).

## How to download the firmware to the PIC

Once MPLAB is opened, load the project through *Project > Open* and then select the file `pic_source.mcp`.
This will open the work environment, where `main.c` is the code file that will be compiled into the PIC.
Make sure that MPLAB is already connected to the PIC. External power needs to be supplied to the programmer. It is recommended to disconnect the CAN wire that is connected to the driver to avoid deriving electric current into it.

First, modify the `canId` variable corresponding to the ID of that encoder. The correspondence is detailed in [this diagram](https://robots.uc3m.es/teo-developer-manual/diagrams.html#joint-indexes). A value of 100 must be added to the ID of the iPOS node. Example: for the elbow of the left arm joint ID 24, use `canId = 124`.

Then, follow the next steps:
* Compile: `Project> Build All`
* Select the programmer: `Programmer> Select Programmer> MPLAB ICD 2`
* Connect the programmer to the PIC: `Programmer> Connect`
* Program: `Programmer> Program`

## Interfacing with the CUI

A 1 Mbps CAN channel is used to interface with the receiver code running on the PIC. Encoder data (in joint space, expressed in degrees) can be retrieved in two operation modes: continuous stream (push mode) and on demand (pull mode). In push mode, encoder reads are streamed after the start command is issued, using the specified delay, until a stop command is received. All commands (as well as the streamed data) return an acknowledge message with the corresponding operation code, i.e., the returned message ID is op code + canId.

| command                                    | request payload                   | response payload  | op code |
|--------------------------------------------|-----------------------------------|-------------------|---------|
| *continuous data stream*<br>*in push mode* | doesn't apply                     | *value* (4 bytes) | 0x80    |
| start push mode                            | 0x01 (byte 0)<br>*delay* (byte 1) | empty             | 0x100   |
| stop push mode                             | 0x02                              | empty             | 0x100   |
| poll current value                         | 0x03                              | *value* (4 bytes) | 0x180   |
| set encoder to zero                        | 0xFF                              | empty             | 0x200   |

## See also

* Víctor César Sanz Labella, *Diseño del circuito electrónico de control y programación de una mano subactuada para el robot humanoide TEO*, bachelor's thesis, Universidad Carlos III de Madrid, 2014. ([lacquey-pic-firmware](https://github.com/roboticslab-uc3m/lacquey-pic-firmware))
