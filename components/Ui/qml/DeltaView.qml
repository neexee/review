import QtQuick 2.1

Component {
    Column {
        width: parent.width
        spacing: 2
        Rectangle {
            height: 25
            width: parent.width
            color: "#204a87"
            border.color: "#729fcf"
            Text {
                anchors.centerIn: parent
                text: modelData.path
                color: "white"
            }
        }
        Rectangle {
            height: fileView.count * 20
            width: parent.width
            ListView {
                id: fileView
                anchors.fill: parent
                orientation: Qt.Vertical
                model: modelData.diffLines
                delegate: lineDelegate
            }
            LineView {
                id: lineDelegate
            }
        }
    }
}
