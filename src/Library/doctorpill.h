//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef DOCTOR_PILL_H
#define DOCTOR_PILL_H

#include "DoctorPillCore/doctor.h"
#include "DoctorPillCore/doctortest.h"

#ifdef DOCTOR_PILL_GUI

#include "DoctorPillGui/doctormodel.h"

inline void initDoctorPillResources() {
    Q_INIT_RESOURCE(DoctorPillRes);
}

class QQmlApplicationEngine;
#endif

/**
 * @brief DP This is base name space of the DoctorPill(DP) library. Please if you use the gui application and gui models then invoke the DP::init method before use this library.
 */
namespace DP {

#ifdef DOCTOR_PILL_GUI
/**
     * @brief init This function initialize the qml gui classes of the DoctorPill library.
     * @note if you do not use GUI then this function do nothing.
     * @param engine This is qml engine pointer if this pointer is invalid then finction return false.
     * @return return true if the library initialized successful else false.
     *
     * @see DoctorModel
     */
    bool DOCTOR_PILL_EXPORT init(QQmlApplicationEngine *engine);
#else
/**
     * @brief init This function is empty wrapper for non gui build
     * @return always return true.
     *
     * @see DoctorModel
     */
    bool DOCTOR_PILL_EXPORT init();
#endif

    /**
     * @brief version This method return string value of lib version
     * @return string value of lib version.
     */
    QString version();
}

#endif // DOCTOR_PILL_H
