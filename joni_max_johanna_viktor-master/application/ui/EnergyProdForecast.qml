import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    //By default on left, change controller for right
    property var controller: LeftUIController

    property double labelWidth: parent.width * 0.2

    anchors.topMargin: 30
    anchors.leftMargin: 60
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
        text: qsTr("Solar")
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
