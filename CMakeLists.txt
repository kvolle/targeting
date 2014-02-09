cmake_minimum_required(VERSION 2.6)

#Name your project here
project(target)

#This tells CMake to fib.c and name it fibonacci
 #add_executable(target src/target.cpp)
 #add_executable(vehicle src/vehicle.cpp)
 add_executable(main src/main.cpp src/target.cpp src/vehicle.cpp)
