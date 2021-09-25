#=======================================
#                PROJECT
#=======================================

cmake_minimum_required(VERSION 3.0)
project("LIBUSBNGINE" CXX)

#=======================================
#               LIBRARIES
#=======================================

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package("LibUSB" REQUIRED)

#=======================================
#              EXECUTABLE
#=======================================

set(libusbngine_src
    libusbngine/main.cpp)

add_executable(libusbngine ${libusbngine_src})
set_target_properties(libusbngine PROPERTIES CXX_STANDARD 14)
target_link_libraries(libusbngine PRIVATE LibUSB::LibUSB)
