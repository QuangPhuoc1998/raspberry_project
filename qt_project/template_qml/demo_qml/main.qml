import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 800
    height: 480
    color: '#242424'
    title: qsTr("Hello World")

    Dial {
        id: control
        x: 80
        y: 148
        background: Rectangle {
            x: control.width / 2 - width / 2
            y: control.height / 2 - height / 2
            width: Math.max(64, Math.min(control.width, control.height))
            height: width
            color: "transparent"
            radius: width / 2
            border.color: control.pressed ? "#17a81a" : "#21be2b"
            opacity: control.enabled ? 1 : 0.3
        }

        handle: Rectangle {
            id: handleItem
            x: control.background.x + control.background.width / 2 - width / 2
            y: control.background.y + control.background.height / 2 - height / 2
            width: 16
            height: 16
            color: control.pressed ? "#17a81a" : "#21be2b"
            radius: 8
            antialiasing: true
            opacity: control.enabled ? 1 : 0.3
            transform: [
                Translate {
                    y: -Math.min(control.background.width, control.background.height) * 0.4 + handleItem.height / 2
                },
                Rotation {
                    angle: control.angle
                    origin.x: handleItem.width / 2
                    origin.y: handleItem.height / 2
                }
            ]
        }
    }

    Button {
        id: button_change_color
        x: 593
        y: 206
        width: 135
        height: 69
        text: qsTr("Click")

        contentItem: Text {
            font: control.font
            opacity: enabled ? 1.0 : 0.3
            color: control.down ? "#FF0000" : "#21be2b"
            text: "Click"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            border.color: control.down ? "#17a81a" : "#21be2b"
            border.width: 1
            radius: 2
        }
        onClicked:
        {
            if (rectangle.color == "#00ff00")
            {
                rectangle.color = "#ff0000"
            }
            else if (rectangle.color == "#ff0000")
            {
                rectangle.color = "#00ff00"
            }
            gpio_handler.control_led()
        }
    }

    Rectangle {
        id: rectangle
        x: 332
        y: 140
        width: 200
        height: 200
        color: "#00ff00"
    }

    Button {
        id: button_exit
        x: 703
        y: 0
        width: 97
        height: 61
        text: qsTr("Click")
        contentItem: Text {
            color: control.down ? "#FF0000" : "#21be2b"
            text: "Exit"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            font: control.font
            opacity: enabled ? 1.0 : 0.3
        }
        background: Rectangle {
            radius: 2
            border.color: control.down ? "#17a81a" : "#21be2b"
            implicitWidth: 100
            border.width: 1
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
        }
        onClicked:
        {
            gpio_handler.disable_led();
            Qt.quit()
        }
    }

    Button {
        id: button_power_off
        x: 703
        y: 419
        width: 97
        height: 61
        text: qsTr("Click")
        background: Rectangle {
            radius: 2
            opacity: enabled ? 1 : 0.3
            implicitHeight: 40
            border.width: 1
            border.color: control.down ? "#17a81a" : "#21be2b"
            implicitWidth: 100
        }
        contentItem: Text {
            color: control.down ? "#FF0000" : "#21be2b"
            text: "Power off"
            horizontalAlignment: Text.AlignHCenter
            opacity: enabled ? 1.0 : 0.3
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        onClicked:
        {
            system_handler.system_gui_off();
            Qt.quit()
        }
    }
}
