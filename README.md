# SyncLoop RTOS HIL: STM32 Hardware-in-the-Loop Controller

[![CI/CD Pipeline](https://github.com/berkut3nko/syncloop-rtos-hil/actions/workflows/ci.yml/badge.svg)](https://github.com/berkut3nko/syncloop-rtos-hil/actions)

## Overview

SyncLoop RTOS HIL is an advanced Embedded C project demonstrating a real-time Hardware-in-the-Loop (HIL) simulation. Rather than interfacing with physical sensors, the microcontroller executes a precise PID control loop to stabilize a virtual physical model simulated on a host PC. 

This architecture showcases industrial-grade practices for embedded systems development, emphasizing strict task synchronization, memory safety, and robust serial communication. The core control logic is hardware-agnostic and validated through host-based unit testing prior to cross-compilation.

## Key Engineering Features

* **Real-Time Operating System:** Utilizes FreeRTOS with preemptive scheduling to guarantee strict `dt` execution for the PID control loop, eliminating timing jitter.
* **Robust Data Link Layer:** Implements a custom serial protocol using COBS (Consistent Overhead Byte Stuffing) framing and CRC16 validation to ensure data integrity over UART/USB.
* **Host-Based Unit Testing:** Integrates the Unity test framework to validate hardware-agnostic algorithms (PID, parsing, framing) directly on the host machine via a dedicated CMake testing target.
* **Continuous Integration:** Automated GitHub Actions pipeline configured for parallel cross-compilation (STM32) and host-testing (Linux x86).

## Hardware Requirements

The firmware is configured and optimized for the following hardware ecosystem:

* **Target Microcontroller:** STM32F103C8T6 (ARM Cortex-M3, commonly known as the "Blue Pill" board).
* **Programmer/Debugger:** ST-Link V2 (via Serial Wire Debug - SWD interface).
* **Communication Interface:** USB-to-UART TTL Adapter (FT232, CP2102, or equivalent) to facilitate high-speed telemetry exchange between the MCU and the PC simulator.

## Software Prerequisites

To compile and test the project locally, ensure the following toolchains are installed:

* **Cross-Compiler:** `arm-none-eabi-gcc`
* **Host Compiler:** Native `gcc` (for unit testing)
* **Build System:** `CMake` (>= 3.22) and `Ninja`
* **Simulation Environment:** `Python 3.10+` with `pyserial` (for executing the host-side physical plant simulation)

## Build Instructions

This project utilizes a dual-target CMake configuration to separate firmware compilation from host-based unit testing.

### 1. Build and Run Unit Tests (Host)
Execute the following commands to compile and run the Unity test suite on your local machine:
```bash
CC=gcc cmake -B build_test -G Ninja -DBUILD_TESTING=ON
cmake --build build_test
cd build_test && ctest --output-on-failure
```


### 2. Cross-Compile Firmware (Target)

Generate the `.elf`, `.bin`, and `.hex` files for the STM32 microcontroller:

```bash
cmake -B build -G Ninja
cmake --build build

```

### 3. Flash to Microcontroller

*(Assuming OpenOCD is installed and the ST-Link is connected)*:

```bash
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program build/FreeRTOSonSTM32.elf verify reset exit"

```

## Architecture Layout

* `Core/` & `Drivers/`: Hardware-specific HAL, RTOS initializations, and main application entry.
* `lib/`: Hardware-agnostic core logic (PID math, COBS protocol, CRC).
* `tests/`: Unity-based test cases for continuous validation.
* `simulation/`: PC-side Python scripts to emulate physical dynamics and render visualization.
