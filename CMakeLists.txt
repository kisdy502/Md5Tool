cmake_minimum_required(VERSION 3.8)
project(Md5Tool)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp md5global.h md5.h md5.cpp md5file.h md5file.cpp)
add_executable(Md5Tool ${SOURCE_FILES})