cmake_minimum_required(VERSION 3.0)

project(Utils CXX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

file(GLOB HEADER_FILES include/*.h)
file(GLOB CPP_FILES src/*.cpp)

# It's header-only library. For now.
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${HEADER_FILES})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_variadic_templates)
target_link_libraries(${PROJECT_NAME})
