//#
//# Copyright (C) 2020-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef BASE_TEST_H
#define BASE_TEST_H
#include "test.h"
#include "testutils.h"
#include "DoctorPillCore/doctortest.h"

#include <QtTest>

class BaseTest: public Test, protected TestUtils
{
public:
    BaseTest();
    ~BaseTest();

    void test();

private:
    DP::DoctorTest _test;

    friend class TestPill;

    bool _appIsBroken = true;

};

#endif // BASE_TEST_H
