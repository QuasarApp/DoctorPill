//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <doctorpill.h>

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setApplicationName("DoctorPillExample");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    if (!DP::init(&engine)) {
        return -1;
    }

    engine.load("qrc:/Main.qml");
    if (engine.rootObjects().isEmpty())
        return -2;

    return app.exec();
}
