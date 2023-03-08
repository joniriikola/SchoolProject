import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    property var controller: LeftUIController

    property double labelHeight: 40
    property double labelWidth: parent.width * 0.2

    anchors.topMargin: 10
    anchors.leftMargin: 20

    Label {
        id: locationLabel
        text: qsTr("Location")
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.pixelSize: 18
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        width: labelWidth
        height: labelHeight
    }

    SearchBar {
        id: locationField
        controller: parent.controller
        anchors.left: locationLabel.right
        anchors.verticalCenter: locationLabel.verticalCenter
        width: parent.width - labelWidth
        height: 40
        onValueChanged: controller.location = value
        onEnter: controller.search()
    }
    Label {
        id: startingDateLabel
        text: qsTr("Start Date")
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.pixelSize: 18
        anchors.top: locationLabel.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 170
        width: labelWidth
        height: labelHeight
    }

    DateField {
        id: startingDate
        anchors.top: locationField.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        onUserSelection: {
            controller.startDate = selectedDate
        }
    }

    Label {
        id: endingDateLabel
        text: qsTr("End Date")
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.pixelSize: 18
        anchors.top: startingDateLabel.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 170
        width: labelWidth
        height: labelHeight
    }

    DateField {
        id: endingDate
        anchors.top: startingDate.bottom
        anchors.right: parent.right
        anchors.topMargin: 2
        onUserSelection: {
            controller.endDate = selectedDate
        }
    }

    Label {
        id: checkBox0Label
        text: qsTr("Cloudiness")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        anchors.top: locationLabel.bottom
        anchors.left: parent.left
        anchors.topMargin: 2
        color: "white"
        font.pixelSize: 18
    }

    CheckBox {
        id: checkBox0
        anchors.verticalCenter: checkBox0Label.verticalCenter
        anchors.left: locationField.left
        checked: controller.checkBox0
        onCheckedChanged: controller.checkBox0 = checked
    }

    Label {
        id: checkBox1Label
        text: qsTr("Wind Speed")
        anchors.top: checkBox0Label.bottom
        anchors.topMargin: 2
        anchors.left: parent.left
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        color: "white"
        font.pixelSize: 18
    }

    CheckBox {
        id: checkBox1
        anchors.verticalCenter: checkBox1Label.verticalCenter
        anchors.left: locationField.left
        checked: controller.checkBox1
        onCheckedChanged: controller.checkBox1 = checked
    }
    Label {
        id: checkBox2Label
        text: qsTr("Temperature")
        anchors.top: checkBox1Label.bottom
        anchors.topMargin: 2
        anchors.left: parent.left
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        color: "white"
        font.pixelSize: 18
    }

    CheckBox {
        id: checkBox2
        anchors.verticalCenter: checkBox2Label.verticalCenter
        anchors.left: locationField.left
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
}
