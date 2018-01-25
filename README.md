# TeensyFreeRTOS
Minial FreeRTOS for Teensy 3.1 using CMake.

This project is directly based on [Teensy3.1_FreeRTOS](https://github.com/stevegolton/Teensy3.1_FreeRTOS) project on github.
The CMake script to find the arm toolchain from the arduino directory is pulled from the [arduino-cmake](https://github.com/queezythegreat/arduino-cmake) repository.

Changes from original project.
* Modified the Makefile to use CMakeLists.txt instead.
* Updated to FreeRTOS v10.0.0

## Build
This build has only been tested on Windows.  Slight modifications can be made to the CMakeLists.txt to find the toolchain on Linux and OSX.
Has been tested with the Ninja build system.  Also compatible with the CLion IDE.
The toolchain used is the noe that is included with the [Arduino](https://www.arduino.cc/en/Main/Software) and the [Teensy](https://www.pjrc.com/teensy/td_download.html) installer.
