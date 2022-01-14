#
# Copyright (C) 2020-2022 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)
project(DoctorPill LANGUAGES CXX)
if(TARGET ${PROJECT_NAME})
  message("The ${PROJECT_NAME} arledy included in main Project")
  return()
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (ANDROID OR IOS)
    set(BUILD_SHARED_LIBS ON)
endif()

if (NOT QT_VERSION_MAJOR)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Test QUIET)
endif()
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test QUIET)

include(submodules/CMake/QuasarApp.cmake)

updateGitVars()
set(DoctorPill_VERSION "0.${GIT_COMMIT_COUNT}.${GIT_COMMIT_HASH}")

option(DOCTOR_PILL_GUI "Enable gui qml model for build" OFF)

if (NOT DEFINED DOCTOR_PILL_TESTS)
    set(DOCTOR_PILL_TESTS ON)

    if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
        if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
            set(DOCTOR_PILL_TESTS OFF)
            set(DOCTOR_EXAMPLE_TESTS OFF)
        endif()
    endif()

    if (ANDROID OR IOS)
        set(DOCTOR_PILL_TESTS OFF)
        set(DOCTOR_EXAMPLE_TESTS OFF)
    endif()

endif()

if (NOT DEFINED DOCTOR_EXAMPLE_TESTS)
    set(DOCTOR_EXAMPLE_TESTS ON)

    if (NOT QT_VERSION_MAJOR)
        set(DOCTOR_EXAMPLE_TESTS OFF)
    endif()
endif()

initAll()

add_subdirectory(src/Library)

if (DEFINED DOCTOR_EXAMPLE_TESTS)
    add_subdirectory(src/Example)
endif()

if (DOCTOR_PILL_TESTS)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled.")
endif()


addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
addDeployFromCustomFile("DoctorPill" "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/DoctorPill.json")
