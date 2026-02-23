pragma ComponentBehavior: Bound
import QtQuick
import "../../theme/color" as ThemeColor
import QtQuick.Window
import Quickshell.Io
import QtQuick.Controls
import Quickshell.Widgets
import Quickshell

ScrollView {
    width: 900
    height: 600
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    Column {
        id: fileLoad
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 12

        FileView {
            id: jsonFile
            path: Qt.resolvedUrl("/home/rajindawanigasingha/.cache/applicationWatchCache/applicationWatchCache.json")
            blockLoading: true
        }

        readonly property var jsonData: JSON.parse(jsonFile.text())

        Repeater {
            id: items
            model: fileLoad.jsonData.length

            Rectangle {
                id: component
                implicitWidth: 850
                implicitHeight: 80
                color: ThemeColor.Color.base
                radius: 12
                required property int index

                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 12
                    spacing: 12

                    IconImage {
                        width: 48
                        height: 48
                        smooth: true
                        antialiasing: true
                        mipmap: true
                        source: Quickshell.iconPath(fileLoad.jsonData[component.index].applicationIcons) ?? Qt.resolvedUrl("../../icons/default-application.svg")
                    }

                    Column {
                        anchors.verticalCenter: parent.verticalCenter

                        Row {
                            spacing: 8

                            Text {
                                text: fileLoad.jsonData[component.index].applicationName ?? "Unkown"
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
                            text: fileLoad.jsonData[component.index].applicationDescription ?? "Unkown description"
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
                    visible: component.index < 10

                    Text {
                        text: component.index < 10 ? `SHIFT + ${component.index + 1}` : ""
                        font.pixelSize: 11
                        font.weight: 500
                        anchors.centerIn: parent
                        color: ThemeColor.Color.text
                    }
                }
            }
        }
    }
}
