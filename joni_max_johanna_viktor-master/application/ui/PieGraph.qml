import QtQuick 2.12
import QtCharts 2.3
import QtQuick.Controls 2.12

ChartView {
    id: chart
    property var model: undefined
    theme: ChartView.ChartThemeDark
    title: model.title
    antialiasing: true

    legend.visible: true
    legend.font.pixelSize: 16

    Component.onCompleted: {
        readModel()
    }

    Connections {
        target: model
        function onGraphsChanged() {
            readModel()
        }
    }

    axes: [
        ValueAxis {
            id: axis
        }
    ]

    GraphMouseArea {
        id: mouseArea
        anchors.fill: chart
        onMoveX: chart.scrollLeft(amount)
        onMoveY: chart.scrollUp(amount)
        onZoom: chart.zoom(amount)

        onRightClick: {
            if (!noData.visible) {
                graphContextMenu.popup()
            }
        }
    }

    Menu {
        id: graphContextMenu
        MenuItem {
            text: "Save as image"
            onTriggered: {
                saveUtility.save()
            }
        }
    }

    GraphSaveUtility {
        id: saveUtility
        onFileSelected: {
            chart.grabToImage(function (result) {
                saveToFile(result)
            })
        }
    }

    GraphNoData {
        id: noData
        model: parent.model
        anchors.fill: parent
        visible: model.graphCount === 0
        z: mouseArea.z + 100
    }

    function readModel() {
        chart.removeAllSeries()
        if (model.graphCount > 0) {
            var series = chart.createSeries(ChartView.SeriesTypePie, "",
                                            axis, axis)
            model.transferSeries(series)
        }
    }
}
