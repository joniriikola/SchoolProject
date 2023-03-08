import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    anchors.topMargin: 10
    anchors.bottomMargin: 10
    ChartViewPane {
        id: leftPane
        width: (parent.width / 2) - 15
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 10
        controller: LeftUIController
    }
    ChartViewPane {
        id: rightPane
        width: (parent.width / 2) - 15
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 10
        controller: RightUIController
    }
}
