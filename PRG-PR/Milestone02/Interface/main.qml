import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    id: root

    Row {
        id: tools

        Button {
            id: start
            text: "Start"
            onClicked: {

            }
        }
        Button {
            id: points
            text: "Punkte"
            onClicked: {
                mouse.print()
            }
        }
    }

    Canvas {
        id: canvas
        anchors.top: tools.bottom
        width: 640
        height: 480
        property int lastX
        property int lastY

        onPaint: {
            var ctx = getContext("2d")
            ctx.lineWidth = 2
            ctx.beginPath()
            ctx.arc(lastX,lastY,4,0,2*Math.PI);
            lastX = area.mouseX
            lastY = area.mouseY
            ctx.stroke()

            mouse.add(lastX, lastY)
        }
        MouseArea {
            id: area
            anchors.fill: parent
            onPressed: {
                canvas.lastX = mouseX
                canvas.lastY = mouseY
            }

            onClicked: {
                canvas.requestPaint()
            }
        }
    }
}
