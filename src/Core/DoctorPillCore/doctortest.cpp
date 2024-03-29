/*
 * Copyright (C) 2018-2024 QuasarApp.
 * Distributed under the GPLv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "doctortest.h"
#include "ipill.h"

namespace DP {

DoctorTest::DoctorTest() {
}

bool DoctorTest::test(const QSharedPointer<iPill> &pill,
                      bool appIsBroken) const {

    if (pill->diagnostic() != appIsBroken) {
        return false;
    }

    if (appIsBroken && !pill->fix()) {
        return false;
    }

    return !pill->diagnostic();
}

}
