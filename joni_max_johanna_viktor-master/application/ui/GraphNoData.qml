import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    property var model: undefined
    id: noData
    color: "#333333"
    Label {
        id: noDataLabel
        text: "No Data"
        anchors.centerIn: parent
        font.pixelSize: 32
        color: "white"
    }
    Label {
        id: errorMsg
        text: model.error
        anchors.top: noDataLabel.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: noDataLabel.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        width: parent.width
        font.pixelSize: 16
        color: "white"
    }
}
