/*
 * Copyright (C) 2018-2023 QuasarApp.
 * Distributed under the GPLv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/


#ifndef IPILL_H
#define IPILL_H

#include <QString>
#include "doctorpill_global.h"
#include <QMetaType>
#include <QSharedPointer>

namespace DP {

/**
 * @brief The iPill class is base interface for the pill object.
 * The Pill object is independet tool that must be fix one issue for runned application.
 *
 * ## For Example:
 *
 * You has a sume bug, but you don't known about this bug.
 *  This big broken the database for your users, but you still don't known about this.
 * You found this bug and create new patch for fix it, but databae of your users alredy broken, and you users can't fix this issues yasterself.
 *  So you can create a pill for fix broked database and delive to your users for fix thes issue.
 *
 * The Pill object structure should be has:
 * * The Action that should be check if contains this issue or not ...
 * * The Action taht should be fix issue.
 * * Description of the issue.
 * * Name of the issue.
 *
 * * @see iPill
 */
class DOCTOR_PILL_EXPORT iPill
{
public:
    iPill();

    /**
     * @brief id This method return unique id of this pill object.
     * @return unique id of this pill object.
     */
    virtual int id() const = 0;

    /**
     * @brief name This method should be return name of this pill.
     * @note for get id use the @a iPill::id method.
     * @return name of this pill.
     * @see iPill::id
     */
    virtual QString name() const = 0;

    /**
     * @brief description This method should be return dital description of the issue that this pill will fix after execute (accept).
     * @return string valeu with description.
     */
    virtual QString description() const = 0;

protected:

    /**
     * @brief diagnostic This method execute action that should be check if exits issues or not.
     * @note This method will executed only on the Doctor object.
     * @return true if the issues is detected.
     */
    virtual bool diagnostic() = 0;

    /**
     * @brief fix This method should be fix detected issue.
     * @return true if the issue fixes successful else false
     */
    virtual bool fix() = 0;


    friend class Doctor;
    friend class DoctorTest;
};


}

Q_DECLARE_METATYPE(QSharedPointer<DP::iPill>);

#endif // IPILL_H
