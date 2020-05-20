#=======================================
#                PROJECT                
#=======================================

cmake_minimum_required(VERSION 3.8)
project("LIBUSBNGINE" VERSION 0.1 LANGUAGES CXX)

#=======================================
#                CONAN                
#=======================================

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

#=======================================
#               EXECUTABLE              
#======================================= 

set(
	LIBUSBNGINE_HEADER_FILES
	)

add_executable(
	${PROJECT_NAME}
	src/main.cpp
	)

target_include_directories(
	${PROJECT_NAME} 
	PRIVATE ${LIBUSBNGINE_HEADER_FILES}
	)

#=======================================
#                SETTINGS               
#=======================================

set_target_properties(
	${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    )

#=======================================
#                PACKAGE                
#=======================================

target_link_libraries(${PROJECT_NAME} CONAN_PKG::libusb)


#=======================================
#                INSTALL                
#=======================================

set(LIBUSBNGINE_RUNTIME_DESTINATION "bin")

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${LIBUSBNGINE_RUNTIME_DESTINATION}
	)