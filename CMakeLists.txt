cmake_minimum_required(VERSION 3.10)
project(aeda_hotel_projeto)


set(CMAKE_CXX_STANDARD 17)

SET(GCC_COVERAGE_COMPILE_FLAGS "-static-libgcc -static-libstdc++")
SET(GCC_COVERAGE_LINK_FLAGS    "-static-libgcc -static-libstdc++")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(
        aeda_hotel_projeto
        main.cpp
        GUI/buttons.cpp
        GUI/utils.cpp
        room/room.cpp
        room/suite.cpp
        room/noviewroom.cpp
        room/viewroom.cpp
        human/client/client.cpp
        human/staff/staff.cpp
        human/staff/manager.cpp
        human/staff/janitor.cpp
        human/staff/receptionist.cpp
        human/staff/responsibles.cpp
        human/human.cpp
        product/product1.cpp
        hotel/hotel.cpp
        hotel/reservation.cpp)
