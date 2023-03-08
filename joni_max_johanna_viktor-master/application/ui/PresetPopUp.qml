import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Dialog {
    id: dialog
    title: "Presets"

    onVisibleChanged: {
        listview.setIndex(-1)
        listview.userSelection = ""
    }

    contentItem: Rectangle {

        anchors.fill: parent
        color: "#333333"

        ListViewElement {
            id: listview
            property string userSelection: ""
            model: PresetController.savedPresetsModel()
            headerText: qsTr("Presets")
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.9
            height: parent.height * 0.8
            anchors.topMargin: 5
            z: 2
            onSelection: userSelection = name
        }

        Button {
            id: saveButton
            text: "Save Current"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.bottomMargin: 5
            anchors.leftMargin: 10
            onClicked: saveDialog.open()
        }

        Button {
            id: loadButton
            text: "Load Preset"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 5
            anchors.rightMargin: 10
            onClicked: {
                PresetController.loadPreset(listview.userSelection)
            }
        }

        NameDialog {
            id: saveDialog
            onAccepted: {
                PresetController.savePreset(userInput)
                clearUserInput()
            }
        }
    }
}
