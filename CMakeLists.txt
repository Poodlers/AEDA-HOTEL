cmake_minimum_required(VERSION 3.10)
project(aeda_hotel_projeto)

set(CMAKE_CXX_STANDARD 11)

add_executable(main.cpp product/product.cpp exceptions/exceptions.h hotel/hotel.h hotel/hotel.cpp provider/provider.h provider/provider.cpp)
