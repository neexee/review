cmake_minimum_required(VERSION 3.0)

project(Review CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(${PROJECT_NAME}_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include CACHE STRING "Review include directory")

include_directories(${Review_INCLUDE_DIR}
					${Cli_INCLUDE_DIR}
					${Utils_INCLUDE_DIR}
					${Git_INCLUDE_DIR})

find_package(Qt5 COMPONENTS Widgets Quick REQUIRED)

file(GLOB HEADER_FILES include/Review/*.h)

set(QT_WRAP_EXCEPTIONS Defs.h Application.h)
foreach(header IN ITEMS ${QT_WRAP_EXCEPTIONS})
	list(REMOVE_ITEM HEADER_FILES ${PROJECT_SOURCE_DIR}/include/Review/${header})
endforeach(header)

file(GLOB CPP_FILES src/*.cpp)
list(REMOVE_ITEM CPP_FILES src/main.cpp)

qt5_wrap_cpp(review_moc ${HEADER_FILES})

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HEADER_FILES} ${review_moc})

add_dependencies(${PROJECT_NAME} Utils Cli Git)

qt5_use_modules(${PROJECT_NAME} Widgets Qml)
target_link_libraries(${PROJECT_NAME} Cli Git Utils Qt5::Widgets Qt5::Quick)

qt5_add_resources(RESOURCES ${Ui_RESOURCES})
add_executable(review src/main.cpp ${RESOURCES})
target_link_libraries(review Review)
