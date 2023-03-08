import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: searchBar

    property var controller: undefined
    property string value: input.text
    property var text: controller.location



    signal enter

    Text {
        id: suggestion
        visible: input.text.length !== 0
        text: controller.locationAutoComp
        font: input.font
        leftPadding: input.leftPadding
        color: "DarkGray"
        anchors.verticalCenter: input.verticalCenter
    }

    Text {
        id: placeholder
        visible: input.text.length === 0
        text: controller.locationHint
        font: input.font
        leftPadding: input.leftPadding
        color: "DarkGray"
        anchors.verticalCenter: input.verticalCenter
    }

    TextInput {
        id: input
        selectByMouse: true
        font.pixelSize: 18
        text: searchBar.text
        height: parent.height
        width: parent.width
        verticalAlignment: Qt.AlignVCenter
        leftPadding: 5
        onAccepted: searchBar.enter()
        onTextChanged: searchBar.value = text

        Binding on text {
            value: controller.location
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Tab) {
            if (suggestion.text !== "") {
                input.text = suggestion.text
            }
            event.accepted = true
        }
    }

    Image {
        sourceSize.height: parent.height * 0.8
        sourceSize.width: height
        source: "qrc:/ui/icons/search.svg"
        anchors.right: parent.right
        anchors.rightMargin: parent.height * 0.2
        anchors.verticalCenter: parent.verticalCenter
    }
}
