import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 800
    height: 480
    color: '#242424'
    title: qsTr("GUI GPIO")

    Button
    {
        id: control
        x: 314
        y: 188
        width: 172
        height: 104
        text: qsTr("Button")

        contentItem: Text {
            font: control.font
            opacity: enabled ? 1.0 : 0.3
            color: control.down ? "#17a81a" : "#21be2b"
            text: "CLICK"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: "#E0B6CD"
            border.color: control.down ? "#17a81a" : "#21be2b"
            border.width: 1
            radius: 2
        }
        onClicked:
        {
            gpio_handler.control_led()
        }
    }

    Button {
        id: exit
        x: 734
        y: 0
        width: 66
        height: 50
        text: qsTr("Button")
        background: Rectangle {
            color: "#FF0000"
            radius: 2
            border.width: 1
            opacity: enabled ? 1 : 0.3
            border.color: exit.down ? "#17a81a" : "#21be2b"
            implicitWidth: 100
            implicitHeight: 40
        }
        contentItem: Text {
            color: exit.down ? "#17a81a" : "#21be2b"
            text: "Exit"
            opacity: enabled ? 1.0 : 0.3
            elide: Text.ElideRight
            font: exit.font
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        onClicked:
        {
            gpio_handler.disable_led();
            Qt.quit()
        }
    }
}
