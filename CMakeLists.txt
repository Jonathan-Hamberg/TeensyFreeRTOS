set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoTeensy3Toolchain.cmake) # Arduino Toolchain

cmake_minimum_required(VERSION 3.0)

project ( TeensyFreeRTOS C ASM)

set(CMAKE_C_FLAGS "-Wall -fno-common -mcpu=cortex-m4 -mthumb")
set(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -T${CMAKE_SOURCE_DIR}/src/Teensy31_flash.ld -Xlinker -Map=Teensy.map -Xlinker --cref")

include_directories(.)
include_directories(src/include)

add_executable(${PROJECT_NAME}.elf
        src/crt0.s
        src/main.c
        src/sysinit.c
        src/arm_cm4.c
        src/freertos/FreeRTOSConfig.h
        src/freertos/tasks.c
        src/freertos/list.c
        src/freertos/heap_2.c
        src/freertos/croutine.c
        src/freertos/queue.c
        src/freertos/event_groups.c
        src/freertos/timers.c
        src/freertos/port.c
        src/freertos/deprecated_definitions.h
        src/freertos/FreeRTOS.h
        src/freertos/mpu_wrappers.h
        src/freertos/portable.h
        src/freertos/portmacro.h
        src/freertos/projdefs.h
        src/freertos/semphr.h
        src/freertos/StackMacros.h
        src/freertos/task.h
        src/include/arm_cm4.h
        src/include/common.h
        src/include/mcg.h
        src/include/MK20D7.h
        src/include/SKEAZN84.h
        src/include/SKEAZN642.h
        src/include/SKEAZ1284.h
        src/include/start.h
        src/include/startup.h
        src/include/sysinit.h
        src/include/term_io.h
        src/include/uart.h
        src/include/wdog.h)

target_link_libraries(${PROJECT_NAME}.elf "C:/Program Files (x86)/Arduino/hardware/tools/arm/arm-none-eabi/lib/armv7e-m/libc_nano.a")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
        )
