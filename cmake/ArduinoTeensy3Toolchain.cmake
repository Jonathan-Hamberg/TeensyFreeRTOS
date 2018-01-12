# Set file paths based on linux.
if(UNIX)
    file(GLOB SDK_PATH_HINTS /usr/share/arduino*
            /opt/local/arduino*
            /opt/arduino*
            /usr/local/share/arduino*)
elseif(WIN32)
    set(SDK_PATH_HINTS "C:\\Program Files\\Arduino"
            "C:\\Program Files (x86)\\Arduino"
            )
endif()

# Find the arduino directory.
find_path(ARDUINO_SDK_PATH
        NAMES lib/version.txt
        PATH_SUFFIXES share/arduino
        Arduino.app/Contents/Resources/Java/
        ${ARDUINO_PATHS}
        HINTS ${SDK_PATH_HINTS}
        DOC "Arduino SDK path.")


set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

SET(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_C_COMPILER ${ARDUINO_SDK_PATH}/hardware/tools/arm/bin/arm-none-eabi-gcc.exe)
set(CMAKE_CXX_COMPILER ${ARDUINO_SDK_PATH}/hardware/tools/arm/bin/arm-none-eabi-g++.exe)
#set(CMAKE_ASM_COMPILER ${ARDUINO_SDK_PATH}/hardware/tools/arm/bin/arm-none-eabi-as.exe)
set(CMAKE_LINKER ${ARDUINO_SDK_PATH}/hardware/tools/arm/bin/arm-none-eabi-ld.exe)
set(CMAKE_OBJCOPY_COMPILER ${ARDUINO_SDK_PATH}/hardware/tools/arm/bin/arm-none-eabi-objcopy.exe)

set(CMAKE_C_LINK_EXECUTABLE "\"${CMAKE_LINKER}\" <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE ""${CMAKE_LINKER}" <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

message("TESTING: ${CMAKE_ASM_FLAGS_INIT}")
set(CMAKE_INSTALL_PREFIX ${ARDUINO_SDK_PATH}/hardware/tools/gcc-arm-none-eabi/arm-none-eabi/lib)

message("CMAKE_C_LINK_EXECUTABLE ${CMAKE_C_LINK_EXECUTABLE}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs")

set(CMAKE_FIND_ROOT_PATH ${ARDUINO_SDK_PATH}/hardware/tools/gcc-arm-none-eabi/arm-none-eabi/lib)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

