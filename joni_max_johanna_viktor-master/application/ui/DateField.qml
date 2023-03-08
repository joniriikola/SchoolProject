import QtQuick 2.12
import QtQuick.Controls 2.12

TextField {
    property date selectedDate: dialog.date
    signal userSelection
    text: selectedDate.toLocaleDateString()
    font.pixelSize: 11
    onVisibleChanged: dialog.reset()

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            dialog.open()
        }
    }

    CalendarPopUp {
        id: dialog
        width: 300
        height: 350
        onAccepted: userSelection()
    }

    Image {
        id: icon
        source: "qrc:/ui/icons/calendar.svg"
        sourceSize.height: parent.height * 0.8
        sourceSize.width: parent.height * 0.8
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.verticalCenter: parent.verticalCenter
    }
}
