#=======================================
#                PROJECT                
#=======================================

cmake_minimum_required(VERSION 3.8)
project("LIBUSBNGINE")

#=======================================
#                 INIT                 
#======================================= 

#---------------------------------------
#               VARIABLES               
#---------------------------------------

set(LIBUSBNGINE_SRC_DIR "src")
set(LIBUSBNGINE_HEADER_DIR "include")
set(LIBUSBNGINE_PROJECT_NAME "libusbngine")

#---------------------------------------
#                 FILES                 
#---------------------------------------

file(GLOB_RECURSE LIBUSBNGINE_src_files ${LIBUSBNGINE_SRC_DIR}/*)
file(GLOB_RECURSE LIBUSBNGINE_header_files ${LIBUSBNGINE_HEADER_DIR}/*)

#---------------------------------------
#                 CONAN                 
#---------------------------------------

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#=======================================
#                CREATE                
#=======================================

#---------------------------------------
#                PROJECT                
#---------------------------------------

add_executable(${LIBUSBNGINE_PROJECT_NAME}  ${LIBUSBNGINE_src_files} ${LIBUSBNGINE_header_files})
target_include_directories(${LIBUSBNGINE_PROJECT_NAME} PRIVATE ${LIBUSBNGINE_HEADER_DIR})

#--------------------------------------- 
#              PROPERTIES              
#---------------------------------------

set_target_properties(${LIBUSBNGINE_PROJECT_NAME} PROPERTIES
                        CXX_STANDARD 14
                        CXX_STANDARD_REQUIRED ON
                        CXX_EXTENSIONS OFF)

#---------------------------------------
#                 CONAN                 
#---------------------------------------

target_link_libraries(${LIBUSBNGINE_PROJECT_NAME} ${CONAN_LIBS})
