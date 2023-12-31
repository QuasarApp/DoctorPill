//#
//# Copyright (C) 2021-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "doctormodel.h"
#include <QHash>
#include <QtConcurrent>

namespace DP {

DoctorModel::DoctorModel(const QList<QSharedPointer<iPill>> &base):
    _doctor(base)
{
    connect(&_doctor, &Doctor::sigDiagnosticFinished,
           this, &DoctorModel::handleDiagnostcFinished,
           Qt::QueuedConnection);

    connect(&_doctor, &Doctor::sigDiagnosticProgressChanged,
           this, &DoctorModel::handleDiagnosticProgressChanged,
           Qt::QueuedConnection);

    connect(&_doctor, &Doctor::sigFixesFailed,
           this, &DoctorModel::handleFixFailed,
           Qt::QueuedConnection);

    connect(&_doctor, &Doctor::sigFixesFinishedSuccessful,
           this, &DoctorModel::handleFixSuccessful,
           Qt::QueuedConnection);

    setState(ViewState::BeginDiagnostic);
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

    if ( role == Roles::Id) {
        return item._pill->id();
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
    roles[Roles::Id] = "id";

    return roles;
}

void DoctorModel::usePill(int pillName) {

    auto work = [this, pillName](){
        auto pill = _viewData.value(pillName, {});
        if (!pill._pill)
            return;

        _doctor.fix({pill._pill});
    };

    auto val = QtConcurrent::run(work);
}

void DoctorModel::diagnostic() {

    auto work = [this](){
        _doctor.diagnostic();
    };

    setState(ViewState::SearchBugs);

    auto val = QtConcurrent::run(work);
}

void DoctorModel::drop(int id) {

    auto iter = _viewData.find(id);

    if (iter == _viewData.end())
        return;

    int row = std::distance(_viewData.begin(), iter);

    beginRemoveRows(QModelIndex{}, row, row);
    _viewData.erase(std::next(_viewData.begin(), row));
    endRemoveRows();

    if (!_viewData.size()) {
        setState(ViewState::AllIsFine);
    }
}

void DoctorModel::handleFixFailed(QList<QSharedPointer<iPill>> failed) {


    for (const auto &pill : qAsConst(failed)) {
        _viewData[pill->id()]._status = static_cast<int>(IssueStatus::Failed);
    }

    emit dataChanged(index(0,0), index(rowCount() - 1, 0),
                     QVector<int>() << Roles::Status);

}

void DoctorModel::handleFixSuccessful(QList<QSharedPointer<iPill>> successful) {


    for (const auto &pill : qAsConst(successful)) {
        _viewData[pill->id()]._status = static_cast<int>(IssueStatus::Solved);
    }

    emit dataChanged(index(0,0), index(rowCount() - 1, 0),
                     QVector<int>() << Roles::Status);
}

void DoctorModel::handleDiagnostcFinished(QList<QSharedPointer<iPill> > issues) {
    beginResetModel();

    _viewData.clear();
    for (const auto &pill : qAsConst(issues)) {
        _viewData[pill->id()] = Issue{0, pill};
    }

    endResetModel();

    if (_viewData.size())
        setState(ViewState::BugFound);
    else
        setState(ViewState::AllIsFine);

}

void DoctorModel::handleDiagnosticProgressChanged(float progress) {
    setProgress(progress);
}

double DoctorModel::progress() const {
    return _progress;
}

void DoctorModel::setProgress(double newProgress) {
    if (qFuzzyCompare(_progress, newProgress))
        return;
    _progress = newProgress;
    emit progressChanged();
}

int DoctorModel::state() const {
    return _state;
}

void DoctorModel::setState(int newState) {
    if (_state == newState)
        return;
    _state = newState;
    emit stateChanged();
}
}
