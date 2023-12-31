//#
//# Copyright (C) 2020-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "basetest.h"

#include <DoctorPillCore/ipill.h>

class TestPill: public DP::iPill {


    // iPill interface
public:
    TestPill(BaseTest* app) {
        _app = app;
    };

    int id() const override {
        return typeid (this).hash_code();
    };

    QString name() const override {
        return "Test pill";
    };

    QString description() const override {
        return "just test pill";
    };

protected:
    bool diagnostic() override {
        return _app->_appIsBroken;
    };

    bool fix() override {
        _app->_appIsBroken = false;
        return !_app->_appIsBroken;
    };

private:
    BaseTest * _app = nullptr;
};

BaseTest::BaseTest() {

}

BaseTest::~BaseTest() {

}

void BaseTest::test() {

    _appIsBroken = true;
    QVERIFY(_test.test({QSharedPointer<TestPill>::create(this)}, _appIsBroken));
    QVERIFY(!_appIsBroken);

    QVERIFY(_test.test({QSharedPointer<TestPill>::create(this)}, _appIsBroken));
    QVERIFY(!_appIsBroken);

}
