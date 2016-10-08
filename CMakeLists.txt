cmake_minimum_required(VERSION 3.0)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

SET(_warnings "-Wall -Wextra -Wno-long-long -Wformat-security -Wno-strict-aliasing")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_warnings}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_warnings}")

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

IF (CMAKE_BUILD_TYPE STREQUAL "Coverage" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
	IF(CMAKE_COMPILER_IS_GNUCXX)
		include(CodeCoverage)

		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_COVERAGE}")
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_COVERAGE}")
		SET(EXCLUDE_FROM_COVERAGE "components/Tests/* /usr/* qrc_*.cpp moc_*.cpp")

		setup_target_for_coverage(coverage tests coverage ${EXCLUDE_FROM_COVERAGE})
	ENDIF()
ENDIF()

set(COMPONENTS_DIR components)
# Add internal libraries
add_subdirectory(${COMPONENTS_DIR}/Utils)
add_subdirectory(${COMPONENTS_DIR}/Cli)
add_subdirectory(${COMPONENTS_DIR}/Git)

# Add executable
add_subdirectory(${COMPONENTS_DIR}/Ui)
add_subdirectory(${COMPONENTS_DIR}/Review)

# Add tests
add_subdirectory(${COMPONENTS_DIR}/Tests)
