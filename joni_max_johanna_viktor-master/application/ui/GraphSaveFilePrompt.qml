import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3

FileDialog {
    id: fileDialog
    title: "Choose save destination"
    folder: shortcuts.pictures
    selectExisting: false
    selectMultiple: false
    nameFilters: ["Image files (*.jpg *.jpeg)"]
}
