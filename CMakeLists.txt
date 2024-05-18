cmake_minimum_required(VERSION 3.10)
project(ComputerClub)

set(CMAKE_CXX_STANDARD 20)
include_directories("headers/")

add_executable(Program main.cpp headers/Club.h headers/Event.h headers/Person.h headers/Time.h include/Club.cpp include/Event.cpp include/Person.cpp include/Time.cpp)
