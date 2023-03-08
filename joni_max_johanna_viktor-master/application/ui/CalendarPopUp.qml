import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.12

Dialog {
    id: dialog
    title: "Select Date"

    property date date: calendar.selectedDate

    standardButtons: Dialog.Ok

    function reset() {
        var d = new Date
        calendar.maximumDate = d
        calendar.selectedDate = d
        monthComboBox.currentIndex = d.getMonth()
        yearComboBox.currentIndex = 0
    }

    ColumnLayout {
        clip: true
        anchors.centerIn: parent
        RowLayout {
            ComboBox {
                id: monthComboBox
                model: MonthModel
                textRole: "display"
                height: 40
                Layout.fillWidth: true
                onCurrentIndexChanged: {
                    calendar.visibleMonth = currentIndex
                }
            }

            ComboBox {
                id: yearComboBox
                model: YearModel
                clip: true
                textRole: "display"
                Layout.fillWidth: true
                onCurrentIndexChanged: {
                    calendar.visibleYear = currentText
                }
            }
        }

        Calendar {
            id: calendar
            Layout.alignment: Qt.AlignHCenter
            navigationBarVisible: false
            maximumDate: new Date
            minimumDate: "1980-01-01"
            onVisibleMonthChanged: {
                if (visible)
                    monthComboBox.currentIndex = visibleMonth
            }
            onVisibleYearChanged: {
                if (visible)
                    yearComboBox.currentIndex = yearComboBox.find(
                                visibleYear.toString())
            }
        }
    }
}
