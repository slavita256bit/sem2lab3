cmake_minimum_required(VERSION 3.20)
project(sem2lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sem2lab3
    src/main.cpp
    src/String.cpp
    src/Vehicle.cpp
    src/CargoVehicle.cpp
    src/DumpTruck.cpp
    src/PassengerVehicle.cpp
    src/Bus.cpp
    src/Trolleybus.cpp
)

target_include_directories(sem2lab3 PRIVATE include)

if(MSVC)
    target_compile_options(sem2lab3 PRIVATE /W4 /utf-8)
else()
    target_compile_options(sem2lab3 PRIVATE -Wall -Wextra -Wpedantic)
endif()
