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
                anchors.left: parent.left
                anchors.leftMargin: 12
                spacing: 12

                Image {
                    id: search_image
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
                    anchors.verticalCenter: parent.verticalCenter

                    Row {
                        spacing: 8

                        Text {
                            text: "Application Name"
                            font.pixelSize: 18
                            font.weight: 700
                            color: ThemeColor.Color.text
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Rectangle {
                            implicitWidth: 66
                            implicitHeight: 18
                            radius: 10
                            color: ThemeColor.Color.link
                            anchors.verticalCenter: parent.verticalCenter

                            Text {
                                text: "Pacman"
                                font.pixelSize: 11
                                font.weight: 600
                                anchors.centerIn: parent
                                color: ThemeColor.Color.text
                            }
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

            Rectangle {
                implicitWidth: 102
                implicitHeight: 23
                radius: 10
                color: ThemeColor.Color.darkFill
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 12

                Text {
                    text: "SHIFT + 1"
                    font.pixelSize: 11
                    font.weight: 500
                    anchors.centerIn: parent
                    color: ThemeColor.Color.text
                }
            }
        }
    }
}
