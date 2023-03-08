import QtQuick 2.12
import QtCharts 2.3
import QtQuick.Controls 2.12

ChartView {
    id: chart

    property var controller: LeftUIController
    property var model: controller.lineChartModel()
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
        DateTimeAxis {
            id: xAxis
            gridVisible: true
            format: "dd.MM.yy hh:mm"
            minorGridVisible: true
            titleText: model.labelX
            min: model.xAxisMin
            max: model.xAxisMax
        },

        ValueAxis {
            id: yAxis
            gridVisible: true
            minorGridVisible: true
            titleText: model.labelY
            min: model.yAxisMin
            max: model.yAxisMax
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
            text: "Reset chart"
            onTriggered: {
                chart.zoomReset()
            }
        }

        MenuItem {
            text: "Save data set"
            onTriggered: {
                nameDialog.open()
            }
        }

        MenuItem {
            text: "Save as image"
            onTriggered: {
                saveUtility.save()
            }
        }
    }

    NameDialog {
        id: nameDialog
        title: "Save Data Set"
        onAccepted: {
            controller.saveDataSet(userInput)
            clearUserInput()
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
        for (var graphIndex = 0; graphIndex < model.graphCount; graphIndex++) {
            var series = chart.createSeries(ChartView.SeriesTypeLine, "",
                                            xAxis, yAxis)
            model.transferSeries(series, graphIndex)
        }
    }
}
