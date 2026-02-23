import Quickshell
import QtQuick
import "theme/color" as ThemeColor
import "components/search"
import "components/searchItem"
import "components/footer"

PanelWindow {
    id: window
    implicitWidth: 900
    implicitHeight: 600
    color: "transparent"
    focusable: true

    Rectangle {
        color: ThemeColor.Color.bg
        anchors.fill: parent
        radius: 12

        Column {
            spacing: 24
            anchors.fill: parent
            Search {
                id: search
            }
            SearchItem {
                anchors.top: search.bottom
                anchors.topMargin: 24
                anchors.left: parent.left
                anchors.leftMargin: 24
                anchors.bottomMargin: 66
                anchors.bottom: parent.bottom
            }
        }

        Footer {
            anchors.bottom: parent.bottom
        }
    }
}
