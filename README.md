# Doctor Pill
The Doctor pill is simple qt / qml library for fast develop fixes for applications that already released and working in production. 

The library has c++ interface DP::iPill and QML view for diagnostic gui applications.

For Disable the gui part of the library use the DOCTOR_PILL_GUI option.


![2022-01-18 17-50-20](https://user-images.githubusercontent.com/12465465/149961627-2f74d25d-f047-4176-913b-6d3f833603cf.gif)


## BUILD OPTIONS

``` cmake 
option(DOCTOR_PILL_GUI "Enable gui qml model for build" ON)
option(DOCTOR_PILL_TESTS "Enable tests of this library" ON)
option(DOCTOR_PILL_EXAMPLE "Enable example app of this library" ON)
```


## Include to cmake project

1. add as a submodule this repo 

``` bash
 git submodule add https://github.com/QuasarApp/DoctorPill.git
```

2. Add to build the DoctorPill as a subdirectory

``` cmake
set(DOCTOR_PILL_GUI ON) # you may change it if you need.
set(DOCTOR_PILL_TESTS OFF) you may change it if you need.
set(DOCTOR_PILL_EXAMPLE OFF) you may change it if you need.

add_subdirectory(DoctorPill)
```

## Using 

### Wihout GUI


#### Create a new pill object.

```cpp
#include <doctorpill.h>

class MyPill: DP::iPill {
    QString name() const override {
        return "My pill";
    };
    
    QString description() const override {
        return "Description of my pill";
    };
    
protected:
    bool diagnostic() const override {
        // some code for search bug
    };
    
    bool fix() const override {
        // some code for fix found bug
    };
}; 
```

#### Use your self created pills


```cpp
#include <doctorpill.h>

// ...

DP::Doctor _doctor;
if (_doctor.fix({QSharedPointer<MyPill>::create()})) {
    // app fixed successfull
} else {
    // fail to fix app
}

// ...
```



### Use GUI QML wrapper

For working with gui wrapper you need to initialize this library before include gui module in to your qml file.


#### initialize the library (main.cpp)


```cpp

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setApplicationName("DoctorPillExample");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    if (!DP::init(&engine)) {
        return -1;
    }

    DP::DoctorModel model({QSharedPointer<SomePill>::create()});

    // see next code view 
    engine.load("qrc:/Main.qml");
    if (engine.rootObjects().isEmpty())
        return -2;

    // Add new doctor pill model to view
    QQmlContext* rootContext = engine.rootContext();
    if (rootContext)
        rootContext->setContextProperty("doctorPillModel", &model);

    return app.exec();
}


```


#### Using qml view (main.qml)


```qml

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import DoctorPillModule 1.0

ApplicationWindow {
    width: 800
    height: 600
    visible: true

    DoctorView {
        anchors.fill: parent
        // use added model in qml file.
        model: (doctorPillModel)? doctorPillModel: null
    }
}

```

