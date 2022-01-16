import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

Page {
    id: root;
    property var model : null
    implicitHeight: 0x0

    signal contactWithDevsPressed();

    contentItem: ColumnLayout {

        Label {
            id: atansionMsg
            text: qsTr("Attention: Please use this page only if you knows what you do. If your application works correctly then please - do nothing.");
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            wrapMode: Label.WordWrap
            Layout.fillWidth: true

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
            id: allIsFineMsg
            text: qsTr("The Doctor not found any issues. If you sure that application is works wrong then you can contact with developers.");
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
            indeterminate: true;
        }

        Button {
            id: diagnosticButton
            text: qsTr("Diagnostic");
            Layout.alignment: Qt.AlignHCenter

            onClicked: {
                if (root.model) {
                    root.model.diagnostic();
                }
            }
        }

        ListView {
            id: list
            anchors.fill: parent
            model: root.model
            visible: (root.model)? root.model.rowCount(): false
            delegate: Component {
                RowLayout {

                    function getSourceImage(status) {
                        switch(status) {
                            case 0: return ""; // detected
                            case 1: return ""; // solved
                            case 2: return ""; // failed
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
                        Layout.preferredHeight: 60
                        Layout.preferredWidth: height
                    }

                    Label {
                        text: issueName
                    }

                    Label {
                        text: issueDescription
                    }

                    Button {
                        text: qsTr("Repair");
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    width: list.width
                }
            }
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
                visible: true
            }

            PropertyChanges {
                target: descriptionMsg;
                visible: true
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
