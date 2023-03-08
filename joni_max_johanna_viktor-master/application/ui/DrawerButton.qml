import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: button
    property string text: ""
    property bool isSelected: false
    color: getColor()
    signal clicked

    Label {
        text: button.text
        anchors.centerIn: parent
        color: "white"
        font.bold: true
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: {
            button.clicked()
        }
    }

    function getColor() {
        if (isSelected) {
            return "#101010"
        } else {
            return mouseArea.containsMouse ? "#515151" : "#232323"
        }
    }
}
