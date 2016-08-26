cmake_minimum_required(VERSION 3.0)

project(review CXX)
set(CMAKE_CXX_STANDARD 14)
include_directories(${Cli_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_SOURCE_DIR}/include)


find_package(Qt5 COMPONENTS Widgets Quick REQUIRED)
qt5_add_resources(RESOURCES ${Ui_RESOURCES})
qt5_wrap_cpp(review_moc include/ReviewHandler.h)

file(GLOB HEADER_FILES include/*.h)
file(GLOB CPP_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${CPP_FILES} ${HEADER_FILES} ${review_moc} ${RESOURCES})
qt5_use_modules(${PROJECT_NAME} Widgets)
target_link_libraries(${PROJECT_NAME} Cli Qt5::Widgets Qt5::Quick)
