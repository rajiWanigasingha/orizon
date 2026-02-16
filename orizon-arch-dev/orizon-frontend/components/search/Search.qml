import Quickshell
import Quickshell.Widgets
import QtQuick
import "../../theme/color" as ThemeColor
import QtQuick.Controls

Rectangle {
    id: search_container
    width: parent.width
    height: 60
    topLeftRadius: 12
    topRightRadius: 12
    color: ThemeColor.Color.bg

    property var focused: ThemeColor.Color.border;

    Row {
        spacing: 10
        anchors.centerIn: parent

        IconImage {
            source: Qt.resolvedUrl("../../icons/search.svg")
            implicitWidth: 16
            implicitHeight: 16
            smooth: true
            onStateChanged: {
                if (status === Image.Ready) {
                    mipmap = true;
                }
            }
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: search_input
            focus: true
            focusReason: Qt.ActiveWindowFocusReason
            font {
                pixelSize: 15
                weight: 500
            }
            color: ThemeColor.Color.text
            placeholderText: "Search for applications"
            placeholderTextColor: ThemeColor.Color.disabledFg
            background: Rectangle {
                implicitWidth: 816
                implicitHeight: 24
                color: "transparent"
            }
            anchors.verticalCenter: parent.verticalCenter

            onActiveFocusChanged: {
                if (focus) {
                    search_container.focused = ThemeColor.Color.borderEdge
                } else {
                    search_container.focused = ThemeColor.Color.border
                }
            }

            Component.onCompleted : search_input.forceActiveFocus()
        }

        IconImage {
            source: Qt.resolvedUrl("../../icons/close.svg")
            implicitWidth: 16
            implicitHeight: 16
            smooth: true
            onStateChanged: {
                if (status === Image.Ready) {
                    mipmap = true;
                }
            }
            anchors.verticalCenter: parent.verticalCenter
            
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    search_input.clear()
                }
                cursorShape: Qt.PointingHandCursor
            }
        }
    }

    Rectangle {
        width: parent.width
        height: 2
        color: search_container.focused
        anchors.horizontalCenter: search_container.horizontalCenter
        anchors.top: search_container.bottom
    }
}
