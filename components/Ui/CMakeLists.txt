cmake_minimum_required(VERSION 3.0)

project(Ui)

file(GLOB RESOURCES *.qrc)

set(${PROJECT_NAME}_RESOURCES ${RESOURCES}
        CACHE INTERNAL "${PROJECT_NAME}: Resources" FORCE)
