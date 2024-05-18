cmake_minimum_required(VERSION 3.10)
project(Test)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
add_subdirectory(googletest-release-1.12.1)
add_executable(Test test.cpp ../headers/Club.h ../headers/Event.h ../headers/Person.h ../headers/Time.h ../include/Club.cpp ../include/Event.cpp ../include/Person.cpp ../include/Time.cpp)
target_link_libraries(Test gtest_main gmock_main)