import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    property var controller: LeftUIController

    property double labelHeight: 40
    property double labelWidth: parent.width * 0.2

    anchors.topMargin: 10
    anchors.leftMargin: 20

    function setDate(month, year) {

        var date = new Date()
        date.setMonth(month)
        date.setFullYear(year)
        controller.startDate = date
    }

    onVisibleChanged: {
        if (visible) {
            var date = new Date()
            monthMenu.currentIndex = date.getMonth()
            yearMenu.currentIndex = 0
        }
    }

    Label {
        id: locationLabel
        text: qsTr("Location")
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.pixelSize: 18
        anchors.top: parent.top
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
        id: monthLabel
        text: qsTr("Month")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        anchors.top: locationLabel.bottom
        anchors.left: parent.left
        anchors.topMargin: 10
        color: "white"
        font.pixelSize: 18
    }
    ComboBox {
        id: monthMenu
        width: 100
        model: MonthModel
        textRole: "display"
        anchors.verticalCenter: monthLabel.verticalCenter
        anchors.left: locationField.left
        anchors.topMargin: 5
        onActivated: setDate(currentIndex, yearMenu.currentText)
    }
    ComboBox {

        id: yearMenu
        width: 100
        model: YearModel
        textRole: "display"
        anchors.verticalCenter: monthLabel.verticalCenter
        anchors.left: monthMenu.right
        anchors.topMargin: 5
        anchors.leftMargin: 3
        onActivated: setDate(monthMenu.currentIndex, currentText)
    }
    Label {
        id: minTLabel
        text: qsTr("Min Temp.")
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        anchors.top: monthLabel.bottom
        anchors.left: parent.left
        anchors.topMargin: 10
        color: "white"
        font.pixelSize: 18
    }
    CheckBox {
        id: minTbox
        anchors.verticalCenter: minTLabel.verticalCenter
        anchors.left: locationField.left
        checked: controller.checkBox0
        onCheckedChanged: controller.checkBox0 = checked
    }
    Label {
        id: maxTLabel
        text: qsTr("Max Temp.")
        anchors.top: minTLabel.bottom
        anchors.left: parent.left
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        color: "white"
        font.pixelSize: 18
    }
    CheckBox {
        id: maxTbox
        anchors.verticalCenter: maxTLabel.verticalCenter
        anchors.left: locationField.left
        checked: controller.checkBox1
        onCheckedChanged: controller.checkBox1 = checked
    }
    Label {
        id: avgTLabel
        text: qsTr("Avg Temp.")
        anchors.verticalCenter: minTbox.verticalCenter
        anchors.left: minTbox.right
        verticalAlignment: Text.AlignVCenter
        width: labelWidth
        height: labelHeight
        color: "white"
        font.pixelSize: 18
    }
    CheckBox {
        id: avgTbox
        anchors.verticalCenter: avgTLabel.verticalCenter
        anchors.left: avgTLabel.right
        checked: controller.checkBox2
        onCheckedChanged: controller.checkBox2 = checked
    }

    Button {
        text: qsTr("Search")
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 1
        anchors.rightMargin: 50
        onClicked: controller.search()
        enabled: !controller.busyIndicator
    }
}
