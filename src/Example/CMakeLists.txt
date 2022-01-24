#
# Copyright (C) 2021-2022 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)

set(CURRENT_PROJECT "${PROJECT_NAME}Eaxample")

file(GLOB SOURCE_CPP
    "*.cpp"
     "Private/*.cpp"
     "*.qrc"
     "Private/*.qrc"
)

if (${QT_VERSION_MAJOR} EQUAL 6)

    qt_add_executable(${CURRENT_PROJECT} MANUAL_FINALIZATION ${SOURCE_CPP})

else()
    if (ANDROID)
        add_library(${CURRENT_PROJECT} ${SOURCE_CPP})
    else ()
        add_executable(${CURRENT_PROJECT} ${SOURCE_CPP} )
    endif()

endif()

target_link_libraries(${CURRENT_PROJECT} PUBLIC ${PROJECT_NAME}GUI)
target_include_directories(${CURRENT_PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(QT_VERSION_MAJOR EQUAL 6)
    # Add This line if your project use the Quick module
    # qt_import_qml_plugins(${CURRENT_PROJECT})
    qt_finalize_executable(${CURRENT_PROJECT})
endif()


addDeployFromCustomFile("DoctorPill" "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/DoctorPill.json")

