cmake_minimum_required(VERSION 3.0)

project(review CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(${PROJECT_NAME}_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include CACHE STRING "Review include directory")

include_directories(${review_INCLUDE_DIR}
					${Utils_INCLUDE_DIR}
					${Git_INCLUDE_DIR})


find_package(Qt5 COMPONENTS Widgets Quick REQUIRED)
qt5_add_resources(RESOURCES ${Ui_RESOURCES})

file(GLOB HEADER_FILES include/Review/*.h)
list(REMOVE_ITEM HEADER_FILES ${PROJECT_SOURCE_DIR}/include/Review/Defs.h)
file(GLOB CPP_FILES src/*.cpp)

qt5_wrap_cpp(review_moc ${HEADER_FILES})

add_executable(${PROJECT_NAME} ${CPP_FILES} ${HEADER_FILES} ${review_moc} ${RESOURCES})
qt5_use_modules(${PROJECT_NAME} Widgets Qml)
target_link_libraries(${PROJECT_NAME} Utils Git Qt5::Widgets Qt5::Quick)
