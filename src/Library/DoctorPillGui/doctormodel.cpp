//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "doctormodel.h"
#include <QHash>

namespace DP {

DoctorModel::DoctorModel(const QList<QSharedPointer<iPill>> &base):
    _doctor(base)
{

}

int DoctorModel::rowCount(const QModelIndex &) const {
    return _viewData.count();
}

QVariant DoctorModel::data(const QModelIndex &index, int role) const {

    if (index.row() < 0 || index.row() >= rowCount()) {
        return "";
    }

    Issue item = *std::next(_viewData.begin(), index.row());

    if (!item._pill) {
        return "Internal Error";
    }

    if (role == Roles::Name) {
        return item._pill->name();
    }

    if (role == Roles::Description) {
        return item._pill->description();
    }

    if (role == Roles::Status) {
        return item._status;
    }

    return "Unknown";
}

QHash<int, QByteArray> DoctorModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[Roles::Name] = "issueName";
    roles[Roles::Description] = "issueDescription";
    roles[Roles::Status] = "issueStatus";

    return roles;
}

void DoctorModel::usePill(QString pillName) {

    auto pill = _viewData.value(pillName, {});
    if (!pill._pill)
        return;

    _doctor.fix({pill._pill});
}

void DoctorModel::diagnostic() {
    _doctor.diagnostic();
}

void DoctorModel::handleFixFailed(QList<QSharedPointer<iPill>> failed) {

    for (const auto &pill : qAsConst(failed)) {
        _viewData[pill->name()]._status = static_cast<int>(IssueStatus::Failed);
    }
}

void DoctorModel::handleFixSuccessful(QList<QSharedPointer<iPill>> successful) {

    for (const auto &pill : qAsConst(successful)) {
        _viewData[pill->name()]._status = static_cast<int>(IssueStatus::Solved);
    }
}

void DoctorModel::handleBugDetected(QList<QSharedPointer<iPill>> bugDetected) {

    beginResetModel();

    _viewData.clear();
    for (const auto &pill : qAsConst(bugDetected)) {
        _viewData[pill->name()] = Issue{0, pill};
    }

    endResetModel();
}
}
