#
# Copyright (C) 2020-2023 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)

add_definitions(-DDOCTOR_PILL_LIBRARY)

file(GLOB SOURCE_CPP
    "*.cpp"
    "DoctorPillCore/*.cpp"
    "*.h"
    "DoctorPillCore/*.h"
)

set(ALL_SOURCES ${SOURCE_CPP})

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

add_library(${PROJECT_NAME} ${ALL_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core )

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_INCUDE_DIR})

set(global_file "${CMAKE_CURRENT_SOURCE_DIR}/doctorpill_global.h")
configure_file("${global_file}.in" ${global_file} @ONLY)
