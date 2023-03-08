import QtQuick 2.0

MouseArea {
    hoverEnabled: true

    property double lastX: 0
    property double lastY: 0

    signal moveX(double amount)
    signal moveY(double amount)
    signal zoom(double amount)
    signal rightClick

    acceptedButtons: Qt.LeftButton | Qt.RightButton

    onPositionChanged: {
        if (pressedButtons & Qt.LeftButton) {
            moveX(mouseX - lastX)
            moveY(mouseY - lastY)
        }
        lastX = mouseX
        lastY = mouseY
    }

    onWheel: {
        if (wheel.angleDelta.y > 0) {
            zoom(1.1)
        } else {
            zoom(0.9)
        }
    }

    onPressed: {
        // Needed for reset zoom to reset also the movement
        zoom(1.0001)
        if (mouse.button & Qt.RightButton) {
            rightClick()
        }
    }
}
