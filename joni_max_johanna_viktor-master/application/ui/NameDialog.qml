import QtQuick 2.12
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.3

Dialog {
    id: dialog
    title: "Title"

    standardButtons: Dialog.Ok

    width: 300
    height: 100

    property string userInput: entry.text

    onVisibilityChanged: {
        if (visible) {
            entry.forceActiveFocus()
        }
    }

    function clearUserInput() {
        entry.text = ""
    }

    Label {
        id: label
        text: qsTr("Name: ")
        font.pixelSize: 16
        verticalAlignment: Label.AlignVCenter
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
    }

    TextField {
        id: entry
        height: 40
        width: 200
        anchors.left: label.right
        anchors.verticalCenter: label.verticalCenter
        font.pixelSize: 18
    }
}
