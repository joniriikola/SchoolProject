import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    property var controller: LeftUIController

    property double  labelHeight: 30
    property double labelWidth: parent.width * 0.2

    anchors.topMargin: 10
    anchors.leftMargin: 60
    anchors.rightMargin: 10

    Label{
        id: prodLabel
        text: qsTr("Production")
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.pixelSize: 18
        anchors.top: parent.top
        anchors.left: parent.left
        width: labelWidth
        height: labelHeight
    }
    CheckBox{
        id: prodBox
        anchors.verticalCenter: prodLabel.verticalCenter
        anchors.left: prodLabel.right
        checked: controller.checkBox0
        onCheckedChanged: controller.checkBox0 = checked
    }

    Label{
        id: consLabel
        text: qsTr("Consumption")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        anchors.top: prodLabel.bottom
        anchors.left: parent.left
        anchors.topMargin: 10
        color: "white"
        font.pixelSize: 18
    }
    CheckBox{
        id: consBox
        anchors.verticalCenter: consLabel.verticalCenter
        anchors.left: prodBox.left
        checked: controller.checkBox1
        onCheckedChanged: controller.checkBox1 = checked
    }

    Button{
        text: qsTr("Search")
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 1
        anchors.rightMargin: 50
        onClicked: controller.search()
        enabled: !controller.busyIndicator
    }
}

