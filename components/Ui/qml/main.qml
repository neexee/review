import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.1
import review 1.0

ApplicationWindow {
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300

    title: "Review prototype"

    ApplicationWindow {
        id: aboutBox

        width: 280
        height: 120
        title: "About Review"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 8
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Label {
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    text: "This is a graphical git-diff-blame implementation.\n 2016"
                }
            }
            Button {
                text: "Ok"
                isDefault: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                onClicked: aboutBox.close()
            }
            Keys.onReturnPressed: aboutBox.close()
            focus: true
        }
    }
    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem { text: "Quit"; onTriggered: Qt.quit() }
        }
        Menu {
            title: "&Help"
            MenuItem { text: "About..." ; onTriggered: aboutBox.show() }
        }
    }
    ToolBar {
        id: toolBar
        width: parent.width

        RowLayout {
            anchors.fill: parent
            SpinBox {
                id: fontSizeSpinBox
                implicitWidth: 50
                value: 0
                onValueChanged: diffView.fontSize = value
            }
            Item { Layout.fillWidth: true }
        }
    }

    Review {
        id: review
        property var fixedFont: fixedFontMetrics
        onDiffChanged: fileTreeModel.paths = review.diff.paths
        objectName: "cppReview"
        anchors.fill: parent

        FontLoader {
            id: fixedFontLoader
            name: "Monospace"
        }
        FontMetrics {
            id: fixedFontMetrics
            font.family: fixedFontLoader.name
            font.pointSize: 10
        }

        SplitView {
            anchors.fill: parent
            orientation: Qt.Horizontal
            Rectangle {
                id: fileTree
                width: 200
                TreeView {
                    model: fileTreeModel
                    anchors.fill: parent
                    TableViewColumn {
                        title: "File names"
                        role: "fileName"
                    }
                }
            }

            ListView {
                id: deltaListView

                anchors.left: fileTree.right
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                orientation: Qt.Vertical

                model: cppReview.diff.deltas

                delegate: DeltaView {
                }
                onFlickStarted: ListView.verticalVelocity = 10000
                maximumFlickVelocity: 10000
                flickDeceleration: 10000
            }
        }
    }
}
