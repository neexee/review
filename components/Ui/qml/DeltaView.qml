import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

Component {
    Column {
        width: parent.width
        spacing: 0

        Rectangle {
            height: 25
            width: parent.width
            color: "#204a87"
            border.color: "#729fcf"
            
            Text {
                anchors.centerIn: parent
                text: modelData.Path()
                color: "white"
            }
        }

        TableView {
            id: fileDiffView
            property var reviewFont: review.fixedFont
            property var rowHeight: reviewFont.height

            frameVisible: false
            headerVisible: false
            height : rowCount * rowHeight
            width: parent.width

            model: modelData

            style: TableViewStyle {
                itemDelegate: LineView {
                }
                rowDelegate: Component {
                    Rectangle {
                        height: fileDiffView.rowHeight
                    }
                }
            }

            TableViewColumn {
                id: rowColumn
                title: "Row"
                role: "rowNumber"
                movable: false
                resizable: true
                width: 20
            }
            TableViewColumn {
                id: infoColumn
                title: "Info"
                role: "commitInfo"
                movable: false
                resizable: true
                elideMode: Text.ElideMiddle
                width:  fileDiffView.viewport.width / 7
            }
            TableViewColumn {
                id: textColumn
                title: "Text"
                role: "text"
                movable: false
                resizable: true
                objectName: "textColumn"
                width: fileDiffView.viewport.width - rowColumn.width - infoColumn.width
            }

            Component.onCompleted: {
                rowColumn.resizeToContents()
                infoColumn.resizeToContents()
            }
        }
    }
}
