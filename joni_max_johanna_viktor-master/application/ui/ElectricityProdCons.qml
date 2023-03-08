import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    property var controller: LeftUIController

    property double  labelHeight: 30
    property double labelWidth: parent.width * 0.2

    anchors.topMargin: 10
    anchors.leftMargin: 20
    anchors.rightMargin: 10


    Label {
        id: prodLabel
        text: qsTr("Production")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        anchors.top: parent.top
        anchors.left: parent.left
        color: "white"
        font.pixelSize: 18
    }

    CheckBox {
        id: prodBox
        anchors.verticalCenter: prodLabel.verticalCenter
        anchors.left: prodLabel.right
        checked: controller.checkBox0
        onCheckedChanged: controller.checkBox0 = checked
    }

    Label {
        id: consLabel
        text: qsTr("Consumption")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        anchors.top: prodLabel.bottom
        anchors.left: parent.left
        anchors.topMargin: 20
        color: "white"
        font.pixelSize: 18
    }

    CheckBox {
        id: consBox
        anchors.verticalCenter: consLabel.verticalCenter
        anchors.left: consLabel.right
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
        height: labelHeight
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
       // verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        anchors.right: parent.right

        anchors.verticalCenter: endingDate.verticalCenter
       // anchors.topMargin: 5
        anchors.rightMargin: 170
        color: "white"
        font.pixelSize: 15
    }
}
