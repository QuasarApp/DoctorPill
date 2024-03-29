/*
 * Copyright (C) 2018-2024 QuasarApp.
 * Distributed under the GPLv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef DOCTOR_H
#define DOCTOR_H

#include "ipill.h"
#include <QObject>
#include <QSharedPointer>

namespace DP {

/**
 * @brief The Doctor class is class that execute pills objects.
 *  The Doctor check issue that will be executed and if the issue realy then execute fix.
 * @warning This is dangerous system because you may create bug in pill and doctor that will execute this pill may broke users app.
 * @see iPill
 */
class DOCTOR_PILL_EXPORT Doctor: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Doctor This is base contructor of doctor calss.
     * @param base This is list of known issues.
     */
    Doctor(const QList<QSharedPointer<iPill>> &base);

    /**
     * @brief diagnostic This method run full diagnostic of this application.
     *  If the @a fix is true then doctor try fix the foundet issues.
     *  If the @a fix value if false then the Doctor emit the sigTroubleDetected signal.
     * @param fix set this argument to tru if you want fix all foundet issues.
     * @see Doctor::fix
     * @see Doctor::addPill
     * @see Doctor::sigFixesFailed
     * @see Doctor::sigFixesFinishedSuccessful
     * @see Doctor::sigDiagnosticFinished
    */
    void diagnostic(bool fix = false);

    /**
     * @brief fix This method try run fixes by input pills.
     * @note All fixes will be checked before execute fix.
     * @param pills This is list of fixes that will be executed.
     * @see Doctor::diagnostic
     * @see Doctor::addPill
     * @see Doctor::sigFixesFailed
     * @see Doctor::sigFixesFinishedSuccessful
     */
    void fix(const QList<QSharedPointer<iPill>>& pills);

    /**
     * @brief addPill This method add new pill object to doctor library
     * @param pill This is pill object.
     * @see Doctor::diagnostic
     * @see Doctor::fix
     * @see Doctor::sigFixesFailed
     * @see Doctor::sigFixesFinishedSuccessful
     */
    void addPill(const QSharedPointer<iPill>& pill);
signals:
    /**
     * @brief sigDiagnosticFinished This signal will emited when The doctor object found issues in this application.
     * @param issues this is list of detected issues.
     * @see Doctor::diagnostic
     * @see Doctor::fix
     * @see Doctor::sigFixesFailed
     * @see Doctor::sigFixesFinishedSuccessful
     */
    void sigDiagnosticFinished(QList<QSharedPointer<DP::iPill>> issues);

    /**
     * @brief sigFixesFailed This signal emited when the doctor can't fix foundet issues.
     * @param issues This is list of the unfixable issues.
     */
    void sigFixesFailed(QList<QSharedPointer<DP::iPill>> issues);

    /**
     * @brief sigFixesFinishedSuccessful This signal emited when the doctor fix foundet issues successfull.
     * @param issues This is list of the fixed issues.
     */
    void sigFixesFinishedSuccessful(QList<QSharedPointer<DP::iPill>> issues);

    /**
     * @brief sigDiagnosticProgressChanged This signal emitted when progress of diagnstic changed.
     * @param progress This is ptogress of diagnostic process from 0 to 1
     */
    void sigDiagnosticProgressChanged(float progress);
private:
    QList<QSharedPointer<iPill>> _pillsData;
};


}

#endif // DOCTOR_H
