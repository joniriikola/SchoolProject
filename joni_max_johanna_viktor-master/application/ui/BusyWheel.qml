import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: background
    anchors.centerIn: parent
    radius: 180

    BusyIndicator {
        id: busyIndicator
        anchors.fill: parent
        running: true
    }
}
