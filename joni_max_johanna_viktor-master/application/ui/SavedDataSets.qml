import QtQuick 2.15
import QtQuick.Controls 2.12

Item {
    property var controller: LeftUIController

    property double labelHeight: 30
    property double labelWidth: parent.width * 0.2

    anchors.topMargin: 10
    anchors.leftMargin: 20
    anchors.rightMargin: 20

    Connections {
        target: controller
        function onFileNameChanged() {
            listView.setIndex(controller.fileIndex)
        }
    }

    ListViewElement {
        id: listView
        anchors.fill: parent
        model: controller.savedFilesModel()
        headerText: qsTr("Saved Data Sets")
        onSelection: {
            controller.fileName = name // gives title to uicontroller
            controller.search()
        }
    }
}
