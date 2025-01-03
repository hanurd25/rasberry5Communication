cmake_minimum_required(VERSION 3.20)
project(TeensySerialCommunication CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(commTest main.cpp)

target_link_libraries(commTest PRIVATE pthread)
