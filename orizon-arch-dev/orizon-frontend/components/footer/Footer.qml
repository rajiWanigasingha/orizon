import QtQuick
import "../../theme/color" as ThemeColor
import Quickshell.Widgets

Rectangle {
    implicitWidth: 900
    implicitHeight: 54
    color: ThemeColor.Color.darkFill
    bottomLeftRadius: 12
    bottomRightRadius: 12

    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 12
        spacing: 20

        IconImage {
            source: Qt.resolvedUrl("../../icons/application.png")
            implicitWidth: 28
            implicitHeight: 28
            smooth: true
            onStateChanged: {
                if (status === Image.Ready) {
                    mipmap = true;
                }
            }
            anchors.verticalCenter: parent.verticalCenter
        }

        IconImage {
            source: Qt.resolvedUrl("../../icons/folder.png")
            implicitWidth: 28
            implicitHeight: 28
            smooth: true
            onStateChanged: {
                if (status === Image.Ready) {
                    mipmap = true;
                }
            }
            anchors.verticalCenter: parent.verticalCenter
        }

        IconImage {
            source: Qt.resolvedUrl("../../icons/open.png")
            implicitWidth: 28
            implicitHeight: 28
            smooth: true
            onStateChanged: {
                if (status === Image.Ready) {
                    mipmap = true;
                }
            }
            anchors.verticalCenter: parent.verticalCenter
        }

        IconImage {
            source: Qt.resolvedUrl("../../icons/cmd.png")
            implicitWidth: 28
            implicitHeight: 28
            smooth: true
            onStateChanged: {
                if (status === Image.Ready) {
                    mipmap = true;
                }
            }
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 12

        Rectangle {
            implicitWidth: 102
            implicitHeight: 23
            radius: 10
            color: ThemeColor.Color.bg

            Text {
                text: "CTRL + 1..4"
                font.pixelSize: 11
                font.weight: 500
                anchors.centerIn: parent
                color: ThemeColor.Color.text
            }
        }
    }
}
