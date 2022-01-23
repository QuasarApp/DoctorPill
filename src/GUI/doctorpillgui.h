//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef DOCTOR_PILL_GUI_H
#define DOCTOR_PILL_GUI_H

#include "DoctorPillCore/doctor.h"
#include "DoctorPillCore/doctortest.h"

#include "DoctorPillGui/doctormodel.h"

inline void initDoctorPillResources() {
    Q_INIT_RESOURCE(DoctorPillRes);
}

class QQmlApplicationEngine;

namespace DP {

/**
     * @brief init This function initialize the qml gui classes of the DoctorPill library.
     * @note if you do not use GUI then this function do nothing.
     * @param engine This is qml engine pointer if this pointer is invalid then finction return false.
     * @return return true if the library initialized successful else false.
     *
     * @see DoctorModel
     */
    bool DOCTOR_PILL_GUI_EXPORT init(QQmlApplicationEngine *engine);
}

#endif // DOCTOR_PILL_GUI_H
