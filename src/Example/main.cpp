//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <doctorpill.h>
#include <thread>

class EmptyPill: public DP::iPill {


    // iPill interface
public:
    QString name() const override {
        return "EmptyPill";
    };

    QString description() const override {
        return "Pill For Test. This pill cant be fixed ";
    };

protected:
    bool diagnostic() const override {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return true;
    };
    bool fix() const override {
        return false;
    };
};

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setApplicationName("DoctorPillExample");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    if (!DP::init(&engine)) {
        return -1;
    }

    DP::DoctorModel model({QSharedPointer<EmptyPill>::create()});

    engine.load("qrc:/Main.qml");
    if (engine.rootObjects().isEmpty())
        return -2;

    QQmlContext* rootContext = engine.rootContext();
    if (rootContext)
        rootContext->setContextProperty("doctorPillMpdel", &model);

    return app.exec();
}
