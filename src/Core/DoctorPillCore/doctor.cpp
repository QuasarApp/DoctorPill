/*
 * Copyright (C) 2018-2023 QuasarApp.
 * Distributed under the GPLv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "ipill.h"

#include "doctor.h"

namespace DP {

Doctor::Doctor(const QList<QSharedPointer<iPill> > &base) {
    _pillsData = base;

    qRegisterMetaType<QList<QSharedPointer<iPill> >>();
}

void Doctor::diagnostic(bool fix) {

    QList<QSharedPointer<iPill> > failed;
    QList<QSharedPointer<iPill> > detected;
    QList<QSharedPointer<iPill> > fixedSuccessful;

    float progress = 0;
    float progressStep = 1.0f / _pillsData.size();

    emit sigDiagnosticProgressChanged(progress);
    for (const auto &pill: _pillsData) {
        if (pill->diagnostic()) {
            if (fix) {
                if (!pill->fix()) {
                    failed.push_back(pill);
                } else {
                    fixedSuccessful.push_back(pill);
                }
            } else {
                detected.push_back(pill);
            }
        }

        progress += progressStep;
        emit sigDiagnosticProgressChanged(progress);
    }

    if (failed.size()) {
        emit sigFixesFailed(failed);
    }

    emit sigDiagnosticFinished(detected);

    if (fixedSuccessful.count()) {
        emit sigFixesFinishedSuccessful(fixedSuccessful);
    }
}

void Doctor::fix(const QList<QSharedPointer<iPill> > &pills) {

    QList<QSharedPointer<iPill> > failed;
    QList<QSharedPointer<iPill> > fixedSuccessful;

    for (const auto &pill: pills) {
        if (pill->diagnostic()) {
            if (!pill->fix()) {
                failed.push_back(pill);
            } else {
                fixedSuccessful.push_back(pill);
            }
        }
    }

    if (failed.size()) {
        emit sigFixesFailed(failed);
    }

    if (fixedSuccessful.count()) {
        emit sigFixesFinishedSuccessful(fixedSuccessful);
    }
}

void Doctor::addPill(const QSharedPointer<iPill> &pill) {
    _pillsData.push_back(pill);
}

}
