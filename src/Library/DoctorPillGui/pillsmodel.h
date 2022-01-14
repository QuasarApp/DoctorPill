//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef PILLSMODEL_H
#define PILLSMODEL_H

#include <QAbstractListModel>
#include <DoctorPillCore/doctor.h>

namespace DP {

struct Issue {
    int _status = 0;
    QSharedPointer<iPill> _pill = nullptr;
};

/**
 * @brief The PillsModel class This is gui model of available pills.
 */
class PillsModel: public QAbstractListModel
{
    Q_OBJECT

    enum Roles {
        Name = Qt::UserRole,
        Description,
        Status
    };

    enum IssueStatus {
        Detected,
        Solved,
        Failed
    };

public:
    PillsModel(const QList<QSharedPointer<iPill>> &base);
    void addPill(const QSharedPointer<iPill>& pill);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void usePill(QString pillName);
    Q_INVOKABLE void diagnostic();

private slots:
    void handleFixFailed(QList<QSharedPointer<iPill>>);
    void handleFixSuccessful(QList<QSharedPointer<iPill>>);
    void handleBugDetected(QList<QSharedPointer<iPill>>);

private:
    Doctor _doctor;
    QHash<QString, Issue> _viewData;
};

}
#endif // PILLSMODEL_H
