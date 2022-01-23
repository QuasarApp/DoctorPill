//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "doctorpillgui.h"
#include <QQmlApplicationEngine>

namespace DP {

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

}
