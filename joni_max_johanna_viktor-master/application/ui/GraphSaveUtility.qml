import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: saveUtility
    signal fileSelected
    function save() {
        saveGraphPrompt.open()
    }

    GraphSaveFilePrompt {
        id: saveGraphPrompt
        onAccepted: {
            fileSelected()
        }
    }

    function saveToFile(image) {
        var saveFile = cleanPath(saveGraphPrompt.fileUrl)
        console.log("Saving to", saveFile)
        image.saveToFile(saveFile)
    }

    function cleanPath(path) {
        var pathStr = path.toString()
        return pathStr.replace("file:///", "")
    }
}
