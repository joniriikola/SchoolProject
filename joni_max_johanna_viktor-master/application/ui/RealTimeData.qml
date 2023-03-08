import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    property var controller: undefined
    Button {
        text: "Start"
        anchors.centerIn: parent
        onClicked: {
            pane.controller.search()
        }
    }
}
