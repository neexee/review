cmake_minimum_required(VERSION 3.0)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

SET(_warnings "-Wall -Wextra -Wno-long-long -Wformat-security -Wno-strict-aliasing")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_warnings}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_warnings}")

set(COMPONENTS_DIR components)
# Add internal libraries
add_subdirectory(${COMPONENTS_DIR}/Utils)
add_subdirectory(${COMPONENTS_DIR}/Git)
add_subdirectory(${COMPONENTS_DIR}/CLI)

# Add executable
add_subdirectory(${COMPONENTS_DIR}/Review)
