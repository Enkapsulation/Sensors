cmake_minimum_required(VERSION 3.10)
project(Sensors)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compile flags 
set(CMAKE_CXX_FLAGS " ")

# Definitions
# add_definitions(-D_DEBUG_FLAG)

# main file
set(MAIN ${CMAKE_SOURCE_DIR}/src/pir.cpp)

#shared module dir
set(SHARED_MODULE_DIR $(CMAKE_SOURCE_DIR)/shared_folder)

#SensorInterface
set(SENSOR_INTERFACE_DIR ${SHARED_MODULE_DIR}/sensor_interface)
set(SENSOR_INTERFACE ${SENSOR_INTERFACE_DIR}/sensor_interface.hpp)

#PIRClass
set(PIR_CLASS_DIR ${CMAKE_SOURCE_DIR}/src/pir_class)
set(PIR_CLASS ${PIR_CLASS_DIR}/PIRClass.hpp ${PIR_CLASS_DIR}/PIRClass.cpp)

#dbg_trace
set(DBG_TRACE_DIR ${CMAKE_SOURCE_DIR}/shared_folder/dbg_trace)
set(DEBUG_TRACE ${DBG_TRACE_DIR}/dbg_trace.hpp ${DBG_TRACE_DIR}/dbg_trace.cpp ${DBG_TRACE_DIR}/dbg_trace_types.hpp)

# add the executable
add_executable(${CMAKE_PROJECT_NAME} ${MAIN} ${SENSOR_INTERFACE} ${PIR_CLASS} ${DEBUG_TRACE})

# Static library
target_link_libraries(${CMAKE_PROJECT_NAME} wiringPi)

# Directories
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
									"${SENSOR_CLASS_DIR}"
									"${DBG_TRACE_DIR}"
									)
