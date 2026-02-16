import QtQuick
import "../../theme/color" as ThemeColor
import QtQuick.Window

Column {

    anchors.horizontalCenter: parent.horizontalCenter
    spacing: 12

    Repeater {
        id: items
        model: 3

        Rectangle {
            implicitWidth: 850
            implicitHeight: 80
            color: ThemeColor.Color.base
            radius: 12

            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left : parent.left
                anchors.leftMargin: 12

                Image {
                    source: Qt.resolvedUrl("../../icons/default-application.svg")
                    width: 48
                    height: 48
                    smooth: true
                    antialiasing: true
                    mipmap: true
                    sourceSize.width: 48
                    sourceSize.height: 48
                    fillMode: Image.PreserveAspectFit
                }
                Column {
                    Row {
                        Text {
                            text: "Application Name"
                            font.pixelSize: 16
                            font.weight: 800
                            color: ThemeColor.Color.text
                        }
                    }
                    Text {
                        text: "Application description. This is where you put application description..."
                        font.pixelSize: 12
                        font.weight: 400
                        color: ThemeColor.Color.disabledFg
                    }
                }
            }
        }
    }
}
