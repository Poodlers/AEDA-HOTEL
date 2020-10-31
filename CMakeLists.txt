cmake_minimum_required(VERSION 3.10)
project(aeda_hotel_projeto)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        aeda_hotel_projeto
        testing.cpp
        room/room.cpp
        room/suite.cpp
        room/noviewroom.cpp
        room/viewroom.cpp
        client/client.cpp
        staff/staff.cpp
        staff/manager.cpp
        staff/janitor.cpp
        staff/receptionist.cpp
        staff/responsibles.cpp
        product/product1.cpp
        hotel/hotel.cpp

        hotel/reservation.h hotel/reservation.cpp)
