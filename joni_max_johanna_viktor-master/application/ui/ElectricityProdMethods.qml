import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    //By default on left, change controller for right
    property var controller: LeftUIController

    property double labelWidth: parent.width * 0.2

    anchors.topMargin: 10
    anchors.leftMargin: 20
    anchors.rightMargin: 10

    Label {
        id: checkBox0Label
        text: qsTr("Wind")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        anchors.top: parent.top
        anchors.left: parent.left
        color: "white"
        font.pixelSize: 18
    }

    CheckBox {
        id: checkBox0
        anchors.verticalCenter: checkBox0Label.verticalCenter
        anchors.left: checkBox0Label.right
        checked: controller.checkBox0
        onCheckedChanged: controller.checkBox0 = checked
    }

    Label {
        id: checkBox1Label
        text: qsTr("Hydro")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        anchors.top: checkBox0Label.bottom
        anchors.left: parent.left
        anchors.topMargin: 20
        color: "white"
        font.pixelSize: 18
    }

    CheckBox {
        id: checkBox1
        anchors.verticalCenter: checkBox1Label.verticalCenter
        anchors.left: checkBox1Label.right
        checked: controller.checkBox1
        onCheckedChanged: controller.checkBox1 = checked
    }

    Label {
        id: checkBox2Label
        text: qsTr("Nuclear")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        anchors.top: checkBox1Label.bottom
        anchors.left: parent.left
        anchors.topMargin: 20
        color: "white"
        font.pixelSize: 18
    }

    CheckBox {
        id: checkBox2
        anchors.verticalCenter: checkBox2Label.verticalCenter
        anchors.left: checkBox2Label.right
        checked: controller.checkBox2
        onCheckedChanged: controller.checkBox2 = checked
    }

    Button {
        text: "Search"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 1
        anchors.rightMargin: 50
        onClicked: controller.search()
        enabled: !controller.busyIndicator
    }

    DateField {
        id: startingDate
        anchors.top: parent.top
        anchors.right: parent.right
        onUserSelection: {
            controller.startDate = selectedDate
        }
    }

    DateField {
        id: endingDate
        anchors.top: startingDate.bottom
        anchors.right: parent.right
        anchors.topMargin: 5
        onUserSelection: {
            controller.endDate = selectedDate
        }
    }

    Label {
        id: startingDateLabel
        text: qsTr("Start Date")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.rightMargin: 170
        color: "white"
        font.pixelSize: 15
    }

    Label {
        id: endingDateLabel
        text: qsTr("End Date")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        anchors.right: parent.right
        anchors.top: startingDateLabel.bottom
        anchors.topMargin: 30
        anchors.rightMargin: 170
        color: "white"
        font.pixelSize: 15
    }
}
