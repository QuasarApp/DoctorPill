//#
//# Copyright (C) 2018-2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef DoctorPill_GLOBAL_H
#define DoctorPill_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DoctorPill_LIBRARY)
#  define DoctorPill_EXPORT Q_DECL_EXPORT
#else
#  define DoctorPill_EXPORT Q_DECL_IMPORT
#endif

#endif //DoctorPill_GLOBAL_H

