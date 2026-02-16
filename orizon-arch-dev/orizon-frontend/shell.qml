import Quickshell
import QtQuick
import "theme/color" as ThemeColor
import "components/search" 1.0

PanelWindow {
    implicitWidth: 900;
    implicitHeight: 600;
    color: "transparent";
    focusable: true

    Rectangle {
        color: ThemeColor.Color.bg
        anchors.fill: parent
        radius: 12

        Search {}
    }
}
