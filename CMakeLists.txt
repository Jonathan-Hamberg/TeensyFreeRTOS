set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoTeensy3Toolchain.cmake) # Arduino Toolchain

cmake_minimum_required(VERSION 3.0)

project ( TeensyFreeRTOS C ASM)



set(CMAKE_C_FLAGS "-Wall -fno-common -mcpu=cortex-m4 -mthumb")
#set(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++11")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m4")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -Map=Teensy.map -T${CMAKE_SOURCE_DIR}/Teensy31_flash.ld --cref")

include_directories(.)
include_directories(include)
include_directories(freertos)
include_directories(freertos/include)
include_directories(freertos/portable)

add_executable(${PROJECT_NAME}.elf
        crt0.s
        main.c
        sysinit.c
        freertos/tasks.c
        freertos/list.c
        freertos/heap_2.c
        freertos/croutine.c
        freertos/queue.c
        freertos/event_groups.c
        freertos/timers.c
        freertos/portable/port.c)

target_link_libraries(${PROJECT_NAME}.elf "C:/Program Files (x86)/Arduino/hardware/tools/arm/arm-none-eabi/lib/armv7e-m/libc.a")

message("SDK_PATH: ${ARDUINO_SDK_PATH}")
message("CMAKE_C_COMPILER ${CMAKE_C_COMPILER}")