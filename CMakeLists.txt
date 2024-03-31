cmake_minimum_required(VERSION 3.26)
project(image_edit)

set(CMAKE_CXX_STANDARD 14)

add_executable(image_edit
        src/main.cpp
        src/bmp.h
        src/bmp.cpp
        src/BMPProcess.h
        src/rgb.cpp
        src/correlation.cpp
        src/ycbcr.cpp)
