import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: item
    signal selection(string name)
    property string headerText: "Header Text"
    property var model: undefined

    function setIndex(index) {
        listView.currentIndex = index
    }

    Rectangle {
        z: -1
        anchors.fill: parent
        color: "white"
    }

    ListView {
        id: listView
        model: item.model
        headerPositioning: ListView.OverlayHeader
        boundsMovement: Flickable.StopAtBounds
        delegate: listDelegate
        header: headerDelegate
        anchors.fill: parent
        clip: true

        ScrollBar.vertical: ScrollBar {
            active: true
        }

        onVisibleChanged: {
            currentIndex = -1
        }

        function select() {
            selection(currentItem.name)
        }
    }

    Component {
        id: headerDelegate
        Rectangle {
            z: 100
            width: listView.width
            height: myText.contentHeight
            border.color: "black"
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "white"
                }
                GradientStop {
                    position: 1
                    color: "lightBlue"
                }
            }

            Label {
                id: myText
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Helvetica"
                font.pointSize: 15
                text: item.headerText
            }
        }
    }

    Component {
        id: listDelegate
        Rectangle {
            property string name: display
            width: listView.width
            height: 20
            color: ListView.isCurrentItem ? "lightBlue" : "white"
            clip: true

            Label {
                text: name
                width: parent.width
                height: parent.height
                leftPadding: 10
                font.pixelSize: 18
                elide: Label.ElideRight
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    listView.currentIndex = index
                    listView.select()
                }
            }
        }
    }
}
