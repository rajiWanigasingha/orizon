import Quickshell
import QtQuick
import "theme/color" as ThemeColor
import "components/search"
import "components/searchItem"

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
            Search {}
            SearchItem {}
        }
    }
}
