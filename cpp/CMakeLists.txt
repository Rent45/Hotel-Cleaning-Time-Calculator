cmake_minimum_required(VERSION 3.29)
project(lab_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(oop_classical_pointers main.cpp
  constants.h
  apartment.h
  menu.cpp
  main.cpp
  menu.h
  hotel.cpp
  hotel.h
  multapartment.h
  singlapartment.h
  hotelrepository.cpp
  hotelrepository.h
)