import QtQuick 2.1
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
        id: reviewId
        anchors.fill: parent
        objectName: "review"
        onDiffChanged: fileTreeModel.paths = review.diff.paths
        SplitView {
            anchors.fill: parent
            orientation: Qt.Horizontal
            Rectangle {
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
            Rectangle {
                ListView {
                    anchors.fill: parent
                    orientation: Qt.Vertical
                    model: review.diff.deltas
                    delegate: deltaView
                    onFlickStarted: ListView.verticalVelocity = 10000
                    maximumFlickVelocity: 10000
                    flickDeceleration: 10000
                }
                DeltaView {
                    id: deltaView
                }
            }
        }
    }
}
