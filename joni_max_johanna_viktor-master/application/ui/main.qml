import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 1280
    height: 720

    minimumWidth: 1280
    minimumHeight: 720

    title: qsTr("Application")

    color: "#333333"

    ChartsView {
        id: chartsView
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: presetButton.left
    }

    Button {
        id: presetButton
        text: "\u2606"
        font.pixelSize: 25
        height: 50
        width: 50
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.rightMargin: 10
        onClicked: preset.open()
    }

    PresetPopUp {
        id: preset
        width: 300
        height: 400
    }
}
