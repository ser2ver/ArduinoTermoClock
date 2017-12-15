cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME ArduinoTermoClock)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SKETCH ArduinoTermoClock.ino Util.h Util.cpp Termo.h Termo.cpp Display.h Display.cpp DisplayText.h DisplayText.cpp)
set(${CMAKE_PROJECT_NAME}_HDRS Util.h Termo.h Display.h DisplayText.h)
set(${CMAKE_PROJECT_NAME}_SRCS ArduinoTermoClock.ino Util.cpp Termo.cpp Display.cpp DisplayText.cpp)

### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_BOARD uno)
set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyUSB0)
#set(nano.build.mcu atmega328p)
#set(nano.upload.protocol wiring) #arduino
set(uno.upload.speed 9600)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
