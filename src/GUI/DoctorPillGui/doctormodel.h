//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef DOCTORMODEL_H
#define DOCTORMODEL_H

#include <QAbstractListModel>
#include <DoctorPillCore/doctor.h>
#include <doctorpill_gui_global.h>

namespace DP {

/**
 * @brief The PillsModel class This is gui model of available pills.
 */
class DOCTOR_PILL_GUI_EXPORT DoctorModel: public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)

    /**
     * @brief The Issue struct Simple structure for collect status of issues.
     * @see IssueStatus
     */
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

    /**
     * @brief The IssueStatus enum This is issue status.
     */
    enum IssueStatus {
        /// the issue detected but not still not fixed
        Detected,
        /// the issue fixed successful
        Solved,
        /// the issue tried to fix but failed.
        Failed
    };

    /**
     * @brief The ViewState enum This enum contains all gui states of the doctor table.
     */
    enum ViewState {
        /// This statte is default state of table. In This state application still not checked bugs.
        BeginDiagnostic,
        /// This state activated when doctor search bugs in app.
        SearchBugs,
        /// This state activated when doctor gound any issue in the system.
        BugFound,
        /// This state activated when doctor thin that application works correctly. activated after diagnostic process.
        AllIsFine,
    };

public:

    /**
     * @brief DoctorModel This is wrapper cntructor for the Doctor class
     * @param base This is list of available fixes
     * @see Doctor
     */
    DoctorModel(const QList<QSharedPointer<iPill>> &base);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief usePill This method try execute fix fo @a pillName pill.
     * @param pillName This is name of selected pill object.
     */
    Q_INVOKABLE void usePill(QString pillName);

    /**
     * @brief diagnostic This method run diagnostic f this application.
     * @note The diagnostic will works in separate thread.
     */
    Q_INVOKABLE void diagnostic();

    /**
     * @brief drop This method remove line frma table.
     * @param row rw that will be removed.
     */
    Q_INVOKABLE void drop(int row);

    /**
     * @brief progress This method return current progress value. (from 0 to 1)
     * @return current progress value
     */
    double progress() const;

    /**
     * @brief state This method return state of table.
     * @see ViewState
     * @return current state of the table.
     */
    int state() const;

signals:
    /**
     * @brief progressChanged This signal emited when progress of diagnostic changed.
     */
    void progressChanged();

    /**
     * @brief stateChanged This signal will emitted when state of the tabe changed.s
     */
    void stateChanged();

private slots:
    void handleFixFailed(QList<QSharedPointer<DP::iPill>>);
    void handleFixSuccessful(QList<QSharedPointer<DP::iPill>>);
    void handleDiagnostcFinished(QList<QSharedPointer<DP::iPill>>);
    void handleDiagnosticProgressChanged(float);

private:
    void setProgress(double newProgress);
    void setState(int newState);

    int _state;
    Doctor _doctor;
    QHash<QString, Issue> _viewData;
    double _progress;
};

}
#endif // DOCTORMODEL_H
