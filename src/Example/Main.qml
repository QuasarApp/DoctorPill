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
        model: (doctorPillModel)? doctorPillModel: null
    }
}
