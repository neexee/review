import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

Component {
    Column {
        width: parent.width
        spacing: 0

        TextArea {
            height: review.fixedFont.height * 2
            width: parent.width
            horizontalAlignment: TextEdit.AlignHCenter
            text: modelData.Path()
            readOnly: true

            style: TextAreaStyle {
                font: review.fixedFont.font
                textColor: "white"
                selectionColor: "steelblue"
                selectedTextColor: "#eee"
                backgroundColor: "#204a87"
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
                id: infoColumn
                title: "Info"
                role: "commitInfo"
                movable: false
                resizable: true
                width: fileDiffView.viewport.width/7 - rowColumn.width
            }

            TableViewColumn {
                id: rowColumn
                title: "Row"
                role: "rowNumber"
                movable: false
                resizable: true
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
                //infoColumn.resizeToContents()
            }
        }
    }
}
