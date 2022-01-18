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


if (NOT QT_VERSION_MAJOR)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
endif()
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

include(submodules/CMake/QuasarApp.cmake)

updateGitVars()
set(DOCTOR_PILL_VERSION "0.${GIT_COMMIT_COUNT}.${GIT_COMMIT_HASH}")

option(DOCTOR_PILL_GUI "Enable gui qml model for build" ON)
option(DOCTOR_PILL_TESTS "Enable tests of this library" ON)
option(DOCTOR_PILL_EXAMPLE "Enable example app of this library" ON)

SET(TARGET_DIR "${CMAKE_SOURCE_DIR}/Distro")
file(MAKE_DIRECTORY ${TARGET_DIR})

if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
    if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
        message("This library depend of the qt concurent library, but The concurent is not available in qt wasm")
        initAll()
        return()
    endif()
endif()

if (ANDROID OR IOS)
    set(DOCTOR_PILL_TESTS OFF)
    set(DOCTOR_PILL_EXAMPLE OFF)
    message("Disable DOCTOR_PILL_TESTS and DOCTOR_PILL_EXAMPLE for mobile paltforms because ios and android not support tests and an example.")

endif()


initAll()

if (DOCTOR_PILL_GUI)
    add_definitions(-DDOCTOR_PILL_GUI)
else()
    set(DOCTOR_PILL_EXAMPLE OFF)
endif()

add_subdirectory(src/Library)

if (DOCTOR_PILL_EXAMPLE)
    add_subdirectory(src/Example)
endif()

if (DOCTOR_PILL_TESTS)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled.")
endif()


addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
addDeployFromCustomFile("DoctorPill" "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/DoctorPill.json")
