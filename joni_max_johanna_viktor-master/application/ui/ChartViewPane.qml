import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: pane

    // By default pane is left pane
    // change controller and model for right
    property var controller: LeftUIController

    Connections {
        target: controller
        function onChartTypeChanged() {
            comboBox.currentIndex = controller.chartIndex
        }
    }

    ComboBox {
        id: comboBox
        model: ChartTypesModel
        textRole: "display"
        font.pixelSize: 18
        width: parent.width
        anchors.top: parent.top
        onCurrentTextChanged: controller.chartType = currentText
    }

    LineGraph {
        id: linegraph
        controller: parent.controller
        width: parent.width
        anchors.top: controlPanel.bottom
        anchors.bottom: parent.bottom
        visible: !busyIndicator.visible && !pieGraph.visible
    }

    PieGraph {
        id: pieGraph
        model: controller.pieChartModel()
        width: parent.width
        anchors.top: controlPanel.bottom
        anchors.bottom: parent.bottom
        visible: !busyIndicator.visible && comboBox.currentIndex == 7
    }

    BusyWheel {
        id: busyIndicator
        width: 200
        height: 200
        anchors.centerIn: linegraph
        visible: controller.busyIndicator
        color: "#232323"
    }

    Item {
        id: controlPanel
        width: parent.width
        height: 180
        anchors.top: comboBox.bottom

        // Order of elements is defined in m_chartTypes in uicontroller.h
        WeatherForecast {
            controller: pane.controller
            visible: comboBox.currentIndex === 0
            anchors.fill: parent
        }

        WeatherHistory {
            controller: pane.controller
            visible: comboBox.currentIndex === 1
            anchors.fill: parent
        }

        WeatherMonthly {
            controller: pane.controller
            visible: comboBox.currentIndex === 2
            anchors.fill: parent
        }

        ElectricityProdCons {
            controller: pane.controller
            visible: comboBox.currentIndex === 3
            anchors.fill: parent
        }

        ElectricityForecast {
            controller: pane.controller
            visible: comboBox.currentIndex === 4
            anchors.fill: parent
        }

        EnergyProdForecast {
            controller: pane.controller
            visible: comboBox.currentIndex === 5
            anchors.fill: parent
        }

        ElectricityProdMethods {
            controller: pane.controller
            visible: comboBox.currentIndex === 6
            anchors.fill: parent
        }

        ElectricityProdDistr {
            controller: pane.controller
            visible: comboBox.currentIndex === 7
            anchors.fill: parent
        }

        SavedDataSets {
            controller: pane.controller
            visible: comboBox.currentIndex === 8
            anchors.fill: parent
        }
        RealTimeData {
            controller: pane.controller
            visible: comboBox.currentIndex === 9
            anchors.fill: parent
        }
        RealTimeData {
            controller: pane.controller
            visible: comboBox.currentIndex === 10
            anchors.fill: parent
        }
        RealTimeData {
            controller: pane.controller
            visible: comboBox.currentIndex === 11
            anchors.fill: parent
        }
    }
}
