# Traffic Light Intersection

I had an embedded systems interview where I was asked to build a traffic light intersection model with only red and green stops (yellow was not required to save time). This is a working model of that project using a **ST NUCLEO-G071RB** board and an 8-bit shift register. The intersection is managed with a state machine.


## Project Overview
* Simulates a 4 stop intersection using a pair of LEDs (green, red) for each stop.
* To simulate yellow, which was omitted to save space, both green & red LEDs turn on to indicate a transition from green to red.
* B1 (blue button on Nucleo) triggers an interrupt to put all traffic stop points to red.


### Technical 

* **ST NUCLEO-G071RB** board (STM32G071xx MCU).
* **TI SN74HC595N** 8-bit shift register to control 8 LEDs.
* Runs **GoogleTest** and step debugging on the host machine.
* Cross-compile target firmware with **arm-none-eabi-gcc**.
* Run step debugging on the target machine.
* [Schematic Diagram](./Schematics.md)

## Included in Container

* GNU ARM Compiler Toolchain (`arm-none-eabi-gcc`)
* Ninja
* OpenOCD (On-Chip Debugger)
* Clangd & Clang-Tidy (Static analysis & autocomplete)
* GDB
* LLDB Debugger
* GoogleTest framework


## Requirements

* VScode
    * Dev Containers Plugin
* Docker


## Setup

1. Build Container using VScode build container.
2. Install the drivers by running **`./build drivers`**


## Terminal Commands

* **`./build drivers`**       : Download STM HAL and CMSIS library files to ./drivers.
* **`./build test`**          : Compiles and runs the host unit tests using host compiler.
* **`./build debug`**         : Cross-compile debug FW, this is for checking ctidy.
* **`./build flash-debug`**   : Cross-compile & flash debug FW for target.
* **`./build flash-release`** : Cross-compile & flash release FW for target.
