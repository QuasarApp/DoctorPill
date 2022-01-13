#
# Copyright (C) 2020-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
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
set(DoctorPill_PACKAGE_ID "quasarapp.core.DoctorPill")

if (NOT DEFINED DoctorPill_TESTS)
    set(DoctorPill_TESTS ON)

    if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
        if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
            set(DoctorPill_TESTS OFF)
        endif()
    endif()

    if (ANDROID OR IOS)
        set(DoctorPill_TESTS OFF)
    endif()

    if (NOT QT_VERSION_MAJOR)
        set(DoctorPill_TESTS OFF)
    endif()
endif()

if (NOT DEFINED DoctorPill_EXAMPLE)
    set(DoctorPill_EXAMPLE ON)

    if (NOT QT_VERSION_MAJOR)
        set(DoctorPill_EXAMPLE OFF)
    endif()
endif()

initAll()

updateGitVars()
set(DOCTOR_PILL_VERSION "0.${GIT_COMMIT_COUNT}.${GIT_COMMIT_HASH}")

add_subdirectory(src/Library)

if (DEFINED DoctorPill_EXAMPLE)
    add_subdirectory(src/Example)
endif()

if (DoctorPill_TESTS)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled.")
endif()


addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
addDeployFromCustomFile("DoctorPill" "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/DoctorPill.json")
