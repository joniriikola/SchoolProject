import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    property var controller: LeftUIController

    property double labelHeight: 40
    property double labelWidth: 120

    anchors.topMargin: 30
    anchors.leftMargin: 20
    anchors.rightMargin: 10

    Button {
        text: "Search"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 1
        anchors.rightMargin: 50
        onClicked: controller.search()
        enabled: !controller.busyIndicator
    }

    Label {
        id: startingDateLabel
        text: qsTr("Start Date")
        verticalAlignment: Qt.AlignVCenter

        width: labelWidth
        height: labelHeight

        anchors.left: parent.left
        anchors.top: parent.top

        color: "white"
        font.pixelSize: 15
    }

    DateField {
        id: startingDate
        anchors.left: startingDateLabel.right
        anchors.verticalCenter: startingDateLabel.verticalCenter

        onUserSelection: {
            controller.startDate = selectedDate
        }
    }

    Label {
        id: endingDateLabel
        text: qsTr("End Date")
        verticalAlignment: Qt.AlignVCenter

        width: labelWidth
        height: labelHeight

        anchors.left: parent.left
        anchors.top: startingDateLabel.bottom
        anchors.topMargin: 20

        color: "white"
        font.pixelSize: 15
    }

    DateField {
        id: endingDate
        anchors.left: endingDateLabel.right
        anchors.verticalCenter: endingDateLabel.verticalCenter

        onUserSelection: {
            controller.endDate = selectedDate
        }
    }
}
