//#
//# Copyright (C) 2021-2022 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <doctorpillgui.h>
#include <thread>

class EmptyPill: public DP::iPill {


    // iPill interface
public:
    QString name() const override {
        return "EmptyPill";
    };

    int id() const override {
        return typeid (this).hash_code();
    };

    QString description() const override {
        return "Pill For Test. This pill cant be fixed ";
    };

protected:
    bool diagnostic() override {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return true;
    };
    bool fix() override {
        return true;
    };
};

class EmptyPill1: public DP::iPill {


    // iPill interface
public:
    QString name() const override {
        return "EmptyPill1";
    };

    QString description() const override {
        return "Pill For Test. This pill cant be fixed ";
    };

    int id() const override {
        return typeid (this).hash_code();
    };

protected:
    bool diagnostic() override {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return true;
    };
    bool fix() override {
        return true;
    };

};


class EmptyPill2: public DP::iPill {


    // iPill interface
public:
    QString name() const override {
        return "EmptyPill2";
    };

    int id() const override {
        return typeid (this).hash_code();
    };

    QString description() const override {
        return "Pill For Test. This pill cant be fixed ";
    };

protected:
    bool diagnostic() override {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return true;
    };
    bool fix() override {
        return true;
    };
};

class LongPill: public DP::iPill {


    // iPill interface
public:
    QString name() const override {
        return "Long Pill ";
    };

    int id() const override {
        return typeid (this).hash_code();
    };

    QString description() const override {
        return "Lorem Ipsum is simply dummy text of the printing and typesetting industry."
               " Lorem Ipsum has been the industry's standard dummy text ever since the 1500s,"
               " when an unknown printer took a galley of type and scrambled it to make a type specimen book."
               " It has survived not only five centuries,"
               " but also the leap into electronic typesetting,"
               " remaining essentially unchanged."
               " It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages,"
               " and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum. ";
    };

protected:
    bool diagnostic() override {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return true;
    };
    bool fix() override {
        return true;
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

    DP::DoctorModel model({QSharedPointer<EmptyPill>::create(),
                           QSharedPointer<LongPill>::create(),
                           QSharedPointer<EmptyPill1>::create(),
                           QSharedPointer<EmptyPill2>::create()});

    engine.load("qrc:/Main.qml");
    if (engine.rootObjects().isEmpty())
        return -2;

    QQmlContext* rootContext = engine.rootContext();
    if (rootContext)
        rootContext->setContextProperty("doctorPillModel", &model);

    return app.exec();
}
