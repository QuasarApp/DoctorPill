import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

Page {
    id: root;
    property var model : null

    property bool showDescription: true
    property bool showTitle: true

    implicitHeight: 0x0

    signal contactWithDevsPressed();

    title: qsTr("Application's doctor room");

    header: Label {
        horizontalAlignment: Label.AlignHCenter
        text: title
        font.pointSize: 20
        color: (Material.theme === Material.Light)? "#424242" : "#aaaaaa"
        wrapMode: Label.WordWrap
        visible: showTitle
    }

    contentItem: ColumnLayout {

        spacing: 20

        Item {
            Layout.fillHeight: !list.visible
        }

        Label {
            id: descriptionMsg
            text: qsTr("This is your personal application doctor room! The doctor automatically check your application to exits errors. If the Doctor found any errors he suggest solution of your issue");
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            wrapMode: Label.WordWrap
            Layout.fillWidth: true

        }

        Label {
            id: atansionMsg
            text: qsTr("<b>Attention</b>: Please use this page only if you knows what you do. If your application works correctly then please - do nothing.")
                  + qsTr(" For begin diagnostic enter please the next line: ") + "<b>" + privateRoot.enterString + "</b>";
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            wrapMode: Label.WordWrap
            Layout.fillWidth: true

        }

        Image {
            id: allIsFineImg
            fillMode: Image.PreserveAspectFit
            source: "qrc:/icons/icons/Solved.png"
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.alignment: Qt.AlignHCenter

        }

        Label {
            id: allIsFineMsg
            text: qsTr("The Doctor not found any issues. If you sure that application is works wrong then you can contact with developers.")

            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            wrapMode: Label.WordWrap
            Layout.fillWidth: true

        }

        Button {
            id: contactButton

            text: qsTr("Contact with Developers");
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                contactWithDevsPressed();
            }
        }


        ProgressBar {
            id: progress
            indeterminate: value < 0.01;
            Layout.alignment: Qt.AlignHCenter

            from: 0
            to: 1

            value: (root.model)? root.model.progress: 0

            Behavior on value {
                NumberAnimation {
                    duration: 500
                    easing.type: Easing.OutQuad

                }
            }
        }

        RowLayout {
            id: diagnosticButton
            Layout.alignment: Qt.AlignHCenter

            TextField {
                id: confirmInput
                placeholderText: qsTr("Enter: ") + privateRoot.enterString
                Layout.alignment: Qt.AlignHCenter

            }

            Button {
                text: qsTr("Diagnostic");
                Layout.alignment: Qt.AlignHCenter
                enabled: confirmInput.text.toLowerCase() ===
                         privateRoot.enterString.toLowerCase()

                onClicked: {
                    if (root.model) {
                        root.model.diagnostic();
                    } else {
                        console.warn("The DoctorView require model object.")
                    }
                }
            }
        }
        ListView {
            id: list

            ScrollBar.vertical: ScrollBar {}

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: root.model
            visible: (root.model)? root.model.rowCount(): false
            spacing: 20

            leftMargin: 10
            rightMargin: 10
            topMargin: 10
            bottomMargin: 10

            delegate: Component {
                RowLayout {

                    width: Math.min(list.width - list.leftMargin - list.rightMargin, 1024)
                    anchors.horizontalCenter: parent.horizontalCenter

                    function getSourceImage(status) {
                        switch(status) {
                        case 0: return "qrc:/icons/icons/Found.png"; // detected
                        case 1: return "qrc:/icons/icons/Solved.png"; // solved
                        case 2: return "qrc:/icons/icons/Failed.png"; // failed
                        default: return "";// unknown status
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Image {
                        id: bugStatuss
                        fillMode: Image.PreserveAspectFit
                        source: getSourceImage(issueStatus)
                        Layout.preferredHeight: 80
                        Layout.preferredWidth: 80
                    }

                    ColumnLayout {
                        id: textBlock
                        Layout.fillWidth: true

                        Label {
                            text: issueName
                            horizontalAlignment: Qt.AlignLeft
                            verticalAlignment: Qt.AlignVCenter
                            wrapMode: Label.WordWrap

                            font.bold: true
                            font.pixelSize: 20
                        }

                        Label {
                            text: issueDescription
                            Layout.fillWidth: true
                            horizontalAlignment: Qt.AlignLeft
                            verticalAlignment: Qt.AlignVCenter
                            wrapMode: Label.WordWrap
                        }
                    }

                    Button {
                        text: qsTr("Fix");
                        visible: issueStatus === 0
                        onClicked: {
                            if (root.model) {
                                root.model.usePill(issueName);
                            }
                        }
                    }

                    Button {
                        text: qsTr("Drop");
                        visible: issueStatus === 1
                        onClicked: {
                            if (root.model) {
                                root.model.drop(row);
                            }
                        }
                    }

                    Label {
                        text: qsTr("Fix failed  ;( ")
                        font.bold: true
                        visible: issueStatus === 2

                    }

                    Item {
                        Layout.fillWidth: true
                    }
                }
            }
        }

        Item {
            Layout.fillHeight: !list.visible
        }

    }

    state: (root.model)? privateRoot.getState(root.model.state): "beginDiagnostic"


    //beginDiagnostic
    //searchBugs
    //bugFound
    //allIsFine
    states: [
        State {
            name: "beginDiagnostic"
            PropertyChanges {
                target: atansionMsg;
                visible: showDescription
            }

            PropertyChanges {
                target: descriptionMsg;
                visible: showDescription
            }

            PropertyChanges {
                target: allIsFineImg;
                visible: false
            }

            PropertyChanges {
                target: allIsFineMsg;
                visible: false
            }

            PropertyChanges {
                target: contactButton;
                visible: false
            }

            PropertyChanges {
                target: progress;
                visible: false
            }

            PropertyChanges {
                target: diagnosticButton;
                visible: true
            }


            PropertyChanges {
                target: list;
                visible: false
            }
        },

        State {
            name: "searchBugs"
            PropertyChanges {
                target: atansionMsg;
                visible: false
            }

            PropertyChanges {
                target: descriptionMsg;
                visible: false
            }

            PropertyChanges {
                target: allIsFineImg;
                visible: false
            }

            PropertyChanges {
                target: allIsFineMsg;
                visible: false
            }

            PropertyChanges {
                target: contactButton;
                visible: false
            }

            PropertyChanges {
                target: progress;
                visible: true
            }

            PropertyChanges {
                target: diagnosticButton;
                visible: false
            }

            PropertyChanges {
                target: list;
                visible: false
            }
        },

        State {
            name: "bugFound"
            PropertyChanges {
                target: atansionMsg;
                visible: false
            }

            PropertyChanges {
                target: descriptionMsg;
                visible: false
            }

            PropertyChanges {
                target: allIsFineImg;
                visible: false
            }

            PropertyChanges {
                target: allIsFineMsg;
                visible: false
            }

            PropertyChanges {
                target: contactButton;
                visible: false
            }

            PropertyChanges {
                target: progress;
                visible: false
            }

            PropertyChanges {
                target: diagnosticButton;
                visible: false
            }

            PropertyChanges {
                target: list;
                visible: true
            }
        },

        State {
            name: "allIsFine"
            PropertyChanges {
                target: atansionMsg;
                visible: false
            }

            PropertyChanges {
                target: descriptionMsg;
                visible: false
            }

            PropertyChanges {
                target: allIsFineImg;
                visible: true
            }

            PropertyChanges {
                target: allIsFineMsg;
                visible: true
            }

            PropertyChanges {
                target: contactButton;
                visible: true
            }

            PropertyChanges {
                target: progress;
                visible: false
            }

            PropertyChanges {
                target: diagnosticButton;
                visible: false
            }

            PropertyChanges {
                target: list;
                visible: false
            }
        }
    ]

    Item {
        id: privateRoot

        property string enterString: qsTr("I know what I'm doing")

        function getState(state) {
            switch(state) {
            case 0: return "beginDiagnostic";
            case 1: return "searchBugs";
            case 2: return "bugFound";
            case 3: return "allIsFine";
            }
        }
    }
}
