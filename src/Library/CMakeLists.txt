#
# Copyright (C) 2020-2022 QuasarApp.
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

if (DOCTOR_PILL_GUI)
    file(GLOB SOURCE_CPP_GUI
        "DoctorPillGui/*.cpp"
        "DoctorPillGui/*.h"

    )

    file(GLOB SOURCE_QRC
        "*.qrc"
        "DoctorPillCore/*.qrc"
    )

endif()

set(ALL_SOURCES ${SOURCE_CPP} ${SOURCE_QRC} ${SOURCE_CPP_GUI})

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

add_library(${PROJECT_NAME} ${ALL_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core )

set(DOCTOR_PILL_DEFINE "DOCTOR_PILL_WITHOUT_GUI")
if (DOCTOR_PILL_GUI)
    set(DOCTOR_PILL_DEFINE "DOCTOR_PILL_WITH_GUI")

    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Quick Concurrent REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Concurrent Qt${QT_VERSION_MAJOR}::Quick )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_INCUDE_DIR})


set(LANGS ${CMAKE_CURRENT_SOURCE_DIR}/languages/en.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ru.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/uk.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ja.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/tr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/zh.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/de.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/fr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/es.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/pl.ts)

prepareQM(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../ "${LANGS}")

set(QML_IMPORT_PATH ${QML_IMPORT_PATH} "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "" FORCE)

set(global_file "${CMAKE_CURRENT_SOURCE_DIR}/doctorpill_global.h")
configure_file("${global_file}.in" ${global_file} @ONLY)
