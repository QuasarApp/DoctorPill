//#
//# Copyright (C) 2021-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef DOCTOR_PILL_H
#define DOCTOR_PILL_H

#include "DoctorPillCore/doctor.h"
#include "DoctorPillCore/doctortest.h"

/**
 * @brief DP This is base name space of the DoctorPill(DP) library. Please if you use the gui application and gui models then invoke the DP::init method before use this library.
 */
namespace DP {

    /**
     * @brief version This method return string value of lib version
     * @return string value of lib version.
     */
    QString DOCTOR_PILL_EXPORT version();
}

#endif // DOCTOR_PILL_H
