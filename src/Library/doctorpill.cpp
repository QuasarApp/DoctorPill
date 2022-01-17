//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "doctorpill.h"
#ifdef DOCTOR_PILL_GUI
#include <QQmlApplicationEngine>
#endif
namespace DP {

#ifdef DOCTOR_PILL_GUI
bool init(QQmlApplicationEngine *engine) {

    if (!engine)
        return false;

    auto root = engine->rootContext();
    if (!root)
        return false;

    initDoctorPillResources();

    engine->addImportPath(":/");

    return true;
}
#else
bool init() {
    return true;
}

#endif
}
