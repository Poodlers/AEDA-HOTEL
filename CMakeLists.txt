cmake_minimum_required(VERSION 3.10)
project(aeda_hotel_projeto)

set(CMAKE_CXX_STANDARD 17)

SET(GCC_COVERAGE_COMPILE_FLAGS "-static")
SET(GCC_COVERAGE_LINK_FLAGS    "-static")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

message("CMAKE_CXX_FLAGS is ${CMAKE_CXX_FLAGS}")
message("CMAKE_EXE_LINKER_FLAGS  is ${CMAKE_EXE_LINKER_FLAGS}")
message("CMAKE_STATIC_LINKER_FLAGS is ${CMAKE_STATIC_LINKER_FLAGS} ")

add_executable(
        aeda_hotel_projeto
        gui.cpp
        GUI/console.cpp
        hotel/date.cpp
        GUI/utils.cpp
        GUI/buttons.cpp
        hotel/reservation.cpp
        room/room.cpp
        room/suite.cpp
        room/noviewroom.cpp
        room/viewroom.cpp
        person/client/client.cpp
        person/staff/staff.cpp
        person/staff/manager.cpp
        person/staff/janitor.cpp
        person/staff/receptionist.cpp
        person/staff/responsibles.cpp
        provider/provider.cpp
        person/person.cpp
        product/product1.cpp
        hotel/hotel.cpp
        GUI/console.h Vehicles/vehicles.cpp)
