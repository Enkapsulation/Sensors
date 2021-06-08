cmake_minimum_required(VERSION 3.10)
project(Sensors)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compile flags 
set(CMAKE_CXX_FLAGS " ")

# Definitions
# add_definitions(-D_DEBUG_FLAG)

# main file
set(MAIN ${CMAKE_SOURCE_DIR}/src/pir.cpp)

set(SHARED_MODULE_DIR ${CMAKE_SOURCE_DIR}/shared_folder)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

#SensorInterface
set(SENSOR_INTERFACE_DIR ${SHARED_MODULE_DIR}/sensor_interface)
set(SENSOR_INTERFACE ${SENSOR_INTERFACE_DIR}/sensor_interface.hpp)

#pir_driver
set(PIR_DRIVER_DIR ${SOURCE_DIR}/pir_driver)
set(PIR_DRIVER ${PIR_DRIVER_DIR}/pir_driver.hpp ${PIR_DRIVER_DIR}/pir_driver.cpp)

#dbg_trace
set(DBG_TRACE_DIR ${SHARED_MODULE_DIR}/dbg_trace)
set(DEBUG_TRACE ${DBG_TRACE_DIR}/dbg_trace.hpp ${DBG_TRACE_DIR}/dbg_trace.cpp ${DBG_TRACE_DIR}/dbg_trace_types.hpp)

#mqtt
set(MQTT_DIR ${SOURCE_DIR}/MQTT)
set(MQTT ${MQTT_DIR}/mqtt.hpp ${MQTT_DIR}/mqtt.cpp)

#mqtt library
find_library(paho-mqttpp3 NAMES libpaho-mqttpp3.a REQUIRED)
find_library(paho-mqtt3a NAMES libpaho-mqtt3a.so REQUIRED)

add_library(pahottpp STATIC IMPORTED)
set_target_properties(pahottpp PROPERTIES IMPORTED_LOCATION ${paho-mqttpp3})

add_library(pahomqtt3a SHARED IMPORTED)
set_property(TARGET pahomqtt3a PROPERTY IMPORTED_LOCATION ${paho-mqtt3a})

# add the executable
add_executable(${CMAKE_PROJECT_NAME} ${MAIN} ${DEBUG_TRACE} ${SENSOR_INTERFACE} ${MQTT} ${PIR_DRIVER})

# Static library
target_link_libraries(${CMAKE_PROJECT_NAME} wiringPi pahottpp pahomqtt3a)

# Directories
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
									"${PIR_DRIVER_DIR}"
									"${DBG_TRACE_DIR}"
									"${SENSOR_INTERFACE_DIR}"
									"${MQTT}"
									)
