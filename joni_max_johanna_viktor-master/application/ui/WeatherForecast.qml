import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    //By default on left, change controller for right
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

        width: labelWidth
        height: labelHeight
        anchors.top: parent.top
        anchors.left: parent.left
    }

    SearchBar {
        id: locationField
        controller: parent.controller
        text: controller.location
        anchors.left: locationLabel.right
        anchors.verticalCenter: locationLabel.verticalCenter
        width: parent.width - labelWidth
        height: 40
        onValueChanged: controller.location = value
        onEnter: controller.search()
    }

    Label {
        id: checkBox0Label
        text: qsTr("Wind Speed")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight

        anchors.top: locationLabel.bottom
        anchors.left: parent.left
        anchors.topMargin: 10
        color: "white"
        font.pixelSize: 18
    }

    CheckBox {
        id: checkBox0
        anchors.verticalCenter: checkBox0Label.verticalCenter
        anchors.left: locationField.left
        anchors.top: locationField.bottom
        checked: controller.checkBox0
        onCheckedChanged: controller.checkBox0 = checked
    }

    Label {
        id: checkBox1Label
        text: qsTr("Temperature")
        anchors.top: checkBox0Label.bottom
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
        anchors.top: checkBox0.bottom
        checked: controller.checkBox1
        onCheckedChanged: controller.checkBox1 = checked
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
