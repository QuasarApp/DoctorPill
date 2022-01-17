//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef PILLSMODEL_H
#define PILLSMODEL_H

#include <QAbstractListModel>
#include <QFuture>
#include <DoctorPillCore/doctor.h>

namespace DP {

/**
 * @brief The PillsModel class This is gui model of available pills.
 */
class DoctorModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)

    struct Issue {
        int _status = 0;
        QSharedPointer<iPill> _pill = nullptr;
    };

    enum Roles {

        Name = Qt::UserRole,
        Description,
        Status,
        Row
    };

    enum IssueStatus {
        Detected,
        Solved,
        Failed
    };

    enum ViewState {
        BeginDiagnostic,
        SearchBugs,
        BugFound,
        AllIsFine,
    };

public:

    DoctorModel(const QList<QSharedPointer<iPill>> &base);
    void addPill(const QSharedPointer<iPill>& pill);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void usePill(QString pillName);
    Q_INVOKABLE void diagnostic();
    Q_INVOKABLE void drop(int row);

    double progress() const;
    int state() const;

signals:
    void progressChanged();

    void stateChanged();

private slots:
    void handleFixFailed(QList<QSharedPointer<iPill>>);
    void handleFixSuccessful(QList<QSharedPointer<iPill>>);
    void handleDiagnostcFinished(QList<QSharedPointer<iPill>>);
    void handleDiagnosticProgressChanged(float);

private:
    void setProgress(double newProgress);
    void setState(int newState);

    int _state;
    Doctor _doctor;
    QHash<QString, Issue> _viewData;
    double _progress;
    QFuture<void> _diagnosticWork;
};

}
#endif // PILLSMODEL_H
